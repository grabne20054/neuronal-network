#include <stdlib.h>
#include <stdbool.h>
#include "neuron.h"

typedef struct network
{
    neuron_t **neurons;
    size_t neurons_length;
    double learning_rate;

    size_t layers;

    size_t epoch;

} network_t;


void feed_forward(network_t *network);

void propagate_back(network_t *network);

double calc_error(double res_calc, double target);

void update_weights(network_t *network, double delta);

void add_to_network(network_t *network, neuron_t *neuron);


network_t *init_network(size_t layers, size_t neurons_per_layer, double *inputs, size_t input_len);