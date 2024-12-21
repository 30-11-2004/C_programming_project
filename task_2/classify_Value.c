#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"classify_Value.h"
#define MIN_VALUE 3.0
#define MAX_VALUE 550.5

float get_Value(char get_line[]) {
    int count = 0;
    char sensor_Value[10];
    int j = 0;
    for(int i = 0; i < strlen(get_line) - 1; i++) {
        if (get_line[i] == ',') {
            count = count + 1;
        }
        if (count == 2) {
            sensor_Value[j] = get_line[i+1];
            j = j + 1;
        }
    }
    return atof(sensor_Value);
}

void print_Classification(char name_file[]) {
    FILE *dust_outlier, *dust_valid;
    FILE *data_File;
    float sensor_Value;
    char get_line[30];
    int count = 0;
    int number_outlier = 0;
    data_File = fopen(name_file, "r");
    dust_outlier = fopen("dust_outlier.csv", "a");
    dust_valid = fopen("dust_valid.csv", "a");
    while(fgets(get_line,30,data_File)) {
       count = count + 1;
       sensor_Value = get_Value(get_line);
       if (sensor_Value < MIN_VALUE || sensor_Value > MAX_VALUE) {
        number_outlier = number_outlier + 1;
       }
       else {
        fputs(get_line, dust_valid);
       }
    }
    rewind(data_File);
    if (number_outlier == 0) {
        fclose(data_File);
        fclose(dust_outlier);
        fclose(dust_valid);
    }
    else {
        fprintf(dust_outlier, "number of outliers: %d\n", number_outlier);
        fprintf(dust_outlier, "id,time,value\n");
        fgets(get_line,30,data_File);
        while(fgets(get_line,30,data_File)) {
            sensor_Value = get_Value(get_line);
            if (sensor_Value < MIN_VALUE || sensor_Value > MAX_VALUE) {
            fputs(get_line, dust_outlier);
       }
    }
    fclose(data_File);
    fclose(dust_outlier);
    fclose(dust_valid);
}
}
