#ifndef GET_INPUT_H
#define GET_INPUT_H

#include<stdio.h>
#include<ctype.h>
#include<string.h>
#include<stdlib.h>

int check_Number(char position[]);

int get_Input(int argc, char* argv[], int* num_sensor, int * sampling, int* interval);

#endif
