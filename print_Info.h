#ifndef PRINT_INFO_H
#define PRINT_INFO_H

#include "get_Time.h"
#include<stdio.h>
#include<stdint.h>
#include<time.h>
#include<stdlib.h>

void print_Info(struct tm *now, uint16_t num_sensor, uint16_t sampling, uint16_t interval);

#endif