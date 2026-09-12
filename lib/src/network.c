#include "../include/network.h"
#include "../include/neuron.h"

void feed_forward(network_t *network, double *sample)
{

    for (size_t i = 0; i < network->layers_length; i++)
    {
        
        layer_t *current = network->layers[i];
        layer_t *next = network->layers[i + 1];

        // perform calculation
        for (size_t n = 0; n < current->neurons_list_lenght; n++)
        {
            if (i == 0)
            {
                // set output = input = sample for i layer
                current->output = sample;
                current->neurons_list[n]->output = sample[n];
            }
            else
            {
                perform(current->neurons_list[n], current->neurons_list[n]->input_len);
            
                current->output[n] = current->neurons_list[n]->output;       
            }
        }

        // pass calculations to next layer if curr != o layer
        if (i != network->layers_length -1 && (i+1) != network->layers_length )
        {
            for (size_t next_n = 0; next_n < next->neurons_list_lenght; next_n++)
            {   
                //printf("CURR OUTPUT: %f\n", current->output[0]);
                next->neurons_list[next_n]->input = current->output;
            }
        }
    }
}

void propagate_back(network_t *network, double target)
{
    compute_delta(network, target);

    for (size_t i = network->layers_length - 1; i > 0; i--)
    {
        layer_t *current = network->layers[i];
        /* Output layer */
        if (i == network->layers_length - 1)
        {
            neuron_t *out = current->neurons_list[0];
            update_weights(out, network->learning_rate);
        }
        /* Hidden layers */
        else
        {
            for (size_t j = 0; j < current->neurons_list_lenght; j++)
            {
                neuron_t *curr = current->neurons_list[j];
                update_weights(curr, network->learning_rate);
            }
        }
    }
}

void compute_delta(network_t *network, double target)
{
    for (size_t i = network->layers_length - 1; i > 0; i--)
    {
        layer_t *current = network->layers[i];

        for (size_t j = 0; j < current->neurons_list_lenght; j++)
        {
            if (i == network->layers_length-1)
            {
                //printf("delta ib=%f output=%f\n",current->neurons_list[j]->delta, current->neurons_list[j]->output);
                current->neurons_list[j]->delta = calc_error(target, current->neurons_list[j]->output);
                //printf("delta i=%f\n",current->neurons_list[j]->delta);
            }
            else
            {
                // err calculation for hidden layers --> calculate the loss of the next layer neurons
                // current neuron has effect on all next layer neurons
                layer_t *next = network->layers[i + 1];
                double sum = 0.0;

                for (size_t k = 0; k < next->neurons_list_lenght; k++)
                {
                    neuron_t *next_neuron = next->neurons_list[k];

                    sum += next_neuron->delta * next_neuron->weight[j];
                    //printf("delta before b i=%zu j=%zu sum=%f, delta=%f weight=%f\n",i,j, sum, current->neurons_list[j]->delta, next_neuron->weight[j]);

                }

                //printf("delta before i=%zu j=%zu sum=%f, delta=%f\n",i,j, sum, current->neurons_list[j]->delta);

                current->neurons_list[j]->delta = current->neurons_list[j]->output * (1.0 - current->neurons_list[j]->output) * sum;

                //printf("hidden[%zu] output=%f sum=%f delta=%f\n",j, current->neurons_list[j]->output, sum, current->neurons_list[j]->delta);

            }
        }
    }
}

double calc_error(double target, double res_calc)
{

    double err = target - res_calc;
    return err * res_calc * (1-res_calc);

}

void update_weights(neuron_t *neuron, double learning_rate)
{

    for (size_t i = 0; i < neuron->input_len; i++)
    {
        neuron->weight[i] += learning_rate * neuron->delta * neuron->input[i];
    }

    neuron->bias += learning_rate * neuron->delta;
}

network_t *init_network(size_t hidden_layers, double **samples, size_t sample_len, size_t features_per_sample, size_t epoch, double learning_rate, int* targets)
{
    network_t *network = malloc(sizeof(network_t));
    network->layers = malloc(sizeof(layer_t *) * (hidden_layers+2));
    network->layers_length = hidden_layers + 2;

    network->epoch = epoch;
    network->learning_rate = learning_rate;
    network->targets = targets;

    network->samples_len = sample_len;

    network->samples = samples;
    network->features_per_sample = features_per_sample;

    //io layers init
    layer_t *i_layer = init_layer(features_per_sample);
    i_layer->io = true;
    network->layers[0] = i_layer;

    for (size_t i = 0; i < features_per_sample; i++)
    {
        printf("I NEURON INIT\n");
        neuron_t *i_neuron = init_io_neuron(features_per_sample);
        network->layers[0]->neurons_list[i] = i_neuron;

    }

    // o layer 1 neuron, 1 output
    printf("O NEURON INIT\n");
    layer_t *o_layer = init_layer(1);
    o_layer->io = true;
    network->layers[network->layers_length-1] = o_layer;
    neuron_t *o_neuron = init_neuron(features_per_sample);
    network->layers[network->layers_length-1]->neurons_list[0] = o_neuron;

    for (size_t i = 1; i < hidden_layers + 1; i++)
    {
        layer_t *hidden_layer = init_layer(features_per_sample);
        network->layers[i] = hidden_layer;

        for (size_t j = 0; j < features_per_sample; j++)
        {
            printf("HIDDEN NEURON INIT\n");
            neuron_t *neuron = init_neuron(features_per_sample);
            network->layers[i]->neurons_list[j] = neuron;
        }
    }

    return network;
}

void train_network(network_t *network)
{
    for (size_t i = 0; i < network->epoch; i++)
    {

        double loss = 0;
        for (size_t j = 0; j < network->samples_len; j++)
        {
            feed_forward(network, network->samples[j]);
            propagate_back(network, network->targets[j]);

            loss += 0.5 * (network->layers[network->layers_length-1]->neurons_list[0]->output - network->targets[j]) * (network->layers[network->layers_length-1]->neurons_list[0]->output - network->targets[j]);
            printf("OUTPUT OF SAMPLE[%zu] of EPOCH[%zu]: %f TARGET: %d\n", j, i, network->layers[network->layers_length-1]->neurons_list[0]->output, network->targets[j]);
        }

        printf("LOSS [%zu]: %f\n", i, loss);

    }
    
}

void free_network(network_t *network)
{
    for (size_t i = 0; i < network->layers_length; i++)
    {
        layer_t *layer = network->layers[i];

        for (size_t j = 0; j < layer->neurons_list_lenght; j++)
        {
            neuron_t *neuron = layer->neurons_list[j];
            free(neuron->input);
            free(neuron->weight);
            free(neuron);
        }

        free(layer->neurons_list);
        free(layer->output);
        free(layer);
    }

    free(network->layers);
    free(network);
}