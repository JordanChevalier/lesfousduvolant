#ifndef __STRATEGIE_H__
#define __STRATEGIE_H__

const char *calcul_prochaine_action();
const char *generate_get_sensors();
void analyse_sensors(const char *line);
extern float sensor_time;
extern int sensor_exploration;

#endif /* __STRATEGIE_H__ */