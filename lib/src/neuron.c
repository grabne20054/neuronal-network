#include "../include/neuron.h"

double activate_function(double sum)
{
    return (1.0 / (1.0 + exp(-sum)));

    /*if (sum > 0)
    {
        return 1;
    }
    return 0;*/
    
}


void perform(neuron_t *neuron, size_t len)
{
    if (neuron->weight == NULL) // indicate neuron is io
    {
        //neuron->output = neuron->input;
        printf("IO NEURON EXIT\n");
        return;
    }

    double sum = 0;

    for (size_t i = 0; i < len; i++)
    {
        sum += (neuron->input[i] * neuron->weight[i]);
    }

    sum += neuron->bias;

    double acv = activate_function(sum);

    neuron->output = acv;

}


neuron_t *init_io_neuron(size_t features_per_sample)
{
    neuron_t *neuron = malloc(sizeof(neuron_t));
    neuron->input = malloc(sizeof(double) * features_per_sample);
    neuron->weight = NULL;
    neuron->output = 0;

    neuron->input_len = features_per_sample;
    
    return neuron;
}

neuron_t *init_neuron(size_t features_per_sample)
{
    neuron_t *neuron = malloc(sizeof(neuron_t));
    neuron->input = malloc(sizeof(double) * features_per_sample);
    neuron->weight = malloc(sizeof(double) * features_per_sample);
    neuron->output = 0;

    neuron->input_len = features_per_sample;

    neuron->bias = rand_double();

    for (size_t i = 0; i < features_per_sample; i++)
    {
        neuron->weight[i] = rand_double();
    }
    
    return neuron;
}


double rand_double()
{
    return (double)rand() / (double)RAND_MAX;
}


void free_neuron(neuron_t *neuron)
{
    if (!neuron) {return;}
    
    free(neuron->weight);
    free(neuron->input);
    free(neuron);
}