#include <stdio.h>
#include <stdlib.h>

#define NUMBER_OF_SAMPLES 10U
#define BASE_TEMPERATURE_C 20.0f
#define TEMPERATURE_VARIATION_C 10.0f

int main(void)
{
    unsigned int sample_id = 0U;
    float random_fraction = 0.0f;
    float temperature_c = 0.0f;

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

        printf("%u,%.2f,OK\n", sample_id, temperature_c);
    }

    return EXIT_SUCCESS;
}