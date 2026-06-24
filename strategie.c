#include "strategie.h"
#include <stdio.h>
#include <string.h>

/* ================= CAPTEURS ================= */

int sensor_time = 0;
int sensor_exploration = 1;

int sensor_x = 0;
int sensor_y = 0;
int sensor_orientation = 0;
int sensor_speed = 0;

int sensor_front = 0;
int sensor_right = 0;
int sensor_rear = 0;
int sensor_left = 0;

/* ================= ETAT ================= */

static int init = 1;
static int last_action_accel = 0;
static int last_blocked = 0;

/* ================= PARSING ================= */

static int is_sensor_line(const char *line)
{
    return (line[0] >= '0' && line[0] <= '9');
}

void analyse_sensors(const char *line)
{
    if (!is_sensor_line(line))
    {
        if (strcmp(line, "BLOCKED") == 0)
            last_blocked = 1;
        else
            last_blocked = 0;
        return;
    }

    /* parsing avec SCALE x100 */
    float t, x, y, o, s, f, r, b, l;
    int exp;

    sscanf(line, "%f %d %f %f %f %f %f %f %f %f", &t, &exp, &x, &y, &o, &s, &f, &r, &b, &l);

    sensor_time = (int)(t * 100);
    sensor_exploration = exp;

    sensor_x = (int)(x * 100);
    sensor_y = (int)(y * 100);
    sensor_orientation = (int)(o * 100);
    sensor_speed = (int)(s * 100);

    sensor_front = (int)(f * 100);
    sensor_right = (int)(r * 100);
    sensor_rear = (int)(b * 100);
    sensor_left = (int)(l * 100);
}

/* ================= RESET ================= */

void reset_strategy()
{
    init = 1;
    last_action_accel = 0;
    last_blocked = 0;
}

/* ================= SECURITE ================= */

static const char *avoidance()
{
    if (sensor_front <= 30)
        return "DECELERATE";

    if (sensor_front <= 80)
        return "DECELERATE";

    return NULL;
}

/* ================= PILOTAGE ================= */

static const char *drive()
{
    /* ================= BLOCKED HANDLING ================= */

    if (last_blocked)
    {
        last_blocked = 0;
        return "TURN_LEFT";
    }

    /* ================= VITESSE FIXE ================= */

    if (sensor_speed > 40)
    {
        last_action_accel = 0;
        return "DECELERATE";
    }

    /* ================= ANTI BOUCLE ACCEL ================= */

    if (sensor_speed < 30 && !last_action_accel)
    {
        last_action_accel = 1;
        return "ACCELERATE";
    }

    if (sensor_speed < 20)
        last_action_accel = 0;

    /* ================= DIRECTION ================= */

    if (sensor_front < 120)
    {
        if (sensor_right > sensor_left)
            return "TURN_RIGHT";
        else
            return "TURN_LEFT";
    }

    if (sensor_right > 100)
        return "TURN_RIGHT";

    if (sensor_front > 120)
        return "ACCELERATE";

    return "TURN_LEFT";
}

/* ================= MAIN ================= */

const char *calcul_prochaine_action()
{
    if (init)
    {
        init = 0;
        return "GET_SENSORS";
    }

    const char *safe = avoidance();
    if (safe)
        return safe;

    return drive();
}