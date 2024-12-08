#ifndef GET_TIME_H
#define GET_TIME_H

#include<stdio.h>
#include<stdint.h>
#include<time.h>
#include<stdlib.h>

void get_Start_Time(struct tm *start_Time, uint16_t interval ); 

void mark_Timeline(struct tm* now, uint16_t sampling);

#endif




