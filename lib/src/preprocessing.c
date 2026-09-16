#include "../include/preprocessing.h"

void normalize(network_t *network)
{
    size_t j = 0;
    double sample_arr[network->samples_len];

    preprocessing_t *data = malloc(sizeof(preprocessing_t));
    data->medians = malloc(sizeof(double) * network->features_per_sample);
    data->iqr = malloc(sizeof(double) * network->features_per_sample);

    while (j < network->features_per_sample)
    {
        
        for (size_t i = 0; i < network->samples_len; i++)
        {
           sample_arr[i] = network->samples[i][j];
        
        }
        
        get_medians_and_iqrs(sample_arr, network->samples_len, data, j); 

        printf("median[%zu]: %f iqr[%zu]: %f\n", j, data->medians[j], j, data->iqr[j]);
        j++;
    }


    for (size_t i = 0; i < network->samples_len; i++)
    {
        for (size_t j = 0; j < network->features_per_sample; j++)
        {
            printf("x: %f\n", network->samples[i][j]); 

            if (data->iqr[j] != 0.0)
            {
                network->samples[i][j] =
                    (network->samples[i][j] - data->medians[j])
                    / data->iqr[j];
            }
            else
            {
                network->samples[i][j] = 0.0;
            }
            printf("x_scaled: %f\n", network->samples[i][j]); 
        }

    }
    
    

    free(data->medians);
    free(data->iqr);
    free(data);

}

int compare( const void* a, const void* b)
{
    double double_a = * ( (double*) a );
    double double_b = * ( (double*) b );
    
    if ( double_a == double_b ) return 0;
    else if ( double_a < double_b ) return -1;
    else return 1;
}

void get_medians_and_iqrs(double *samples, size_t samples_len, preprocessing_t *data, size_t j)
{
    if (samples_len == 0)
        return;

    qsort(samples, samples_len, sizeof *samples, compare);

    /* Median */
    if (samples_len % 2 == 0)
    {
        data->medians[j] =
            (samples[samples_len / 2 - 1] +
             samples[samples_len / 2]) / 2.0;
    }
    else
    {
        data->medians[j] = samples[samples_len / 2];
    }

    /* Q1 and Q3 */
    size_t mid = samples_len / 2;

    double q1;
    double q3;

    if (samples_len % 2 == 0)
    {
        q1 = (samples[mid / 2 - 1] +
              samples[mid / 2]) / 2.0;

        q3 = (samples[mid + mid / 2 - 1] +
              samples[mid + mid / 2]) / 2.0;
    }
    else
    {
        q1 = samples[mid / 2];

        q3 = samples[mid + 1 + mid / 2];
    }

    data->iqr[j] = q3 - q1;
}
