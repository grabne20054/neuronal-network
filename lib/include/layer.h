#include "neuron.h"

typedef struct
{

    neuron_t **neurons_list;
    size_t neurons_list_lenght;

    double *output;

    bool io;

} layer_t;


void add_to_layer(layer_t *layer, neuron_t *neuron);

layer_t *init_layer(size_t neurons_len, size_t features_per_sample);