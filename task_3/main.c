#include<stdio.h>
#include"take_File_Name.h"
#include"convert_Data.h"

int main(int argc, char* argv[]) {
    char *data_File[30];
    char *hex_File[30];
    struct frame frame_1;
    if(name_File(argc, argv, data_File, hex_File) == 0) return 0;
    convert_Data(&frame_1, *data_File, *hex_File);
    return 1;
}