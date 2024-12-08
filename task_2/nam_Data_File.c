#include<stdio.h>

int name_Data_File(int argc, char** argv, char *name_file[]) {
    if (argc == 1) {
        *name_file = "dust_sensor.csv";
        return 1;
    }
    else if (argc == 2) {
        *name_file = argv[1];
        return 1;
    }
    else {
        printf("ERROR_INPUT!");
        return 1;
    }
} 
