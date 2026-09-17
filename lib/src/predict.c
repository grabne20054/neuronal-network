#include "../include/neuron.h"
#include "../include/network.h"
#include "../include/preprocessing.h"

#include "data.c"

#include <time.h>

typedef struct
{
    char *filename;

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
        return 1;
    }

    double output = predict(loaded_network, prediction);
    printf("Prediction for sample [1.0, 0.0, 0.0]: %f\n", output);
    
}

void handle_args(int argc, char *argv[], cliargs_t *args)
{
    if (argc < 2)
    {
        printf("Usage: %s <f>\n", argv[0]);
        exit(1);
    }

    args->filename = argv[1];
}
