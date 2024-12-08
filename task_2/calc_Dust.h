#ifndef CALC_DUST_H
#define CALC_DUST_H

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"classify_Value.h"
#include"air_Quality.h"

struct interval_Time {
    int hour;
    int minute;
    int second;
};

void interval(struct interval_Time *si, int interval_Sec);

int get_Interval_Sec(FILE *fptr);

void take_Value(FILE *fptr, float dust_Value[20][20000], int *len_Column);

void sort_data(float dust_Value[20][20000], int len_Column);

int median(float dust_Value[20][20000], int len_Column, int id);

int mean(float dust_Value[20][20000], int len_Column, int id) ;

void print_Summary(char name_file[]);

#endif