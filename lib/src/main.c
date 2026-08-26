#include "../include/neuron.h"
#include "../include/network.h"

int main(void)
{
    neuron_t *neuron = malloc(sizeof(neuron_t));

    neuron->bias = 0;
    neuron->input = malloc(sizeof(double));
    neuron->weight = malloc(sizeof(double));
    neuron->output = malloc(sizeof(double));

    neuron->input[0] = 0.0;
    neuron->weight[0] = 0.2;

    network_t *network = malloc(sizeof(network_t));

    network->neurons = malloc(sizeof(neuron_t *));

    network->neurons[0] = neuron;
    network->epoch = 200000000;

    network->learning_rate = 0.2;

    for (size_t i = 0; i < network->epoch; i++)
    {
        feed_forward(network);
        propagate_back(network);

        printf("%f\n", network->neurons[0]->output[0]);

    }



    // end
    free(network->neurons);
    free(network);

    free(neuron->output);
    free(neuron->weight);
    free(neuron->input);

}