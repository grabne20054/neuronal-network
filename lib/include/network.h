#include <stdlib.h>
#include <neuron.h>

typedef struct network
{
    neuron_t *neurons;
    double learning_rate;

    uint16_t epoch;

} network_t;


void feed_forward(network_t *network);

void propagate_back(network_t *network);

void calc_error(network_t *network);

void update_weights(network *network);