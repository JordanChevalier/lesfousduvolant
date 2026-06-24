#ifndef __STRATEGIE_H__
#define __STRATEGIE_H__

/* ================= CAPTEURS (INT SCALE x100) ================= */

extern int sensor_time;
extern int sensor_exploration;

extern int sensor_x;
extern int sensor_y;
extern int sensor_orientation;
extern int sensor_speed;

extern int sensor_front;
extern int sensor_right;
extern int sensor_rear;
extern int sensor_left;

/* ================= API ================= */

const char *calcul_prochaine_action();
void analyse_sensors(const char *line);

/* ================= RESET ================= */

void reset_strategy();

#endif