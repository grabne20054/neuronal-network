#include "../include/layer.h"

void add_to_layer(layer_t *layer, neuron_t *neuron)
{
    layer->neurons_list = realloc(layer->neurons_list, (layer->neurons_list_lenght + 1) * sizeof(*layer->neurons_list));
    layer->neurons_list[layer->neurons_list_lenght++] = neuron;

}

layer_t *init_layer(size_t neurons_len)
{
    layer_t *layer = malloc(sizeof(layer_t));

    layer->neurons_list = malloc(sizeof(neuron_t *) * neurons_len);
    layer->neurons_list_lenght = neurons_len;

    layer->i = false;
    layer->o = false;

    layer->output = malloc(sizeof(double) * neurons_len);
    
    return layer;
}

void save_layer(layer_t *layer, FILE *file, size_t features_per_sample)
{
    if (file == NULL)
    {
        return;
    }

    fwrite(&layer->i, sizeof(layer->i), 1, file);
    fwrite(&layer->o, sizeof(layer->o), 1, file);
    
    fwrite(&layer->neurons_list_lenght, sizeof(layer->neurons_list_lenght), 1, file);

    if (layer->o)
    {
        fwrite(layer->output, sizeof(*layer->output), 1, file);
    }
    else
    {
        fwrite(layer->output, sizeof(*layer->output), features_per_sample, file);
    }

    for (size_t i = 0; i < layer->neurons_list_lenght; i++)
    {
        save_neuron(layer->neurons_list[i], file);
    }
    
}


void load_layer(layer_t *layer, FILE *file, size_t features_per_sample)
{
    fread(&layer->i, sizeof(bool), 1, file);
    printf("layer->i %d\n", layer->i);

    fread(&layer->o, sizeof(bool), 1, file);
    printf("layer->o %d\n", layer->o);

    fread(&layer->neurons_list_lenght, sizeof(size_t), 1, file);
    printf("layer->neurons_list_lenght %zu\n", layer->neurons_list_lenght);

    layer->neurons_list = malloc(sizeof(neuron_t) * layer->neurons_list_lenght);

    if (layer->o)
    {
        layer->output = malloc(sizeof(*layer->output));
        fread(layer->output, sizeof(*layer->output), 1, file);
        printf("layer->output[0] %f\n", layer->output[0]);


    }
    else
    {
        layer->output = malloc(features_per_sample * sizeof(*layer->output));
        fread(layer->output, sizeof(*layer->output), features_per_sample, file);
        printf("layer->output[0] %f\n", layer->output[0]);
    }

    for (size_t i = 0; i < layer->neurons_list_lenght; i++)
    {
        neuron_t *neuron = malloc(sizeof(neuron_t));
        load_neuron(neuron, file, layer->i);
        layer->neurons_list[i] = neuron;
    }
    

}