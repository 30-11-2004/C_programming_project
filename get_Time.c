#include<stdio.h>
#include<stdint.h>
#include<time.h>
#include<stdlib.h>

void get_Start_Time(struct tm *start_Time, uint16_t interval ) {
    time_t cur_Time = time(NULL);
    cur_Time = cur_Time - interval*3600;
    struct tm *temp_Time = localtime(&cur_Time);
    *start_Time = *temp_Time;
}

void mark_Timeline(struct tm* now, uint16_t sampling) {
    time_t cur_Time = mktime(now) + sampling;
    struct tm *temp_Time = localtime(&cur_Time);
    *now = *temp_Time;
}





