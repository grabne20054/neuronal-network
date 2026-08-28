#include "../include/neuron.h"
#include "../include/network.h"

int main(void)
{

    // INPUT LAYER 0 weights

    double input_arr[1] = {0.0, 0.5};

    size_t input_length = sizeof(input_arr) / sizeof(input_arr[0]);

    network_t *network = init_network(3, 50, input_arr, input_length, 300, 0.05, 1);

    start_network(network);

}