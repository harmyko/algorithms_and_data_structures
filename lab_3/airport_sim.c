#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "airport_sim.h"

Plane *create_plane(PlaneType type, int max_air_time)
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
    srand(time(NULL));
    return airport;
}

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

void run_simulation(Airport *airport, int max_steps)
{
    for (int step = 0; step < max_steps; step++)
    {
        double chance = (double)rand() / RAND_MAX;
        if (chance < airport->arrival_probability)
        {
            PlaneType type = (rand() % 2 == 0) ? LANDING : TAKEOFF;
            Plane *new_plane = create_plane(type, airport->max_air_time);
            if (type == LANDING)
                enqueue(airport->landing_queue, new_plane, 0);
            else
                enqueue(airport->takeoff_queue, new_plane, 1);
        }

        int landing_size = getQueueSize(airport->landing_queue);
        int takeoff_size = getQueueSize(airport->takeoff_queue);

        for (int i = 0; i < landing_size; i++)
        {
            Plane *plane = (Plane *)peekAt(airport->landing_queue, i);
            plane->wait_time++;
            if (plane->fuel_time_left > 0)
                plane->fuel_time_left--;
        }

        for (int i = 0; i < takeoff_size; i++)
        {
            Plane *plane = (Plane *)peekAt(airport->takeoff_queue, i);
            plane->wait_time++;
        }

        for (int i = 0; i < landing_size; i++)
        {
            Plane *plane = (Plane *)peekAt(airport->landing_queue, i);
            if (plane->fuel_time_left == 0)
            {
                Plane *crashed = (Plane *)removeAt(airport->landing_queue, i);
                free(crashed);
                landing_size--;
                i--;
            }
        }

        if (airport->runway_busy_time == 0)
        {
            if (!isEmpty(airport->landing_queue))
            {
                Plane *plane = (Plane *)pop(airport->landing_queue);
                airport->runway_busy_time = airport->landing_duration;
                airport->landed_planes++;
                BigInteger *wait = createBigIntegerFromInt(plane->wait_time);
                BigInteger *new_total = addTwoBigIntegers(airport->total_landing_wait, wait);
                freeBigInteger(airport->total_landing_wait);
                freeBigInteger(wait);
                airport->total_landing_wait = new_total;
                if (plane->wait_time > airport->max_landing_wait)
                {
                    airport->max_landing_wait = plane->wait_time;
                }
                free(plane);
            }
            else if (!isEmpty(airport->takeoff_queue))
            {
                Plane *plane = (Plane *)pop(airport->takeoff_queue);
                airport->runway_busy_time = airport->takeoff_duration;
                airport->took_off_planes++;
                BigInteger *wait = createBigIntegerFromInt(plane->wait_time);
                BigInteger *new_total = addTwoBigIntegers(airport->total_takeoff_wait, wait);
                freeBigInteger(airport->total_takeoff_wait);
                freeBigInteger(wait);
                airport->total_takeoff_wait = new_total;
                if (plane->wait_time > airport->max_takeoff_wait)
                {
                    airport->max_takeoff_wait = plane->wait_time;
                }
                free(plane);
            }
        }

        if (airport->runway_busy_time > 0)
            airport->runway_busy_time--;
    }
}

void print_simulation_results(const Airport *airport)
{
    printf("Simulation Results:\n");
    if (airport->landed_planes > 0)
    {
        printf("Landing planes:\n");
        printf("- Max wait time: %d\n", airport->max_landing_wait);
        printf("- Average wait time: ");
        BigInteger *landed = createBigIntegerFromInt(airport->landed_planes);
        printf("%f\n", divideBigIntegers(airport->total_landing_wait, landed));
        freeBigInteger(landed);
    }
    else
        printf("No planes landed.\n");

    if (airport->took_off_planes > 0)
    {
        printf("Takeoff planes:\n");
        printf("- Max wait time: %d\n", airport->max_takeoff_wait);
        printf("- Average wait time: ");
        BigInteger *tookoff = createBigIntegerFromInt(airport->took_off_planes);
        printf("%f\n", divideBigIntegers(airport->total_takeoff_wait, tookoff));
        freeBigInteger(tookoff);
    }
    else
        printf("No planes took off.\n");
}

void print_airport_details(Airport *airport)
{
    if (!airport)
    {
        printf("Airport is NULL.\n");
        return;
    }

    // Print the PriorityQueue sizes (if they are not NULL)
    printf("Landing Queue Size: %lld\n", airport->landing_queue ? airport->landing_queue->size : 0);
    printf("Takeoff Queue Size: %lld\n", airport->takeoff_queue ? airport->takeoff_queue->size : 0);

    // Print the integer fields
    printf("Runway Busy Time: %d\n", airport->runway_busy_time);
    printf("Landing Duration: %d\n", airport->landing_duration);
    printf("Takeoff Duration: %d\n", airport->takeoff_duration);
    printf("Max Air Time: %d\n", airport->max_air_time);
    printf("Arrival Probability: %.2f\n", airport->arrival_probability);

    // Print the BigInteger fields
    printf("Total Landing Wait Time: ");
    printBigInteger(airport->total_landing_wait);
    printf("\n");

    printf("Total Takeoff Wait Time: ");
    printBigInteger(airport->total_takeoff_wait);
    printf("\n");

    // Print the other integer fields
    printf("Landed Planes: %d\n", airport->landed_planes);
    printf("Took Off Planes: %d\n", airport->took_off_planes);
    printf("Max Landing Wait: %d\n", airport->max_landing_wait);
    printf("Max Takeoff Wait: %d\n", airport->max_takeoff_wait);
}

void print_plane_details(Plane *plane)
{
    if (plane == NULL)
    {
        printf("Error: Plane is NULL.\n");
        return;
    }

    // Print the plane's type
    if (plane->type == LANDING)
    {
        printf("Plane Type: LANDING\n");
    }
    else
    {
        printf("Plane Type: TAKEOFF\n");
    }

    // Print the wait time
    printf("Wait Time: %d\n", plane->wait_time);

    // Print the fuel time left (only for landing planes)
    if (plane->type == LANDING)
    {
        printf("Fuel Time Left: %d\n", plane->fuel_time_left);
    }
    else
    {
        printf("Fuel Time Left: N/A (Not relevant for takeoff)\n");
    }
}
