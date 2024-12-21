#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"air_Quality.h"
#include"statistic_Aqi.h"

int get_Aqi_Value(char get_Line[]) {
    int count = 0;
    char value[5];
    int j = 0;
    for ( int i = 0; i < strlen(get_Line); i++) {
        if (get_Line[i] == ',') {
            count = count + 1;
        }
        if (count == 3 && get_Line[i] != ',') {
            value[j] = get_Line[i];
            j = j + 1;
        }
        if (count == 4) {
            value[j] = '\0';
            return atoi(value);
        }
    }
}

void aqi_Statistic(FILE *fptr, int statistic[20][8]) {
    char get_Line[50];
    int id = 0;
    int value = 0;
    int column = 0;
    while(fgets(get_Line, 50, fptr)) {
        id = get_Id(get_Line);
        value = get_Aqi_Value(get_Line);
        if (0 <= value && value < 50) column = 0;
        if (50 <= value && value < 100) column = 1;
        if (100 <= value && value < 150) column = 2;
        if (150 <= value && value < 200) column = 3;
        if (200 <= value && value < 300) column = 4;
        if (300 <= value && value < 400) column = 5;
        if (400 <= value && value < 500) column = 6;
        statistic[id][column]++;
    }
}

int number_senser(FILE *fptr) {
    char get_Line[50];
    int count = 1;
    int id = 0;
    fgets(get_Line, 50, fptr);
    while(fgets(get_Line, 50, fptr)) {
        id = get_Id(get_Line);
        if (id == 1) return count;
        count = count + 1;
    }
}

void print_Aqi_Statistic() {
    FILE *dust_Aqi;
    FILE *dust_Statistic;
    int statistic[20][8] = {0};
    dust_Aqi = fopen("dust_aqi.csv", "r");
    dust_Statistic = fopen("dust_statistic.csv", "a");
    aqi_Statistic(dust_Aqi, statistic);
    rewind(dust_Aqi);
    fputs("id,pollution,duảtion", dust_Statistic);
    for (int row = 1; row <= number_senser(dust_Aqi); row++) {
        fprintf(dust_Statistic, "%d,%s,%d\n", row, "Good", statistic[row][0]);
        fprintf(dust_Statistic, "%d,%s,%d\n", row, "Moderate", statistic[row][1]);
        fprintf(dust_Statistic, "%d,%s,%d\n", row, "Slightly unhealthy", statistic[row][2]);
        fprintf(dust_Statistic, "%d,%s,%d\n", row, "Unhealthy", statistic[row][3]);
        fprintf(dust_Statistic, "%d,%s,%d\n", row, "Very unhealthy", statistic[row][4]);
        fprintf(dust_Statistic, "%d,%s,%d\n", row, "Hazardous", statistic[row][5]);
        fprintf(dust_Statistic, "%d,%s,%d\n", row, "Extremely hazardous", statistic[row][6]);
    }
    fclose(dust_Aqi);
    fclose(dust_Statistic);
}