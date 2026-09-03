#include <stdlib.h>
#include <stdbool.h>
#include "neuron.h"
#include "layer.h"

typedef struct
{
    double **samples;
    size_t samples_len;

    double learning_rate;

    size_t epoch;

    layer_t **layers;
    size_t layers_length;

    double target;

} network_t;


void feed_forward(network_t *network, double *sample);

void propagate_back(network_t *network);

double calc_error(double res_calc, double target);

void update_weights(double delta, neuron_t *neuron, double learning_rate);

void add_to_network(network_t *network, layer_t *layer);

network_t *init_network(size_t hidden_layers, size_t neurons_per_hidden_layer, double **samples, size_t sample_len, size_t features_per_sample, size_t epoch, double learning_rate, double target);

void start_network(network_t *network);
