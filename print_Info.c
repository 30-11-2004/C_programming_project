#include "get_Time.h"
#include<stdio.h>
#include<stdint.h>
#include<time.h>
#include<stdlib.h>

void print_Info(struct tm *now, uint16_t num_sensor, uint16_t sampling, uint16_t interval) {
    FILE* dust_sensor;
    dust_sensor = fopen("dust_sensor.csv", "a");
    fputs("id,time,value\n",dust_sensor);
    srand(time(NULL));
    float sensor_Value;
    int num_loop;
    num_loop = interval*3600/sampling;
    for (int j=1; j <= num_sensor; j++) {
        get_Start_Time(now, interval);
        sensor_Value = (float)rand()*800 / RAND_MAX;
        fprintf(dust_sensor, "%d,%4d:%0.2d:%0.2d %0.2d:%0.2d:%0.2d,%3.1f\n", j, now->tm_year + 1900, now->tm_mon + 1, now->tm_mday, now->tm_hour, now->tm_min, now->tm_sec, sensor_Value);
    }
    for (int i=2; i <= num_loop; i++) {
        mark_Timeline(now, sampling);
        for (int j=1; j <= num_sensor; j++) {
            sensor_Value = (float)rand()*800 / RAND_MAX;
            fprintf(dust_sensor, "%d,%4d:%0.2d:%0.2d %0.2d:%0.2d:%0.2d,%3.1f\n", j, now->tm_year + 1900, now->tm_mon + 1, now->tm_mday, now->tm_hour, now->tm_min, now->tm_sec, sensor_Value);
        }
    }
    fclose(dust_sensor);
}

