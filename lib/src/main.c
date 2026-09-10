#include "../include/neuron.h"
#include "../include/network.h"

#include "data.c"

#include <time.h>

typedef struct
{
    size_t n_hidden_layers;
    size_t epochs;
    double learning_rate;

    char *filename;

    //todo: add features and targets?
} cliargs_t;

void handle_args(int argc, char *argv[], cliargs_t *args);

int main(int argc, char *argv[])
{

    cliargs_t args;
    handle_args(argc, argv, &args);

    // INPUT LAYER 0 weights
    size_t sample_len = 100;
    size_t features_per_sample = 3;

    double **samples = malloc(sample_len * sizeof(*samples));

    for (size_t i = 0; i < sample_len; i++) {
        samples[i] = malloc(features_per_sample * sizeof(*samples[i]));

        for (size_t j = 0; j < features_per_sample; j++) {
            samples[i][j] = X[i][j];
        }
    }

    // todo n hidden layers does not work (more epochs needed?)

    // curr neuron_per_hidden_layer must == features_per_sample
    network_t *network = init_network(args.n_hidden_layers, samples, sample_len, features_per_sample, args.epochs, args.learning_rate, y);

    time_t start_time = time(NULL);
    start_network(network);
    time_t end_time = time(NULL);

    printf("RAN for %f minutes\n", difftime(end_time, start_time)/60);

    //free_network(network);

}

void handle_args(int argc, char *argv[], cliargs_t *args)
{
    if (argc < 5)
    {
        printf("Usage: %s <n_hidden_layers> <epochs> <learning_rate> <filename>\n", argv[0]);
        exit(1);
    }

    args->n_hidden_layers = atoi(argv[1]);
    args->epochs = atoi(argv[2]);
    args->learning_rate = atof(argv[3]);
    args->filename = argv[4];
}
