#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <math.h>


typedef struct neuron
{
    double *input;

    double *weight;
    int bias;

    double *output;

} neuron_t;

double activate_function(double sum);

double perform(neuron_t *neuron, size_t len);