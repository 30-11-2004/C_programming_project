#include<stdio.h>
#include<ctype.h>
#include<string.h>
#include<stdlib.h>

int check_Number(char position[]) {
    for (int i=0; i<strlen(position); i++) {
        if (isdigit(position[i])==0) return 0;
    }
    return 1;
}

int get_Input(int argc, char* argv[], int* num_sensor, int * sampling, int* interval) {
    if (argc == 1) {
        *num_sensor = 1;
        *sampling = 60;
        *interval = 24;
    }
    else
    {
        if (check_Number(argv[1])) {
            printf("ERROR_INPUT!");
            return 0;
        }
        for (int i = 1; i < (argc-1); i++) {
            if (check_Number(argv[i]) && check_Number(argv[i+1]) || !check_Number(argv[i]) && !check_Number(argv[i+1])) {
                printf("ERROR_INPUT!");
                return 0;
            }
        }
        if (argc == 7) {
            *num_sensor = atoi(argv[2]);
            *sampling = atoi(argv[4]);
            *interval = atoi(argv[6]);
            return 1;
        }
        else if (argc == 5) {
            if (strcmp(argv[1],"-n") == 0) {
                *num_sensor = atoi(argv[2]);
                if (strcmp(argv[3],"-st") == 0) {
                    *sampling = atoi(argv[4]);
                    *interval = 24;
                    return 1;
                }
                else {
                    *sampling = 60;
                    *interval = atoi(argv[4]);
                    return 1;
                }
            }
            else {
                *num_sensor = 1;
                *sampling = atoi(argv[2]);
                *interval = atoi(argv[4]);
                return 1;
            }
        }
        else if (argc == 3) {
            if (strcmp(argv[1],"-n") == 0){
                *num_sensor = atoi(argv[2]);
                *sampling = 60;
                *interval = 24;
                return 1;
            }
            else if (strcmp(argv[1],"-st") == 0){
                *num_sensor = 1;
                *sampling = atoi(argv[2]);
                *interval = 24;
                return 1;
            }

            else {
                *num_sensor = 1;
                *sampling = 60;
                *interval = atoi(argv[2]);
                return 1;
            }
        }
        else {
            printf("ERROR_INPUT!");
            return 0;
        }
        if (*num_sensor < 1 || *sampling < 10 || *interval < 1) {
            printf("ERROR_INPUT!");
            return 0;
        }
   }
}

