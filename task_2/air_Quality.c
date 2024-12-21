#include <stdio.h>
#include<string.h>
#include "classify_Value.h"
#include"air_Quality.h"

int get_Id(char get_line[]) {
    char id[2];
    for (int i = 0; i < 3; i++) {
        if (get_line[i] == ',') return atoi(id);
        id[i] = get_line[i];
    }
}

int get_Hour(char get_line[]) {
    int count = 0;
    char hour[2];
    int j = 0;
    for (int i = 0; i < strlen(get_line) - 1; i++) {
        if (get_line[i] == ' ') {
            hour[0] = get_line[i + 1];
            hour[1] = get_line[i + 2];
            return atoi(hour);
        }
    }
}

int air_Quality(float average_dust, char pollution[]) {
    if (0 <= average_dust && average_dust < 12) {
        strcpy(pollution, "Good");
        return average_dust * 50 / 12;
    }
    else if (12 <= average_dust && average_dust < 35.5) {
        strcpy(pollution, "Moderate");
        return 50 + (50 / (35.5 - 12)) * (average_dust - 12);
    }
    else if (35.5 <= average_dust && average_dust < 55.5) {
        strcpy(pollution, "Slightly unhealthy");
        return 100 + (50 / (55.5 - 35.5)) * (average_dust - 35.5);
    }
    else if (55.5 <= average_dust && average_dust < 150.5) {
        strcpy(pollution, "Unhealthy");
        return 150 + (50 / (150.5 - 55.5)) * (average_dust - 55.5);
    }
    else if (150.5 <= average_dust && average_dust < 250.5) {
        strcpy(pollution, "Very unhealthy");
        return 200 + (100 / (250.5 - 150.5)) * (average_dust - 150.5);
    }
    else if (250.5 <= average_dust && average_dust < 350.5) {
        strcpy(pollution, "Hazardous");
        return 300 + (100 / (350.5 - 250.5)) * (average_dust - 250.5);
    }
    else if (350.5 <= average_dust && average_dust <= 550.5) {
        strcpy(pollution, "Extremely hazardous");
        return 400 + (100 / (550.5 - 350.5)) * (average_dust - 350.5);
    }
}

void print_AQI() {
    char pollution[30];
    char get_line[30];
    float sum_dust[20] = {0};
    int hour[20] = {0};
    int count[20] = {0};
    FILE *data_valid;
    FILE *dust_aqi;
    data_valid = fopen("dust_valid.csv", "r");
    dust_aqi = fopen("dust_aqi.csv","a");
    fputs("id,time,value,aqi,pollution\n", dust_aqi);
    fgets(get_line, 30, data_valid);
    int temp[20] = {get_Hour(get_line)};
    count[1] = 1;
    sum_dust[1] = get_Value(get_line);
    while (fgets(get_line, 30, data_valid)) {
        int id = get_Id(get_line);
        hour[id] = get_Hour(get_line);
        int value = get_Value(get_line);
        if (temp[id] != hour[id]) {
            float average_dust = sum_dust[id]/count[id];
            int aqi = air_Quality(average_dust, pollution);
            for (int i =0; i<13 ; i++) {
                fputc(get_line[i], dust_aqi);
            }
            fprintf(dust_aqi,"%d:00:00,%.1f,%d,%s\n",hour[id], average_dust, aqi,pollution);
            sum_dust[id] = 0;
            count[id] = 0;
        }
        sum_dust[id] = sum_dust[id] + value;
        count[id] = count[id] + 1;
        temp[id] = hour[id];
    }
    fclose(dust_aqi);
    fclose(data_valid);
}
