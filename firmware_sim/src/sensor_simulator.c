#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUMBER_OF_SAMPLES 10U
#define FAULT_SAMPLE_ID 5U
#define FROZEN_START_SAMPLE_ID 5U
#define FROZEN_END_SAMPLE_ID 7U
#define FROZEN_TEMPERATURE_C 25.0f


#define BASE_TEMPERATURE_C 20.0f
#define TEMPERATURE_VARIATION_C 10.0f
#define OUT_OF_RANGE_TEMPERATURE_C 85.0f



typedef enum
{
    SENSOR_MODE_NORMAL,
    SENSOR_MODE_RANGE,
    SENSOR_MODE_INVALID,
    SENSOR_MODE_FROZEN,
    SENSOR_MODE_TIMEOUT,
    SENSOR_MODE_UNSUPPORTED
} SensorMode;


static SensorMode parse_mode(const char *mode_text)
{
    if (strcmp(mode_text, "normal") == 0)
    {
        return SENSOR_MODE_NORMAL;
    }
    else if (strcmp(mode_text, "range") == 0)
    {
        return SENSOR_MODE_RANGE;
    }
    else if (strcmp(mode_text, "invalid") == 0)
    {
        return SENSOR_MODE_INVALID;
    }
    else if (strcmp(mode_text, "frozen") == 0)
    {
        return SENSOR_MODE_FROZEN;
    }
    else if (strcmp(mode_text, "timeout") == 0)
    {
        return SENSOR_MODE_TIMEOUT;
    }

    return SENSOR_MODE_UNSUPPORTED;
}


int main(int argc, char *argv[])
{
    unsigned int sample_id = 0U;
    float random_fraction = 0.0f;
    float temperature_c = 0.0f;
    const char *status = "OK";
    SensorMode mode = SENSOR_MODE_UNSUPPORTED;

    if (argc != 2)
    {
        fprintf(
            stderr,
           "Usage: %s <normal|range|invalid|frozen|timeout>\n",
            argv[0]
        );

        return EXIT_FAILURE;
    }

    mode = parse_mode(argv[1]);

   if (mode == SENSOR_MODE_UNSUPPORTED)
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

        if ((mode == SENSOR_MODE_TIMEOUT) &&
    (sample_id == FAULT_SAMPLE_ID))
        {
        continue;
        }

        else if ((mode == SENSOR_MODE_RANGE) &&
         (sample_id == FAULT_SAMPLE_ID))
        {
            temperature_c = OUT_OF_RANGE_TEMPERATURE_C;
            status = "RANGE_FAULT";
        }
       else if ((mode == SENSOR_MODE_INVALID) &&
         (sample_id == FAULT_SAMPLE_ID))
        {
            printf("%u,INVALID,INVALID_DATA\n", sample_id);
            continue;
        }

      else if ((mode == SENSOR_MODE_FROZEN) &&
         (sample_id >= FROZEN_START_SAMPLE_ID) &&
         (sample_id <= FROZEN_END_SAMPLE_ID))
        {
            temperature_c = FROZEN_TEMPERATURE_C;
            status = "FROZEN_FAULT";
        }



        printf("%u,%.2f,%s\n", sample_id, temperature_c, status);
    }

    return EXIT_SUCCESS;
}