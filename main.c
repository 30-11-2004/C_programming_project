#include "get_Input.h"
#include "get_Time.h"
#include "print_Info.h"
#include<stdio.h>
#include<time.h>
#include<stdlib.h>
#include<stdint.h>

int main(int argc, char* argv[]) {
    int num_sensor, sampling, interval;
    get_Input(argc, argv, &num_sensor, &sampling, &interval);
    struct tm start_Time;
    print_Info(&start_Time, num_sensor, sampling, interval);
    return 1;
}