#include "../include/neuron.h"

double activate_function(double sum)
{
    return (1.0 / (1.0 + exp(-sum)));
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