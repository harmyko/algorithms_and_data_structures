#include <stdio.h>
#include <stdlib.h>
#include "airport_sim.h"

int main()
{
    // Simulation settings
    int landing_duration = 3;         // time units needed to land
    int takeoff_duration = 2;         // time units needed to take off
    int max_air_time = 5;             // max time a plane can stay in air
    double arrival_probability = 0.7; // probability of new plane arrival each step
    int max_steps = 1000;             // number of simulation steps

    // Create airport
    Airport *airport = create_airport(landing_duration, takeoff_duration, max_air_time, arrival_probability);

    // Run the simulation
    run_simulation(airport, max_steps);

    // Print results
    print_simulation_results(airport);

    // Clean up memory
    destroy_airport(airport);

    return 0;
}
