#include "../include/neuron.h"
#include "../include/network.h"

int main(void)
{

    // INPUT LAYER 0 weights

    double input_arr[1] = {1.0};

    size_t input_length = sizeof(input_arr) / sizeof(input_arr[0]);

    printf("%ld\n", input_length);

    network_t *network = init_network(3, 3, input_arr, input_length);

    printf("%ld\n", network->neurons_length);

    for (size_t i = 0; i < network->neurons_length; i++)
    {
        free_neuron(network->neurons[i]);
    }
    

    /*for (size_t i = 0; i < network->epoch; i++)
    {
        feed_forward(network);
        propagate_back(network);

        printf("%f\n", network->neurons[0]->output[0]);

    }*/



    // end
    /*free(network->neurons);
    free(network);

    free(neuron->output);
    free(neuron->weight);
    free(neuron->input);*/

}