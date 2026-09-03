#include "../include/layer.h"

void add_to_layer(layer_t *layer, neuron_t *neuron)
{
    layer->neurons_list = realloc(layer->neurons_list, (layer->neurons_list_lenght + 1) * sizeof(*layer->neurons_list));
    layer->neurons_list[layer->neurons_list_lenght++] = neuron;

}

layer_t *init_layer(size_t neurons_len, size_t features_per_sample)
{
    layer_t *layer = malloc(sizeof(layer_t));

    layer->neurons_list = malloc(sizeof(neuron_t *) * neurons_len);
    layer->neurons_list_lenght = neurons_len;

    layer->io = false;

    layer->output = malloc(sizeof(double) * features_per_sample);
    
    return layer;
}