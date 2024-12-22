#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<string.h>
#include<time.h>
#include"take_File_Name.h"
#include"convert_Data.h"

uint32_t take_PM(float value) {
    uint32_t* PM = (uint32_t*)&value;
    return *PM;
}

uint8_t take_Pollution_Code(char pollution[]) {
    if(strcmp(pollution, "Good") == 0) return 'A';
    else if(strcmp(pollution, "Moderate") == 0) return 'B';
    else if(strcmp(pollution, "Slightly unhealthy") == 0) return 'C';
    else if(strcmp(pollution, "Unhealthy") == 0) return 'D';
    else if(strcmp(pollution, "Very unhealthy") == 0) return 'E';
    else if(strcmp(pollution, "Hazardous") == 0) return 'F';
    else return 'G';
}
// return sum of bytes
uint8_t format_hex_uint32(uint32_t number, char string_Hex_uint32[12]) {
    int i = 0;
    uint8_t sum = 0;
    while(number != 0) {
        if (i == 2 || i == 5 || i ==8) string_Hex_uint32[i] = ' ';
        else{
            string_Hex_uint32[i] = "0123456789ABCDEF"[number%16];
            if (i == 0 || i == 3 || i == 6 || i == 9) {
                sum = sum + number%16;
            }
            else if (i == 1 || i == 4 || i == 7 || i == 10) {
                sum = sum + 16 * (number%16);
            }
            number = number/16;
        }
        i++;
    }
    for (int j=0; j<10; j++) {
        if(string_Hex_uint32[j] != ' ' && string_Hex_uint32[j+1] != ' ') {
            char temp = string_Hex_uint32[j];
            string_Hex_uint32[j] = string_Hex_uint32[j+1];
            string_Hex_uint32[j+1] = temp;
        }
    }
    return sum;
}

// return sum of bytes
uint8_t format_hex_uint16(uint16_t number, char string_Hex_uint16[6]) {
    int i = 0;
    uint8_t sum = 0;
    while(number != 0) {
        if (i == 2) string_Hex_uint16[i] = ' ';
        else {
            string_Hex_uint16[i] = "0123456789ABCDEF"[number%16];
            if (i == 0 || i == 3) {
                sum = sum + number%16;
            }
            else if (i == 1 || i == 4) {
                sum = sum + 16 * (number%16);
            }
            number = number/16;
        }
        i++;
    }
    for (int j=0; j<4; j++) {
        if(string_Hex_uint16[j] != ' ' && string_Hex_uint16[j+1] != ' ') {
            char temp = string_Hex_uint16[j];
            string_Hex_uint16[j] = string_Hex_uint16[j+1];
            string_Hex_uint16[j+1] = temp;
        }
    }
    return sum;
}

int convert_Data(struct frame *frame_1, char data_File[], char hex_File[]) {
    FILE *data;
    FILE *hex;
    int id;
    float value;
    struct tm take_Time;
    int aqi;
    char level[50];
    char string_Hex_uint32[12] = "00 00 00 00";
    char string_Hex_uint16[6] = "00 00";
    hex = fopen(hex_File, "a");
    if(hex == NULL) {
        FILE *error_File;
        error_File = fopen("task3.log", "a");
        fputs("Error 07: cannot override the hex file", error_File);
        fclose(error_File);
        fclose(hex);
        return 0;
    }
    data = fopen(data_File, "r");
    printf("%s", data_File);
    fgets(level, 50, data);
    frame_1->start_Byte = 0xAA;
    frame_1->packet_Len = 0x10;
    frame_1->stop_Byte = 0xFF;
    while(fscanf(data, "%d,%d:%d:%d %d:%d:%d,%f,%d,%s", &id, &take_Time.tm_year, &take_Time.tm_mon, &take_Time.tm_mday, &take_Time.tm_hour, &take_Time.tm_min, &take_Time.tm_sec, &value, &aqi, level) == 10) {
        frame_1->ID = (uint8_t)id;
        take_Time.tm_year = take_Time.tm_year - 1900;
        take_Time.tm_mon = take_Time.tm_mon - 1;
        frame_1->Time = (uint32_t) (mktime(&take_Time));
        frame_1->PM = take_PM(value);
        frame_1->AQI = (uint16_t) aqi;
        frame_1->pollution_Code = take_Pollution_Code(level);
        fprintf(hex, "%X %X %0.2X ", frame_1->start_Byte, frame_1->packet_Len, frame_1->ID);
        uint8_t sum_bytes_time = format_hex_uint32(frame_1->Time, string_Hex_uint32);
        printf("%s ", string_Hex_uint32);
        fprintf(hex,"%s ", string_Hex_uint32);
        uint8_t sum_bytes_PM = format_hex_uint32(frame_1->PM, string_Hex_uint32);
        fprintf(hex,"%s ", string_Hex_uint32);
        uint8_t sum_bytes_AQI = format_hex_uint16(frame_1->AQI, string_Hex_uint16);
        fprintf(hex, "%s ", string_Hex_uint16);
        uint8_t sum = (frame_1->packet_Len + frame_1->ID + sum_bytes_time + sum_bytes_PM + sum_bytes_AQI + frame_1->pollution_Code);
        frame_1->checksum =  (~sum) + 1;
        fprintf(hex, "%0.2X %0.2X %X\n", frame_1->pollution_Code, frame_1->checksum, frame_1->stop_Byte);
        }
    fclose(data);
    fclose(hex);
    return 1;
}
