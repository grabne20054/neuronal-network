#include "../include/neuron.h"

double activate_function(double sum)
{
    //return (1.0 / (1.0 + exp(-sum)));

    if (sum > 0)
    {
        return 1;
    }
    return 0;
    
}


double perform(neuron_t *neuron, size_t len)
{

    double sum = 0;

    for (size_t i = 0; i < len; i++)
    {
        sum += (neuron->input[i] * neuron->weight[i]);
    }

    double acv = activate_function(sum);

    return acv + neuron->bias;

}


neuron_t *init_neuron(double *target, size_t target_len, size_t layer)
{
    neuron_t *neuron = malloc(sizeof(neuron_t));
    neuron->input = malloc(sizeof(double) * target_len);
    neuron->weight = malloc(sizeof(double) * target_len);
    neuron->output = malloc(sizeof(double) * target_len);
    neuron->next_layer_neurons = NULL;

    neuron->layer = layer;

    neuron->bias = rand_double();

    for (size_t i = 0; i < target_len; i++)
    {
        neuron->output[i] = rand_double();
    }
    
    memcpy(neuron->input, target, target_len * sizeof(double));

    return neuron;
}


double rand_double()
{
    return (double)rand() / (double)RAND_MAX;
}


void free_neuron(neuron_t *neuron)
{
    if (!neuron) {return;}
    
    free(neuron->output);
    free(neuron->weight);
    free(neuron->input);
    free(neuron);
}

void connect(neuron_t *parent, neuron_t *child)
{
    parent->next_layer_neurons = realloc(parent->next_layer_neurons, (parent->next_layer_neurons_length + 1) * sizeof(*parent->next_layer_neurons));
    parent->next_layer_neurons[parent->next_layer_neurons_length++] = child;
}