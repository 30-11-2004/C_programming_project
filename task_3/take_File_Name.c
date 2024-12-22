#include<stdio.h>
#include "take_File_Name.h"

int name_File(int argc, char** argv, char *data_file[], char *hex_file[]) {
        if (argc == 3) {
                *data_file = argv[1];
                *hex_file = argv[2];
                return 1;
        }
        else {
                FILE *error_File;
                error_File = fopen("task3.log", "a");
                fputs("Error 01: file not found or cannot be accessed", error_File);
                fclose(error_File);
                return 0;
        }
} 