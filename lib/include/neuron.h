#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>


typedef struct
{
    double *input;
    size_t input_len;

    double *weight;
    double bias;

    double output;


} neuron_t;

double activate_function(double sum);

void perform(neuron_t *neuron, size_t len);

neuron_t *init_neuron(size_t target_len);

neuron_t *init_io_neuron(size_t target_len);

double rand_double();

void free_neuron(neuron_t *neuron);
