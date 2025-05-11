#define MAX_CITIES 100
#define MAX_NAME_LENGTH 50

typedef struct Flight
{
    int destination;
    int departure_time;
    int duration;
    struct Flight *next;
} Flight;

typedef struct
{
    char name[MAX_NAME_LENGTH];
    Flight *flights;
} City;

typedef struct
{
    int city_index;
    int arrival_time;
    int total_duration;
    int previous_city;
} Path;

typedef struct
{
    City cities[MAX_CITIES];
    int count;
} FlightGraph;

void init_graph(FlightGraph *graph);

int find_or_add_city(FlightGraph *graph, const char *name);

void add_flight(FlightGraph *graph, const char *source_city_name, const char *target_city_name,
                int departure_time, int duration);

int time_to_minutes(const char *time_str);

void minutes_to_time(int minutes, char *time_str);

int find_fastest_route(FlightGraph *graph, const char *source_city_name, const char *target_city_name,
                        int *route, int *route_length);

void free_graph(FlightGraph *graph);