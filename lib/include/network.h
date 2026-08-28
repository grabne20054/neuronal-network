#include <stdlib.h>
#include <stdbool.h>
#include "neuron.h"
#include "layer.h"

typedef struct
{
    double learning_rate;

    size_t epoch;

    layer_t **layers;
    size_t layers_length;

    double target;

} network_t;


void feed_forward(network_t *network);

void propagate_back(network_t *network);

double calc_error(double res_calc, double target);

void update_weights(double delta, neuron_t *neuron, double learning_rate);

void add_to_network(network_t *network, layer_t *layer);

network_t *init_network(size_t layers, size_t neurons_per_layer, double *inputs, size_t input_len, size_t epoch, double learning_rate, double target);

void start_network(network_t *network);
