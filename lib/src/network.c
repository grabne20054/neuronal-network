#include "../include/network.h"
#include "../include/neuron.h"

void feed_forward(network_t *network)
{

    for (size_t i = 0; i < network->layers_length - 1; i++)
    {
        layer_t *current = network->layers[i];
        layer_t *next = network->layers[i + 1];

        for (size_t n = 0; n < current->neurons_list_lenght; n++)
        {
            perform(current->neurons_list[n], current->neurons_list[n]->input_len);
        }

        for (size_t next_n = 0; next_n < next->neurons_list_lenght; next_n++)
        {
            for (size_t curr_n = 0; curr_n < current->neurons_list_lenght; curr_n++)
            {
                next->neurons_list[next_n]->input[curr_n] = current->neurons_list[curr_n]->output[0];

            }
        }
    }
    
}

void propagate_back(network_t *network)
{
    for (size_t i = network->layers_length - 1; i > 0; i--)
    {
        if (network->layers[i]->io == false)
        {
            for (size_t j = 0; j < network->layers[i]->neurons_list_lenght; j++)
            {
                double delta = calc_error(network->target, network->layers[i]->neurons_list[j]->output[0]);
                printf("DELTA : %f\n", delta);
                update_weights(delta, network->layers[i]->neurons_list[j], network->learning_rate);
            }
            
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

    for (size_t i = 0; i < neuron->input_len; i++)
    {
        neuron->weight[i] += learning_rate * delta * neuron->input[i];
        printf("NEW WEIGHT: %f\n", neuron->weight[i]);
    }

    neuron->bias += learning_rate * delta;
    printf("NEW BIAS: %f\n", neuron->bias);
}

network_t *init_network(size_t layers, size_t neurons_per_layer, double *inputs, size_t input_len, size_t epoch, double learning_rate, double target)
{
    network_t *network = malloc(sizeof(network_t));
    network->layers = malloc(sizeof(layer_t *) * layers);
    network->layers_length = layers;

    network->epoch = epoch;
    network->learning_rate = learning_rate;
    network->target = target;

    for (size_t i = 0; i < layers; i++)
    {
        layer_t *layer = init_layer(neurons_per_layer);
        network->layers[i] = layer;

        for (size_t j = 0; j < neurons_per_layer; j++)
        {
           
            if (i == 0 || i == layers-1)
            {
                printf("IO NEURON INIT\n");
                network->layers[i]->io = true;

                neuron_t *io_neuron = init_io_neuron(inputs, input_len);
                network->layers[i]->neurons_list[j] = io_neuron;
                network->layers[i]->neurons_list_lenght = 1;
                // curr one io input each io layer
                break;
            }
            printf("HIDDEN NEURON INIT\n");
            neuron_t *neuron = init_neuron(input_len);
            network->layers[i]->neurons_list[j] = neuron;
            
            
        }
    }

    return network;
}

void start_network(network_t *network)
{
    for (size_t i = 0; i < network->epoch; i++)
    {
        printf("EPOCH: %d\n", i);
        feed_forward(network);
        propagate_back(network);

        size_t neuron_len = network->layers[network->layers_length-1]->neurons_list_lenght;

        printf("%f\n", network->layers[network->layers_length-1]->neurons_list[neuron_len-1]->output[0]);
    }
    
}