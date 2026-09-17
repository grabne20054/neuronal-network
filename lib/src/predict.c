#include "../include/neuron.h"
#include "../include/network.h"
#include "../include/preprocessing.h"

#include "data.c"

#include <time.h>

typedef struct
{
    char *filename;

    double *prediction_sample;

    //todo: add features and targets?
} cliargs_t;

void handle_args(int argc, char *argv[], cliargs_t *args);

int main(int argc, char *argv[])
{

    cliargs_t args;
    handle_args(argc, argv, &args);

    network_t *loaded_network = load_network(args.filename);

    if (loaded_network)
    {
        printf("Network loaded successfully!\n");
    }
    else
    {
        printf("Failed to load network.\n");
        exit(1);
    }

    if (argc-2 != (int)loaded_network->features_per_sample)
    {
        printf("Not enough / to much prediction features passed!\n");
        exit(1);
    }
    

    double output = predict(loaded_network, prediction); // always returning same value
    printf("Prediction: %f\n", output);
    
}

void handle_args(int argc, char *argv[], cliargs_t *args)
{
    if (argc < 3)
    {
        printf("Usage: %s <f> <prediction sample n features>\n", argv[0]);
        exit(1);
    }

    args->filename = argv[1];
    printf("args filename: %s\n", args->filename);

    for (size_t i = 2; i < (size_t)argc; i++)
    {
        args->prediction_sample[(uint)i-2] = atof(argv[i]);
    }
    
}
