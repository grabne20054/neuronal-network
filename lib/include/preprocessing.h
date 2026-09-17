#include "network.h"

typedef struct
{
    double *medians;
    double *iqr;

} preprocessing_t;


void normalize(network_t *network);

void get_medians_and_iqrs(double *samples, size_t samples_len, preprocessing_t *data, size_t j);

void normalize_prediction_sample(network_t *network, double *prediction_sample);
