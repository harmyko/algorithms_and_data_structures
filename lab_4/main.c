#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "flight_graph.h"

void printUsage(char *programName)
{
    fprintf(stderr, "Usage: %s [-|filename] [-test]\n", programName);
    fprintf(stderr, "Options:\n");
    fprintf(stderr, "  filename: Read from specified file\n");
    fprintf(stderr, "  -test   : Run built-in test cases\n");
    fprintf(stderr, "Input format:\n");
    fprintf(stderr, "First line: start_city destination_city\n");
    fprintf(stderr, "Following lines: city1 city2 departure_time duration (one flight per line)\n");
    fprintf(stderr, "  departure_time format: HH:MM (24-hour format)\n");
    fprintf(stderr, "  duration: time in minutes\n");
}

void runDefaultTest()
{
    printf("=== Running Default Test ===\n");
    FlightGraph graph;
    init_graph(&graph);

    add_flight(&graph, "Vilnius", "Kaunas", time_to_minutes("08:00"), 45);
    add_flight(&graph, "Vilnius", "Ryga", time_to_minutes("09:30"), 60);
    add_flight(&graph, "Kaunas", "Klaipeda", time_to_minutes("10:15"), 50);
    add_flight(&graph, "Ryga", "Klaipeda", time_to_minutes("11:00"), 40);
    add_flight(&graph, "Klaipeda", "Talinas", time_to_minutes("13:30"), 75);
    add_flight(&graph, "Kaunas", "Talinas", time_to_minutes("12:45"), 120);

    printf("\nCurrent Flight Network:\n");
    printf("----------------------\n");
    for (int i = 0; i < graph.count; i++)
    {
        printf("%-15s -> ", graph.cities[i].name);

        Flight *flight = graph.cities[i].flights;
        if (!flight)
        {
            printf("No direct flights");
        }
        else
        {
            int first = 1;
            while (flight)
            {
                char departure[10], arrival[10];
                minutes_to_time(flight->departure_time, departure);
                minutes_to_time(flight->departure_time + flight->duration, arrival);

                if (!first)
                    printf(", ");
                printf("%s (%s, %dmin)",
                       graph.cities[flight->destination].name,
                       departure,
                       flight->duration);
                first = 0;
                flight = flight->next;
            }
        }
        printf("\n");
    }
    printf("----------------------\n\n");

    int route[MAX_CITIES];
    int route_length;
    int total_duration;

    total_duration = find_fastest_route(&graph, "Vilnius", "Talinas", route, &route_length);
    if (total_duration != -1)
    {
        printf("Fastest route from Vilnius to Talinas takes %d minutes:\n", total_duration);
        for (int i = 0; i < route_length; i++)
        {
            printf("%s", graph.cities[route[i]].name);
            if (i < route_length - 1)
                printf(" -> ");
        }
        printf("\n\n");
    }
    else
    {
        printf("No route found between Vilnius and Talinas\n\n");
    }

    total_duration = find_fastest_route(&graph, "Ryga", "Kaunas", route, &route_length);
    if (total_duration != -1)
    {
        printf("Fastest route from Ryga to Kaunas takes %d minutes:\n", total_duration);
        for (int i = 0; i < route_length; i++)
        {
            printf("%s", graph.cities[route[i]].name);
            if (i < route_length - 1)
                printf(" -> ");
        }
        printf("\n");
    }
    else
    {
        printf("No route found between Ryga and Kaunas\n");
    }

    free_graph(&graph);
}

void runCustomTest(FILE *input)
{
    printf("=== Running Custom Test ===\n");
    FlightGraph graph;
    init_graph(&graph);

    char startCity[MAX_NAME_LENGTH], endCity[MAX_NAME_LENGTH];
    char city1[MAX_NAME_LENGTH], city2[MAX_NAME_LENGTH];
    char departureStr[10];
    int duration;

    if (fscanf(input, "%s %s", startCity, endCity) != 2)
    {
        fprintf(stderr, "Error reading start and destination cities\n");
        return;
    }

    while (fscanf(input, "%s %s %s %d", city1, city2, departureStr, &duration) == 4)
    {
        int departureTime = time_to_minutes(departureStr);
        add_flight(&graph, city1, city2, departureTime, duration);
    }

    printf("\nCurrent Flight Network:\n");
    printf("----------------------\n");
    for (int i = 0; i < graph.count; i++)
    {
        printf("%-15s -> ", graph.cities[i].name);

        Flight *flight = graph.cities[i].flights;
        if (!flight)
        {
            printf("No direct flights");
        }
        else
        {
            int first = 1;
            while (flight)
            {
                char departure[10], arrival[10];
                minutes_to_time(flight->departure_time, departure);
                minutes_to_time(flight->departure_time + flight->duration, arrival);

                if (!first)
                    printf(", ");
                printf("%s (%s, %dmin)",
                       graph.cities[flight->destination].name,
                       departure,
                       flight->duration);
                first = 0;
                flight = flight->next;
            }
        }
        printf("\n");
    }
    printf("----------------------\n\n");

    int route[MAX_CITIES];
    int route_length;
    int total_duration = find_fastest_route(&graph, startCity, endCity, route, &route_length);

    if (total_duration == -1)
    {
        printf("No route found between %s and %s\n", startCity, endCity);
    }
    else
    {
        printf("Fastest route from %s to %s takes %d minutes:\n", startCity, endCity, total_duration);
        for (int i = 0; i < route_length; i++)
        {
            printf("%s", graph.cities[route[i]].name);
            if (i < route_length - 1)
                printf(" -> ");
        }
        printf("\n");
    }

    free_graph(&graph);
}

int main(int argc, char *argv[])
{
    if (argc == 1)
    {
        printUsage(argv[0]);
        return EXIT_FAILURE;
    }

    if (strcmp(argv[1], "-test") == 0)
    {
        runDefaultTest();

        printf("\n=== Additional Test Cases ===\n");
        FlightGraph testGraph;
        init_graph(&testGraph);
        add_flight(&testGraph, "London", "Paris", time_to_minutes("08:30"), 80);
        add_flight(&testGraph, "Paris", "Berlin", time_to_minutes("10:15"), 110);
        add_flight(&testGraph, "Berlin", "Rome", time_to_minutes("13:00"), 140);

        printf("\nCurrent Flight Network:\n");
        printf("----------------------\n");
        for (int i = 0; i < testGraph.count; i++)
        {
            printf("%-15s -> ", testGraph.cities[i].name);

            Flight *flight = testGraph.cities[i].flights;
            if (!flight)
            {
                printf("No direct flights");
            }
            else
            {
                int first = 1;
                while (flight)
                {
                    char departure[10], arrival[10];
                    minutes_to_time(flight->departure_time, departure);
                    minutes_to_time(flight->departure_time + flight->duration, arrival);

                    if (!first)
                        printf(", ");
                    printf("%s (%s, %dmin)",
                           testGraph.cities[flight->destination].name,
                           departure,
                           flight->duration);
                    first = 0;
                    flight = flight->next;
                }
            }
            printf("\n");
        }
        printf("----------------------\n\n");

        int route[MAX_CITIES];
        int route_length;
        int total_duration = find_fastest_route(&testGraph, "London", "Rome", route, &route_length);

        if (total_duration != -1)
        {
            printf("Fastest route from London to Rome takes %d minutes:\n", total_duration);
            for (int i = 0; i < route_length; i++)
            {
                printf("%s", testGraph.cities[route[i]].name);
                if (i < route_length - 1)
                    printf(" -> ");
            }
            printf("\n");
        }
        else
        {
            printf("No route found between London and Rome\n");
        }

        free_graph(&testGraph);

        return EXIT_SUCCESS;
    }

    FILE *input = stdin;
    if (strcmp(argv[1], "-") != 0)
    {
        input = fopen(argv[1], "r");
        if (input == NULL)
        {
            fprintf(stderr, "Error: Could not open file %s\n", argv[1]);
            return EXIT_FAILURE;
        }
    }

    runCustomTest(input);

    if (input != stdin)
    {
        fclose(input);
    }

    return EXIT_SUCCESS;
}