#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>


typedef struct neuron
{
    double *input;

    double *weight;
    double bias;

    double *output;

    size_t layer;

    struct neuron **next_layer_neurons;
    size_t next_layer_neurons_length;


} neuron_t;

double activate_function(double sum);

double perform(neuron_t *neuron, size_t len);

neuron_t *init_neuron(double *target, size_t target_len, size_t layer);

double rand_double();

void free_neuron(neuron_t *neuron);

void connect(neuron_t *parent, neuron_t *child);