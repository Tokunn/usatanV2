#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <bitset>
#include <iomanip>
#include <sys/time.h>
#include <unistd.h>

#include "../include/get_destination.hpp"
#include "../include/get_frontsensor_value.hpp"
#include "../include/get_sensor_value.hpp"
#include "../include/do_linetrace.hpp"
#include "../include/write_tire_speed_value.hpp"
#include "../include/say_voice.hpp"
#include "../include/wiringBBB.hpp"
#include "../include/gpio_config.hpp"

#define WAIT_LOOP_TIME           30000


int main()
{
    printf("Start! Initializing...");
    Destination destination;
    FrontsensorValue frontsensor;
    SensorValue sensor;
    LineTrace command_lib;
    TireSpeedvalueGPIO motor;
    // TODO kmizu motadora pin HIGH
    // TODO find pin (1)
    printf("OK\n");

    pinMode(LIMIT_SWITCH, INPUT);

    while (true) {      // 1 Round
        printf("Waiting...\n");
        bool onlineflag = false;
        bool kokodayoflag = false;
        int count = 0;
        int stopline = destination.get_position();
        //int stopline = 3;   // #=# DEUBG #=#
        int all_count = destination.get_all_count();
        int stop_val = 0x00;
        int on_val = 0x3F;

        printf("Stop Line: %d\n", stopline);
        talk_usatan(-3);
        usleep(10000000);
        talk_usatan(-1);

        while (true) {      // Small Loop
            /*struct timeval t0;      // Roop Start
            gettimeofday(&t0, NULL);*/

            int val = sensor.get_sensor_value();
            command_lib.set_sensor_value(&val);
            int command = command_lib.get_tire_speed_value();

            // front sensor
            int frontsensorvalue = frontsensor.get_sensor_value();
            if (frontsensorvalue) {
                command_lib.set_sensor_value(&stop_val);
                command = command_lib.get_tire_speed_value();
                motor.write_speed(command);
                printf("\n[!!]OBJECT FOUND (FRONT)\tvalue: %d\n", frontsensorvalue);
                usleep(600000);
                continue;
            }

            /*if (val != 0x3F) {      // 0x3F = 0b111111
                onlineflag = false;
                printf("\tON Line Flag = false");
            }
            else if (onlineflag == false) {
                count++;
                onlineflag = true;
                printf("\tON Line Flag = true");
            }*/

            if (val == 0x3F) {      // Count UP
                count++;
                talk_usatan(count);
            }

            if ((val == 0x3F) && (count == stopline) && (onlineflag == false)) {   // STOP LINE
                command_lib.set_sensor_value(&stop_val);
                command = command_lib.get_tire_speed_value();
                motor.write_speed(command);
                printf("\n[II]STOP DIRECTION\n");
                if (kokodayoflag == false) {
                    talk_usatan(-2);
                    kokodayoflag = true;
                }
                // Wait Limit Swich
                int value;
                printf("Waiting Limit...\n");
                do {
                    value = digitalRead(LIMIT_SWITCH);
                } while (value == HIGH);
                printf("End\n");
                onlineflag = true;
                //talk_usatan(-2);
                usleep(1000000);
                // RUN
                command_lib.set_sensor_value(&on_val);
                command = command_lib.get_tire_speed_value();
                motor.write_speed(command);
                usleep(600000);
            }
            else if (count == all_count) {      // HOME LINE
                command_lib.set_sensor_value(&stop_val);
                command = command_lib.get_tire_speed_value();
                motor.write_speed(command);

                printf("[II]STOP HOME\n");
                talk_usatan(-2);
                break;
            }
            else if (val != 0x3F) {
                onlineflag = false;
            }

            //int command = command_lib.get_tire_speed_value();

            printf("\tCount: %d", count);
            std::cout << "\tSensor Val: " << std::bitset<6>(val);
            printf("\tTire Speed: %06d\n", command);

            motor.write_speed(command);

            if (val == 0x3F) {
                usleep(600000); //300000
            }

            /*struct timeval t1;      // Roop End
            gettimeofday(&t1, NULL);
            int delay_time = WAIT_LOOP_TIME - (t1.tv_usec - t0.tv_usec);
            if (delay_time > 0) {
                usleep(delay_time);
            }*/
            usleep(100);
        }

    }

    return EXIT_SUCCESS;
}
