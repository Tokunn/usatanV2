#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <bitset>
#include <iomanip>

#include "../include/get_destination.hpp"
#include "../include/get_sensor_value.hpp"
#include "../include/do_linetrace.hpp"
#include "../include/write_tire_speed_value.hpp"


int main()
{
    Destination destination;
    SensorValue sensor;
    LineTrace command_lib;
    TireSpeedvalueGPIO motor;

    while (true) {      // 1 Round
        bool onlineflag = false;
        int count = 0;
        int stopline = destination.get_position();
        int all_count = destination.get_all_count();
        int stop_val = 0x00;

        printf("Stop Line: %d\n", stopline);

        while (true) {
            int val = sensor.get_sensor_value();
            command_lib.set_sensor_value(&val);

            if (val != 0x3F) {      // 0x3F = 0b111111
                onlineflag = false;
                printf("\tON Line Flag = false");
            }
            else if (onlineflag == false) {
                count++;
                onlineflag = true;
                printf("\tON Line Flag = true");
            }

            if ((val == 0x3F) && ((count == stopline) || (count == all_count))) {
                command_lib.set_sensor_value(&stop_val);
                printf("[!!]STOP\n");
            }

            int command = command_lib.get_tire_speed_value();

            printf("\tCount: %d", count);
            std::cout << "\tSensor Val: " << std::bitset<6>(val);
            printf("\tTire Speed: %06d\n", command);

            motor.write_speed(command);
            if (count == all_count) {
                break;
            }
        }

    }

    return EXIT_SUCCESS;

}
