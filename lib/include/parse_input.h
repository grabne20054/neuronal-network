#pragma once

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

struct
{
    double **X;
    double *y;

    size_t sample_len;
    size_t features_per_sample;

} typedef parse_result_t;

parse_result_t load_input(const char* filename);
