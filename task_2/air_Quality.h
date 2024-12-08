#ifndef AIR_QUALITY_H
#define AIR_QUALITY_H

#include <stdio.h>
#include<string.h>
#include "classify_Value.h"

int get_Id(char get_line[]);

int get_Hour(char get_line[]);

int air_Quality(float average_dust, char pollution[]);

void print_AQI();
#endif