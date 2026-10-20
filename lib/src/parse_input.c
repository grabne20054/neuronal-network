#include "../include/parse_input.h"

double **load_input(const char* filename)
{
    FILE *file = fopen(filename, "r");

    char *line = NULL;
    size_t size = 0;
    ssize_t nread;

    size_t digits_count = 0;
    size_t line_count = 0;
    size_t feature_count = 0;

    char *numb = malloc(sizeof(double));

    double *feature_target_row = malloc(sizeof(double));
    double **features_targets = malloc(sizeof(double*));

    if (file == NULL)
    {
        perror("COULD NOT READ FILE");
        return 1;
    }

    while ((nread = getline(&line, &size, file)) != -1) {

        for (size_t i = 0; i < nread; i++)
        {

            if (line[i] == ',' || line[i] == '\0' || line[i] == '\n')
            {
                feature_target_row = realloc(feature_target_row, (i+1) * sizeof(double));
                feature_target_row[feature_count] = atof(numb-digits_count);
                printf("res %zu: %f\n", feature_count, feature_target_row[feature_count]);
                feature_count++;
                digits_count = 0;
            }
            else if (line[i] != ',')
            {
                strcpy(numb, &line[i]);
                numb++;
                digits_count++;
            }
            
        }
        feature_count = 0;

        features_targets = realloc(features_targets, (line_count+1) * sizeof(double*));
        features_targets[line_count] = malloc(sizeof(feature_target_row));
        features_targets[line_count] = feature_target_row;

        line_count++;

    }

    return features_targets;
}