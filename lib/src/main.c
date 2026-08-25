#include "../include/neuron.h"
#include "../include/network.h"

int main(void)
{
    neuron_t *neuron = malloc(sizeof(neuron_t));


    neuron->bias = 0;
    neuron->input[0] = 1.0;

    neuron->weight[0] = 0.5;

    network_t *network = malloc(sizeof(network_t));


    network->neurons[0] = neuron;

    feed_forward(network);

}