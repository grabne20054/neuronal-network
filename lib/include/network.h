#include <stdlib.h>
#include "neuron.h"

typedef struct network
{
    neuron_t **neurons;
    double learning_rate;

    size_t epoch;

} network_t;


void feed_forward(network_t *network);

void propagate_back(network_t *network);

double calc_error(double res_calc, double target);

void update_weights(network_t *network);