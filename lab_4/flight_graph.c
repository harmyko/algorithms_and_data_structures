#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>

#include "flight_graph.h"

void init_graph(FlightGraph *graph)
{
    graph->count = 0;
}

int find_or_add_city(FlightGraph *graph, const char *name)
{
    for (int i = 0; i < graph->count; i++)
    {
        if (strcmp(graph->cities[i].name, name) == 0)
        {
            return i;
        }
    }

    if (graph->count < MAX_CITIES)
    {
        strcpy(graph->cities[graph->count].name, name);
        graph->cities[graph->count].flights = NULL;
        return graph->count++;
    }

    return -1; 
}

void add_flight(FlightGraph *graph, const char *from, const char *to, int departure_time, int duration)
{
    int from_index = find_or_add_city(graph, from);
    int to_index = find_or_add_city(graph, to);

    if (from_index == -1 || to_index == -1)
    {
        printf("Cannot add flight, graph is full\n");
        return;
    }

    Flight *new_flight = (Flight *)malloc(sizeof(Flight));
    if (new_flight == NULL)
    {
        printf("Memory allocation failed\n");
        return;
    }

    new_flight->destination = to_index;
    new_flight->departure_time = departure_time;
    new_flight->duration = duration;

    new_flight->next = graph->cities[from_index].flights;
    graph->cities[from_index].flights = new_flight;
}

int time_to_minutes(const char *time_str)
{
    int hours, minutes;
    sscanf(time_str, "%d:%d", &hours, &minutes);
    return hours * 60 + minutes;
}

void minutes_to_time(int minutes, char *time_str)
{
    int hours = minutes / 60;
    int mins = minutes % 60;
    sprintf(time_str, "%02d:%02d", hours, mins);
}

int find_fastest_route(FlightGraph *graph, const char *from, const char *to,
                       int *route, int *route_length)
{
    int start_index = -1;
    int end_index = -1;

    for (int i = 0; i < graph->count; i++)
    {
        if (strcmp(graph->cities[i].name, from) == 0)
        {
            start_index = i;
        }
        if (strcmp(graph->cities[i].name, to) == 0)
        {
            end_index = i;
        }
    }

    if (start_index == -1 || end_index == -1)
    {
        return -1; 
    }

    int *visited = (int *)malloc(graph->count * sizeof(int));
    Path *paths = (Path *)malloc(graph->count * sizeof(Path));

    if (!visited || !paths)
    {
        printf("Memory allocation failed\n");
        free(visited);
        free(paths);
        return -1;
    }

    for (int i = 0; i < graph->count; i++)
    {
        visited[i] = 0;
        paths[i].total_duration = INT_MAX;
        paths[i].previous_city = -1;
    }

    paths[start_index].total_duration = 0;
    paths[start_index].arrival_time = 0;

    // Dijkstra's algorithm
    for (int count = 0; count < graph->count; count++)
    {
        int min_duration = INT_MAX;
        int current = -1;

        for (int i = 0; i < graph->count; i++)
        {
            if (!visited[i] && paths[i].total_duration < min_duration)
            {
                min_duration = paths[i].total_duration;
                current = i;
            }
        }

        if (current == -1 || current == end_index)
            break;

        visited[current] = 1;

        Flight *flight = graph->cities[current].flights;
        while (flight)
        {
            int dest = flight->destination;

            int new_duration = paths[current].total_duration + flight->duration;

            if (new_duration < paths[dest].total_duration)
            {
                paths[dest].total_duration = new_duration;
                paths[dest].arrival_time = flight->departure_time + flight->duration;
                paths[dest].previous_city = current;
                paths[dest].city_index = dest;
            }

            flight = flight->next;
        }
    }

    if (paths[end_index].total_duration == INT_MAX)
    {
        free(visited);
        free(paths);
        return -1;
    }

    int temp_route[MAX_CITIES];
    int temp_length = 0;
    int current = end_index;

    while (current != -1)
    {
        temp_route[temp_length++] = current;
        current = paths[current].previous_city;
    }

    *route_length = temp_length;
    for (int i = 0; i < temp_length; i++)
    {
        route[i] = temp_route[temp_length - 1 - i];
    }

    int total_duration = paths[end_index].total_duration;

    free(visited);
    free(paths);

    return total_duration;
}

void free_graph(FlightGraph *graph)
{
    for (int i = 0; i < graph->count; i++)
    {
        Flight *current = graph->cities[i].flights;
        while (current)
        {
            Flight *temp = current;
            current = current->next;
            free(temp);
        }
    }
}