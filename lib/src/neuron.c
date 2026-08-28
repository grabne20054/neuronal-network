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
        neuron->output = neuron->input;
        return;
    }

    double sum = 0;

    for (size_t i = 0; i < len; i++)
    {
        sum += (neuron->input[i] * neuron->weight[i]);
    }

    double acv = activate_function(sum);

    
    neuron->output[0] = acv + neuron->bias;
    printf("output of feed forward: %f\n", neuron->output[0]);

}


neuron_t *init_io_neuron(double *target, size_t target_len)
{
    neuron_t *neuron = malloc(sizeof(neuron_t));
    neuron->input = malloc(sizeof(double) * target_len);
    neuron->weight = NULL;
    neuron->output = malloc(sizeof(double) * target_len);

    neuron->input_len = target_len;
    
    memcpy(neuron->input, target, target_len * sizeof(double));
    
    return neuron;
}

neuron_t *init_neuron(size_t target_len)
{
    neuron_t *neuron = malloc(sizeof(neuron_t));
    neuron->input = malloc(sizeof(double) * target_len);
    neuron->weight = malloc(sizeof(double) * target_len);
    neuron->output = malloc(sizeof(double) * target_len);

    neuron->input_len = target_len;

    neuron->bias = rand_double();

    for (size_t i = 0; i < target_len; i++)
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
    
    free(neuron->output);
    free(neuron->weight);
    free(neuron->input);
    free(neuron);
}