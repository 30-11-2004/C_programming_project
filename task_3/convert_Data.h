#ifndef CONVERT_DATA_H
#define CONVERT_DATA_H

#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<string.h>
#include<time.h>
#include"take_File_Name.h"

struct frame{
    uint8_t start_Byte;
    uint8_t packet_Len;
    uint8_t ID;
    uint32_t Time;
    uint32_t PM;
    uint16_t AQI;
    uint8_t pollution_Code;
    uint8_t checksum;
    uint8_t stop_Byte;
};

uint32_t take_PM(float value);

uint8_t take_Pollution_Code(char pollution[]);

// return sum of bytes
uint8_t format_hex_uint32(uint32_t number, char string_Hex_uint32[12]);

// return sum of bytes
uint8_t format_hex_uint16(uint16_t number, char string_Hex_uint16[6]);

void convert_Data(struct frame *frame_1, char data_File[], char hex_File[]);

#endif