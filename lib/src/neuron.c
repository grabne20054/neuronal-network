#include "../include/neuron.h"

double activate_function(double sum)
{
    return (1.0 / (1.0 + exp(-sum)));

    if (sum > 0)
    {
        return 1;
    }
    return 0;
    
}


void perform(neuron_t *neuron, size_t len)
{
    if (neuron->weight == NULL) // indicate neuron is io
    {
        //neuron->output = neuron->input;
        printf("IO NEURON EXIT\n");
        return;
    }

    double sum = 0;

    for (size_t i = 0; i < len; i++)
    {
        sum += (neuron->input[i] * neuron->weight[i]);
    }

    sum += neuron->bias;

    double acv = activate_function(sum);

    neuron->output = acv;
    //printf("neuron output: %f\n", neuron->output);

}


neuron_t *init_io_neuron(size_t features_per_sample)
{
    neuron_t *neuron = malloc(sizeof(neuron_t));
    neuron->input = malloc(sizeof(double) * features_per_sample);
    neuron->weight = NULL;
    neuron->output = 0;

    neuron->input_len = features_per_sample;
    
    return neuron;
}

neuron_t *init_neuron(size_t features_per_sample)
{
    neuron_t *neuron = malloc(sizeof(neuron_t));
    neuron->input = malloc(sizeof(double) * features_per_sample);
    neuron->weight = malloc(sizeof(double) * features_per_sample);
    neuron->output = 0;

    neuron->input_len = features_per_sample;

    neuron->bias = 0.0;

    for (size_t i = 0; i < features_per_sample; i++)
    {
        neuron->weight[i] = rand_double();
        printf("WEIGHT: %f\n", neuron->weight[i]);
    }
    
    return neuron;
}


double rand_double()
{
    return (((double)rand() / RAND_MAX) * 2.0 - 1.0) * 0.1;
}


void free_neuron(neuron_t *neuron)
{
    if (!neuron) {return;}
    
    free(neuron->weight);
    free(neuron->input);
    free(neuron);
}


void save_neuron(neuron_t *neuron, FILE *file)
{
    if (file == NULL)
    {
        return;
    }

    fwrite(&neuron->input_len, sizeof(neuron->input_len), 1, file);
    fwrite(&neuron->bias, sizeof(neuron->bias), 1, file);
    fwrite(&neuron->output, sizeof(neuron->output), 1, file);
    fwrite(&neuron->delta, sizeof(neuron->delta), 1, file);
    

    fwrite(neuron->input, sizeof(*neuron->input), neuron->input_len, file);

    if (neuron->weight != NULL)
    {
      fwrite(neuron->weight, sizeof(*neuron->weight), neuron->input_len, file);

    }
    
}

void load_neuron(neuron_t *neuron, FILE *file, bool i)
{
    if (file == NULL)
    {
        return;
    }

    fread(&neuron->input_len, sizeof(size_t), 1, file);
    printf("neuron->input_len %zu\n", neuron->input_len);
    fread(&neuron->bias, sizeof(double), 1, file);
    printf("neuron->bias %f\n", neuron->bias);
    fread(&neuron->output, sizeof(double), 1, file);
    printf("neuron->output %f\n", neuron->output);
    fread(&neuron->delta, sizeof(double), 1, file);
    printf("neuron->delta %f\n", neuron->delta);

    neuron->input = malloc(sizeof(double) * neuron->input_len);
    fread(neuron->input, sizeof(*neuron->input), neuron->input_len, file);
    printf("neuron->input[0] %f\n", neuron->input[0]);


    if (i != 1)
    {
        neuron->weight = malloc(sizeof(*neuron->weight) * neuron->input_len);
        fread(neuron->weight, sizeof(*neuron->weight), neuron->input_len, file);
        printf("neuron->weight[0] %f\n", neuron->weight[0]);
    }

}
