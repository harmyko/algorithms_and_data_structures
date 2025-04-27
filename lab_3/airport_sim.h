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
    int wait_time;      // How many steps the plane has waited
    int fuel_time_left; // For landing planes: how much fuel is left
} Plane;

typedef struct
{
    PriorityQueue *landing_queue; // Priority queue for landing planes
    PriorityQueue *takeoff_queue; // Priority queue for takeoff planes
    int runway_busy_time;         // How much time left until runway becomes free
    int landing_duration;         // Time needed for landing
    int takeoff_duration;         // Time needed for takeoff
    int max_air_time;             // Maximum air time (fuel limit)
    double arrival_probability;   // Probability of a plane arriving each step

    BigInteger *total_landing_wait; // Sum of all landing wait times
    BigInteger *total_takeoff_wait; // Sum of all takeoff wait times

    int landed_planes;    // How many planes landed
    int took_off_planes;  // How many planes took off
    int max_landing_wait; // Max wait for landing
    int max_takeoff_wait; // Max wait for takeoff
} Airport;

// Airport simulation API
Airport *create_airport(int landing_duration, int takeoff_duration, int max_air_time, double arrival_probability);
void destroy_airport(Airport *airport);
void run_simulation(Airport *airport, int max_steps);
void print_simulation_results(const Airport *airport);
void print_airport_details(Airport *airport);
void print_airplane_details(Plane *plane);

#endif // AIRPORT_SIM_H
