#include<stdio.h>
#include "take_File_Name.h"

int name_File(int argc, char** argv, char *data_file[], char *hex_file[]) {
        *data_file = argv[1];
        *hex_file = argv[2];
} 