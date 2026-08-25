#include "../include/neuron.h"

double activate_function(double sum)
{
    return (1.0 / (1.0 + exp(-sum)));
}


double perform(neuron_t *neuron)
{

    size_t lenght_i = sizeof(neuron->input) / sizeof(neuron->input[0]);
    size_t lenght_w = sizeof(neuron->weight) / sizeof(neuron->weight[0]);


}