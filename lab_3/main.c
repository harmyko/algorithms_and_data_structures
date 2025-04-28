#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "airport_sim.h"

int main(int argc, char *argv[])
{
    if (argc == 2 && strcmp(argv[1], "-test") == 0)
    {
        FILE *file = fopen("tests.txt", "r");
        if (!file)
        {
            perror("Failed to open tests.txt");
            return 1;
        }

        printf("Running test scenarios from tests.txt...\n\n");

        int landing_duration, takeoff_duration, max_air_time, max_steps;
        double arrival_probability;
        int test_num = 1;

        while (fscanf(file, "%d %d %d %lf %d",
                      &landing_duration, &takeoff_duration,
                      &max_air_time, &arrival_probability,
                      &max_steps) == 5)
        {
            printf("Test %d:\n", test_num++);
            printf("Landing duration: %d\n", landing_duration);
            printf("Takeoff duration: %d\n", takeoff_duration);
            printf("Max air time: %d\n", max_air_time);
            printf("Arrival probability: %.2f\n", arrival_probability);
            printf("Max steps: %d\n\n", max_steps);

            Airport *airport = create_airport(landing_duration, takeoff_duration, max_air_time, arrival_probability);
            run_simulation(airport, max_steps);
            print_simulation_results(airport);
            destroy_airport(airport);

            printf("\n----------------------------\n\n");
        }

        fclose(file);
    }
    else if (argc == 6)
    {
        int landing_duration = atoi(argv[1]);
        int takeoff_duration = atoi(argv[2]);
        int max_air_time = atoi(argv[3]);
        double arrival_probability = atof(argv[4]);
        int max_steps = atoi(argv[5]);

        if (landing_duration <= 0 || takeoff_duration <= 0 || max_air_time <= 0 || arrival_probability < 0 || arrival_probability > 1 || max_steps <= 0)
        {
            printf("Invalid arguments. Please provide positive integers and 0 <= arrival_probability <= 1.\n");
            return 1;
        }

        printf("Simulation Parameters:\n");
        printf("Landing duration: %d\n", landing_duration);
        printf("Takeoff duration: %d\n", takeoff_duration);
        printf("Max air time: %d\n", max_air_time);
        printf("Arrival probability: %.2f\n", arrival_probability);
        printf("Max steps: %d\n\n", max_steps);

        Airport *airport = create_airport(landing_duration, takeoff_duration, max_air_time, arrival_probability);
        run_simulation(airport, max_steps);
        print_simulation_results(airport);
        destroy_airport(airport);
    }
    else
    {
        printf("Usage:\n");
        printf("  %s <landing_duration> <takeoff_duration> <max_air_time> <arrival_probability> <max_steps>\n", argv[0]);
        printf("  %s -test\n", argv[0]);
        return 1;
    }

    return 0;
}
