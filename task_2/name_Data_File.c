#include<stdio.h>
#include"name_Data_File.h"

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
        FILE *error_File;
        error_File = fopen("task2.log", "a");
        fputs("Error 03: invalid command", error_File);
        fclose(error_File);
        return 0;
    }
} 
