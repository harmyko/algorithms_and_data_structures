#ifndef AIRPORT_SIM_H
#define AIRPORT_SIM_H

#include "BigInteger.h"    // Author: emsa0885
#include "priorityQueue.h" // Author: ugva1377

typedef enum
{
    LANDING,
    TAKEOFF
} PlaneType;

typedef struct
{
    PlaneType type;
    int wait_time;
    int fuel_time_left;
} Plane;

typedef struct
{
    PriorityQueue *landing_queue;
    PriorityQueue *takeoff_queue;
    int runway_busy_time;
    int landing_duration;
    int takeoff_duration;
    int max_air_time;
    double arrival_probability;

    BigInteger *total_landing_wait;
    BigInteger *total_takeoff_wait;

    int landed_planes;
    int took_off_planes;
    int max_landing_wait;
    int max_takeoff_wait;
} Airport;

Airport *create_airport(int landing_duration, int takeoff_duration, int max_air_time, double arrival_probability);
void destroy_airport(Airport *airport);
void run_simulation(Airport *airport, int max_steps);
void print_simulation_results(const Airport *airport);
void print_airport_details(Airport *airport);
void print_plane_details(Plane *plane);

#endif // AIRPORT_SIM_H
