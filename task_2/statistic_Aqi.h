#ifndef STATISTIC_AQI_H
#define STATISTIC_AQI_H

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"air_Quality.h"

int get_Aqi_Value(char get_Line[]);

void aqi_Statistic(FILE *fptr, int statistic[20][8]);

int number_senser(FILE *fptr);

void print_Aqi_Statistic();

#endif