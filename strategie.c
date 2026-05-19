#include "strategie.h"

float sensor_time;
int sensor_exploration;

const char *calcul_prochaine_action()
{
    return generate_get_sensors();
}

const char *generate_get_sensors()
{
    return "GET_SENSORS";
}

void analyse_sensors(const char *line)
{
    sensor_time = 33.70;
    sensor_exploration = 1;
}
