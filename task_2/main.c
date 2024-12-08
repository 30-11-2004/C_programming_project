#include <stdio.h>
#include"name_Data_File.h"
#include"classify_Value.h"
#include"air_Quality.h"
#include"calc_Dust.h"
#include"statistic_Aqi.h"

int main(int argc, char** argv) {
    char *name_file[30];
    name_Data_File(argc, argv, name_file);
    print_Classification(*name_file);
    print_AQI();
    print_Summary(*name_file);
    print_Aqi_Statistic();
    return 1;
}
