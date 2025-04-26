#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "airport_sim.h"

// Internal helper to create a new plane
static Plane *create_plane(PlaneType type, int max_air_time)
{
    Plane *plane = (Plane *)malloc(sizeof(Plane));
    if (!plane)
    {
        perror("Failed to allocate Plane");
        exit(EXIT_FAILURE);
    }
    plane->type = type;
    plane->wait_time = 0;
    plane->fuel_time_left = (type == LANDING) ? max_air_time : -1;
    return plane;
}

// Create and initialize the airport
Airport *create_airport(int landing_duration, int takeoff_duration, int max_air_time, double arrival_probability)
{
    Airport *airport = (Airport *)malloc(sizeof(Airport));
    if (!airport)
    {
        perror("Failed to allocate Airport");
        exit(EXIT_FAILURE);
    }

    airport->landing_queue = newPriorityQueue();
    airport->takeoff_queue = newPriorityQueue();
    airport->runway_busy_time = 0;
    airport->landing_duration = landing_duration;
    airport->takeoff_duration = takeoff_duration;
    airport->max_air_time = max_air_time;
    airport->arrival_probability = arrival_probability;
    airport->total_landing_wait = createBigIntegerFromInt(0);
    airport->total_takeoff_wait = createBigIntegerFromInt(0);
    airport->landed_planes = 0;
    airport->took_off_planes = 0;
    airport->max_landing_wait = 0;
    airport->max_takeoff_wait = 0;

    srand(time(NULL)); // Seed for random plane generation

    return airport;
}

// Free all memory related to the airport
void destroy_airport(Airport *airport)
{
    if (!airport)
        return;

    freePriorityQueue(airport->landing_queue);
    freePriorityQueue(airport->takeoff_queue);
    freeBigInteger(airport->total_landing_wait);
    freeBigInteger(airport->total_takeoff_wait);

    free(airport);
}

// Run the simulation
void run_simulation(Airport *airport, int max_steps)
{
    for (int step = 0; step < max_steps; step++)
    {
        // 1. Random chance to create a new plane
        double chance = (double)rand() / RAND_MAX;
        if (chance < airport->arrival_probability)
        {
            // Decide randomly whether it's landing or takeoff
            PlaneType type = (rand() % 2 == 0) ? LANDING : TAKEOFF;
            Plane *new_plane = create_plane(type, airport->max_air_time);
            if (type == LANDING)
            {
                enqueue(airport->landing_queue, new_plane, 0); // Landing planes have priority
            }
            else
            {
                enqueue(airport->takeoff_queue, new_plane, 1); // Takeoff planes have less priority
            }
        }

        // 2. Handle existing planes (wait times, fuel burning, etc.)
        // TODO: Implement increment wait times, check for crashes

        // 3. If runway free, start a new landing or takeoff
        if (airport->runway_busy_time == 0)
        {
            if (!isEmpty(airport->landing_queue))
            {
                // Start landing
                Plane *plane = (Plane *)pop(airport->landing_queue);
                airport->runway_busy_time = airport->landing_duration;
                airport->landed_planes++;
                addTwoBigIntegers(airport->total_landing_wait, createBigIntegerFromInt(plane->wait_time));
                if (plane->wait_time > airport->max_landing_wait)
                {
                    airport->max_landing_wait = plane->wait_time;
                }
                free(plane);
            }
            else if (!isEmpty(airport->takeoff_queue))
            {
                // Start takeoff
                Plane *plane = (Plane *)pop(airport->takeoff_queue);
                airport->runway_busy_time = airport->takeoff_duration;
                airport->took_off_planes++;
                addTwoBigIntegers(airport->total_takeoff_wait, createBigIntegerFromInt(plane->wait_time));
                if (plane->wait_time > airport->max_takeoff_wait)
                {
                    airport->max_takeoff_wait = plane->wait_time;
                }
                free(plane);
            }
        }

        // 4. Decrease busy time of runway
        if (airport->runway_busy_time > 0)
        {
            airport->runway_busy_time--;
        }
    }
}

// Print the simulation results
void print_simulation_results(const Airport *airport)
{
    printf("Simulation Results:\n");

    if (airport->landed_planes > 0)
    {
        printf("Landing planes:\n");
        printf("- Max wait time: %d\n", airport->max_landing_wait);
        printf("- Average wait time: ");
        printf("%f\n", divideBigIntegers(airport->total_landing_wait, createBigIntegerFromInt(airport->landed_planes)));
    }
    else
    {
        printf("No planes landed.\n");
    }

    if (airport->took_off_planes > 0)
    {
        printf("Takeoff planes:\n");
        printf("- Max wait time: %d\n", airport->max_takeoff_wait);
        printf("- Average wait time: ");
        printf("%f\n", divideBigIntegers(airport->total_takeoff_wait, createBigIntegerFromInt(airport->took_off_planes)));
    }
    else
    {
        printf("No planes took off.\n");
    }
}
