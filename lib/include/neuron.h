#pragma once
#include <stdlib.h>
#include <stdio.h>
#include <math.h>


typedef struct neuron
{
    double *input;

    double *weight;
    double bias;

    double *output;

    size_t layer;


} neuron_t;

double activate_function(double sum);

double perform(neuron_t *neuron, size_t len);