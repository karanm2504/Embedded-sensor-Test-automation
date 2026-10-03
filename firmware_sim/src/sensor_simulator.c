#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUMBER_OF_SAMPLES 10U
#define FAULT_SAMPLE_ID 5U

#define BASE_TEMPERATURE_C 20.0f
#define TEMPERATURE_VARIATION_C 10.0f
#define OUT_OF_RANGE_TEMPERATURE_C 85.0f

int main(int argc, char *argv[])
{
    unsigned int sample_id = 0U;
    float random_fraction = 0.0f;
    float temperature_c = 0.0f;
    const char *status = "OK";

    if (argc != 2)
    {
        fprintf(
            stderr,
            "Usage: %s <normal|range|invalid>\n",
            argv[0]
        );

        return EXIT_FAILURE;
    }

    if ((strcmp(argv[1], "normal") != 0) &&
        (strcmp(argv[1], "range") != 0) &&
        (strcmp(argv[1], "invalid") != 0))
    {
        fprintf(
            stderr,
            "Error: unsupported mode '%s'\n",
            argv[1]
        );

        return EXIT_FAILURE;
    }

    srand(42U);

    printf("sample_id,temperature_c,status\n");

    for (sample_id = 1U;
         sample_id <= NUMBER_OF_SAMPLES;
         sample_id++)
    {
        random_fraction = (float)rand() / (float)RAND_MAX;

        temperature_c =
            BASE_TEMPERATURE_C +
            (random_fraction * TEMPERATURE_VARIATION_C);

        status = "OK";

        if ((strcmp(argv[1], "range") == 0) &&
            (sample_id == FAULT_SAMPLE_ID))
        {
            temperature_c = OUT_OF_RANGE_TEMPERATURE_C;
            status = "RANGE_FAULT";
        }
        else if ((strcmp(argv[1], "invalid") == 0) &&
                 (sample_id == FAULT_SAMPLE_ID))
        {
            printf("%u,INVALID,INVALID_DATA\n", sample_id);
            continue;
        }

        printf("%u,%.2f,%s\n", sample_id, temperature_c, status);
    }

    return EXIT_SUCCESS;
}