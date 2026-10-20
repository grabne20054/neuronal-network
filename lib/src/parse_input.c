#include "../include/parse_input.h"

parse_result_t load_input(const char* filename)
{
    FILE *file = fopen(filename, "r");

    parse_result_t result;

    result.y = malloc(sizeof(double));

    char *line = NULL;
    size_t size = 0;
    ssize_t nread;

    size_t digits_count = 0;
    size_t line_count = 0;
    size_t feature_count = 0;
    size_t y_feature_count = 1;

    char *numb = malloc(sizeof(double));

    double *feature_target_row = malloc(sizeof(double));
    double **features_targets = malloc(sizeof(double*));

    if (file == NULL)
    {
        perror("COULD NOT READ FILE");
        exit(1);
    }

    while ((nread = getline(&line, &size, file)) != -1) {

        for (int i = 0; i < nread; i++)
        {

            if (line[i] == ',' || line[i] == '\0' || line[i] == '\n')
            {
                feature_target_row = realloc(feature_target_row, (i+1) * sizeof(double));
                
                if (i == nread-1)
                {
                    result.y = realloc(result.y, (y_feature_count)*sizeof(double));
                    result.y[y_feature_count] = atof(numb-digits_count);

                    printf("y: %f", atof(numb-digits_count));
                    y_feature_count++;
                    printf("y feature count: %zu\n", y_feature_count);
                }
                else
                {

                    feature_target_row[feature_count] = atof(numb-digits_count);

                    printf("res %zu: %f\n", feature_count, feature_target_row[feature_count]);
                    feature_count++;
                    digits_count = 0;
                }
            }
            else if (line[i] != ',')
            {
                strcpy(numb, &line[i]);
                numb++;
                digits_count++;
            }
            
        }
        result.features_per_sample = feature_count; // assuming every feature row has the same len
        feature_count = 0;

        features_targets = realloc(features_targets, (line_count+1) * sizeof(double*));
        features_targets[line_count] = malloc(sizeof(feature_target_row));
        features_targets[line_count] = feature_target_row;

        line_count++;

    }

    result.sample_len = line_count;
    result.X = features_targets;


    return result;
}