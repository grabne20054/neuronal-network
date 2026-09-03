#include "../include/neuron.h"
#include "../include/network.h"

int main(void)
{

    // INPUT LAYER 0 weights

    size_t sample_len = 3;
    size_t features_per_sample = 3;

    double init[3][3] = {
        {0.1, 0.5, 0.7},
        {0.3, 0.4, 0.6},
        {0.7, 0.4, 0.1}
    };

    double **samples = malloc(sample_len * sizeof(*samples));

    for (size_t i = 0; i < sample_len; i++) {
        samples[i] = malloc(features_per_sample * sizeof(*samples[i]));

        for (size_t j = 0; j < features_per_sample; j++) {
            samples[i][j] = init[i][j];
        }
    }

    network_t *network = init_network(1, 2, samples, sample_len, features_per_sample, 1, 0.5, 0);

    start_network(network);

}