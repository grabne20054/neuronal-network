#include "../include/neuron.h"
#include "../include/network.h"
#include "../include/preprocessing.h"

#include "data.c"

#include <time.h>

typedef struct
{
    size_t n_hidden_layers;
    size_t epochs;
    double learning_rate;
    bool train; // if true, train the network, if false, load the network from file

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

    char *filename = args.filename;

    if (args.train)
    {
        network_t *network = init_network(args.n_hidden_layers, samples, sample_len, features_per_sample, args.epochs, args.learning_rate, y);
        normalize(network);
        // todo save median iqr into network since prediction values should be normalized too
        time_t start_time = time(NULL);
        train_network(network);
        time_t end_time = time(NULL);

        printf("RAN for %f minutes\n", difftime(end_time, start_time)/60);


        // save trained network
        filename = save_network(network);
        free_network(network);
    }
    else
    {
        printf("Loading network from file...\n");
    }

    
    network_t *loaded_network = load_network(filename);

    if (loaded_network)
    {
        printf("Network loaded successfully!\n");
    }
    else
    {
        printf("Failed to load network.\n");
        return 1;
    }

    double output = predict(loaded_network, prediction);
    printf("Prediction for sample [1.0, 0.0, 0.0]: %f\n", output);

}

void handle_args(int argc, char *argv[], cliargs_t *args)
{
    if (argc < 6)
    {
        printf("Usage: %s <hlayers> <e> <lr> <train> <filename>\n", argv[0]);
        exit(1);
    }

    args->n_hidden_layers = atoi(argv[1]);
    args->epochs = atoi(argv[2]);
    args->learning_rate = atof(argv[3]);
    args->train = atoi(argv[4]);
    args->filename = argv[5];
}
