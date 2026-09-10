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

    int* targets;

    size_t features_per_sample;

} network_t;


void feed_forward(network_t *network, double *sample);

void propagate_back(network_t *network, double target);
void compute_delta(network_t *network, double target);

double calc_error(double target, double output);

void update_weights(neuron_t *neuron, double learning_rate);

void add_to_network(network_t *network, layer_t *layer);

network_t *init_network(size_t hidden_layers, double **samples, size_t sample_len, size_t features_per_sample, size_t epoch, double learning_rate, int* targets);

void start_network(network_t *network);

void free_network(network_t *network);
