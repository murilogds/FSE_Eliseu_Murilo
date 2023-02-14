#ifndef PWM_H
#define PWM_H

#include "cJSON.h"

void start_pwm();

void pwm_set_value(int value);

int pwm_get_value();

#endif