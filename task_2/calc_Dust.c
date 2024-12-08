#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"classify_Value.h"
#include"air_Quality.h"

struct interval_Time {
    int hour;
    int minute;
    int second;
};

void interval(struct interval_Time *si, int interval_Sec) {
    si->hour = interval_Sec/3600;
    si->minute = (interval_Sec%3600) / 60;
    si->second = (interval_Sec%3600) % 60;
}

int get_Interval_Sec(FILE *fptr) {
    int id;
    float value;
    int hour, min, sec, year, mon, day;
    int start_Time, after_Time;
    char get_Line[30];
    int count = 0;
    fscanf(fptr, "%s", &get_Line);
    fscanf(fptr, "%d,%d:%d:%d %d:%d:%d,%f" , &id, &year, &mon, &day, &hour, &min, &sec, &value);
    start_Time = day*3600*24 + hour*3600 + 60*min + sec;
    while(fscanf(fptr, "%d,%d:%d:%d %d:%d:%d,%f", &id, &year, &mon, &day, &hour, &min, &sec, &value)) {
        if (id == 1) {
            after_Time = day*3600*24 + hour*3600 + 60*min + sec;
            break;
        }
    }
    int step_Time = after_Time - start_Time;
    rewind(fptr);
    fscanf(fptr, "%s", &get_Line);
    while (fgets(get_Line, 30, fptr)) {
        if (get_Id(get_Line) == 1) count = count + 1;
    }
    return step_Time * (count - 1);
}

void take_Value(FILE *fptr, float dust_Value[20][20000], int *len_Column) {
    char get_Line[30];
    int id = 1;
    float value;
    int column_index[20] = {0};
    while(fgets(get_Line, 30, fptr)) {
        id = get_Id(get_Line);
        value = get_Value(get_Line);
        int cur_index = column_index[id];
        dust_Value[id][cur_index] = value;
        column_index[id] = column_index[id] + 1;
    }
    *len_Column = column_index[1];
}

void sort_data(float dust_Value[20][20000], int len_Column) {
    int row = 1;
    int column = 0;
    while(dust_Value[row][0] != 0) {
        for (column; column < (len_Column - 1); column++) {
            for (int i = column + 1; i < len_Column; i++) {
                if (dust_Value[row][column] > dust_Value[row][i]) {
                    float temp = dust_Value[row][column];
                    dust_Value[row][column] = dust_Value[row][i];
                    dust_Value[row][i] = temp;
                }
            }
        }
     row = row + 1;
    }
}

int median(float dust_Value[20][20000], int len_Column, int id) {
    if (len_Column % 2 == 0) return dust_Value[id][len_Column/2];
    else return (dust_Value[id][len_Column/2] + dust_Value[id][len_Column/2 + 1])/2;
}

int mean(float dust_Value[20][20000], int len_Column, int id) {
    double sum = 0.0;
    for (int i = 0; i<len_Column; i++) {
        sum = sum + dust_Value[id][i];
    }
    return sum/len_Column;
}

void print_Summary(char name_file[]) {
    FILE *dust_Summary;
    FILE *dust_Valid;
    FILE *dust_Sensor;
    struct interval_Time si;
    int interval_Sec;
    float dust_Value[20][20000] = {0};
    int len_Column;
    char get_Line[30];
    dust_Valid = fopen("dust_valid.csv", "r");
    dust_Summary = fopen("dust_summary.csv", "a");
    dust_Sensor = fopen(name_file, "r");
    fputs("id,parameter,time,value\n", dust_Summary);
    take_Value(dust_Valid, dust_Value, &len_Column);
    rewind(dust_Valid);
    interval_Sec = get_Interval_Sec(dust_Sensor);
    interval(&si, interval_Sec);
    sort_data(dust_Value, len_Column);
    int row = 1;
    int id = 0;
    float value = 0.0;
    while (dust_Value[row][0] != 0) {
        while (fgets(get_Line, 30, dust_Valid)) {
            id = get_Id(get_Line);
            value = get_Value(get_Line);
            if (id == row && value == dust_Value[row][len_Column - 1]) {
                char time[30];
                int count = 0;
                int j = 0;
                for (int i = 0; i < strlen(get_Line); i++) {
                    if (get_Line[i] == ',') count = count +1;
                    if (count == 1 && get_Line[i] != ',') {
                        time[j] = get_Line[i];
                        j++;
                    }
                    if (count == 2) {
                        time[j] = '\0';
                        break;
                    }

                }
                fprintf(dust_Summary, "%d,max,%s,%.1f\n", row, time, value);
                rewind(dust_Valid);
                break;
            }
        }
         while (fgets(get_Line, 30, dust_Valid)) {
            id = get_Id(get_Line);
            value = get_Value(get_Line);
            if (id == row && value == dust_Value[row][0]) {
                char time[30];
                int count = 0;
                int j = 0;
                for (int i = 0; i < strlen(get_Line); i++) {
                    if (get_Line[i] == ',') count = count +1;
                    if (count == 1) {
                        time[j] = get_Line[i];
                        j++;
                    }
                    if (count == 2) {
                        time[j] = '\0';
                        break;
                    }

                }
                fprintf(dust_Summary, "%d,min,%s,%.1f\n", row, time, value);
                rewind(dust_Valid);
                break;
            }
        }
        float dust_Mean = mean(dust_Value, len_Column, row);
        fprintf(dust_Summary, "%d,mean,%d:%d:%d,%.1f\n", row, si.hour, si.minute, si.second, dust_Mean);
        float dust_Median = median(dust_Value, len_Column, row);
        fprintf(dust_Summary, "%d,median,%d:%d:%d,%.1f\n", row, si.hour, si.minute, si.second, dust_Median);
        row = row + 1;
    }
    fclose(dust_Valid);
    fclose(dust_Summary);
}
