#include "../include/network.h"
#include "../include/neuron.h"

void feed_forward(network_t *network, double *sample)
{

    for (size_t i = 0; i < network->layers_length - 1; i++)
    {
        layer_t *current = network->layers[i];
        layer_t *next = network->layers[i + 1];

        for (size_t n = 0; n < current->neurons_list_lenght; n++)
        {
            if (i == 0)
            {
                current->neurons_list[n]->input = sample; // input neuron should not perform --> weights are null
            }
            else
            {
                perform(current->neurons_list[n], current->neurons_list[n]->input_len);
                
                for (size_t j = 0; j < current->neurons_list[n]->input_len; j++)
                {
                    current->output[j] = current->neurons_list[n]->output;
                }
            }

        }

        for (size_t next_n = 0; next_n < next->neurons_list_lenght; next_n++)
        {   
            next->neurons_list[next_n]->input = current->output;
            printf("%zu , %zu, %p %zu\n", i+1, next_n ,next->neurons_list[next_n], next->neurons_list_lenght);
            next->neurons_list[next_n]->output = current->output[0];
        }
        
    }
    
}

void propagate_back(network_t *network)
{
        for (size_t i = network->layers_length-1; i > 0; i--)
        {
            printf("%zu\n", i);
            
            printf("hallo %p\n", network->layers[i]);

            for (size_t j = 0; j < network->layers[i]->neurons_list_lenght; j++)
            {
                printf("%p\n", network->layers[i]->neurons_list[j]);

                double delta = calc_error(network->target, network->layers[i]->neurons_list[j]->output);
                update_weights(delta, network->layers[i]->neurons_list[j], network->learning_rate);
                
                printf("OUTPUT AFTER BACKPROP: %f\n", network->layers[i]->neurons_list[j]->output);

            }
        }
}

double calc_error(double target, double res_calc)
{

    double err = target - res_calc;

    return err * res_calc * (1-res_calc);

}

void update_weights(double delta, neuron_t *neuron, double learning_rate)
{

    printf("%p\n", neuron->weight);

    for (size_t i = 0; i < neuron->input_len; i++)
    {
        neuron->weight[i] += learning_rate * delta * neuron->input[i];
    }
    printf("hallo\n");

    neuron->bias += learning_rate * delta;
}

network_t *init_network(size_t hidden_layers, size_t neurons_per_hidden_layer, double **samples, size_t sample_len, size_t features_per_sample, size_t epoch, double learning_rate, double target)
{
    network_t *network = malloc(sizeof(network_t));
    network->layers = malloc(sizeof(layer_t *) * (hidden_layers+2));
    network->layers_length = hidden_layers + 2;

    network->epoch = epoch;
    network->learning_rate = learning_rate;
    network->target = target;

    network->samples_len = sample_len;

    network->samples = samples;

    //io layers init
    layer_t *i_layer = init_layer(features_per_sample, features_per_sample);
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
    layer_t *o_layer = init_layer(1, 1);
    o_layer->io = true;
    network->layers[network->layers_length-1] = o_layer;
    neuron_t *o_neuron = init_io_neuron(features_per_sample);
    network->layers[network->layers_length-1]->neurons_list[0] = o_neuron;

    for (size_t i = 1; i < hidden_layers + 1; i++)
    {
        layer_t *hidden_layer = init_layer(neurons_per_hidden_layer, features_per_sample);
        network->layers[i] = hidden_layer;

        for (size_t j = 0; j < neurons_per_hidden_layer; j++)
        {
            printf("HIDDEN NEURON INIT\n");
            neuron_t *neuron = init_neuron(features_per_sample);
            network->layers[i]->neurons_list[j] = neuron;
        }
    }

    return network;
}

void start_network(network_t *network)
{
    for (size_t i = 0; i < network->epoch; i++)
    {
        printf("EPOCH: %zu\n", i);
        for (size_t j = 0; j < network->samples_len; j++)
        {
            printf("SAMPLE: %zu\n", j);
            feed_forward(network, network->samples[j]);
            propagate_back(network);

            printf("OUTPUT OF SAMPLE[%zu] of EPOCH[%zu]: %f\n", j, i, network->layers[network->layers_length-1]->output[0]);
        }

    }
    
}