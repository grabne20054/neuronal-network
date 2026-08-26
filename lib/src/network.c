#pragma once

#include "../include/network.h"
#include "../include/neuron.h"

void feed_forward(network_t *network)
{
    // poc --> needs to be done with n neurons --> how to connect them?
    double res = perform(network->neurons[0], 1);

    network->neurons[0]->output[0] = res;
}

void propagate_back(network_t *network)
{
    double delta = calc_error(network->neurons[0]->input[0], network->neurons[0]->output[0]);

    update_weights(network, delta);
}

double calc_error(double target, double res_calc)
{

    double err = target - res_calc;

    return err * res_calc * (1-res_calc);

}

void update_weights(network_t *network, double delta)
{
    double tmp_w = network->neurons[0]->weight[0];

    network->neurons[0]->weight[0] = tmp_w + network->learning_rate * delta * network->neurons[0]->input[0];


    double tmp_bias = network->neurons[0]->bias;

    network->neurons[0]->bias = tmp_bias - network->learning_rate * delta;

}

network_t *init_network(size_t layers, size_t neurons_per_layer, double **inputs)
{

    network_t *network = malloc(sizeof(network_t));

    for (size_t i = 0; i < layers; i++)
    {
        for (size_t j = 0; j < neurons_per_layer; j++)
        {

        }
        
    }
    

}

