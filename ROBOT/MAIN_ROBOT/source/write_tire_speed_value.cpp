#include "../include/write_tire_speed_value.hpp"

#include <stdio.h>


/*----- initialize() -----*/
TireSpeedvalueGPIO::TireSpeedvalueGPIO() {
    if (wiringPiSetup() != -1) {
        pinMode(LEFT_NORMAL_ROTATION, OUTPUT);
        pinMode(LEFT_REVERS_ROTATION, OUTPUT);
        pinMode(LEFT_SPEED,           OUTPUT);

        pinMode(RIGT_NORMAL_ROTATION, OUTPUT);
        pinMode(RIGT_REVERS_ROTATION, OUTPUT);
        pinMode(RIGT_SPEED,           OUTPUT);
    }
}


/*----- write_speed() -----*/
void TireSpeedvalueGPIO::write_speed(int speed) {
    char speed_char[7];
    comv_speed_i2a(speed_char, &speed);
    write_gpio(speed_char);
}


/*----- comv_speed_i2a() -----*/
void TireSpeedvalueGPIO::comv_speed_i2a(char* p_speed_char, int* p_speed) {
    sprintf(p_speed_char, "%06d", *p_speed);
}


/*----- write_gpio() -----*/
void TireSpeedvalueGPIO::write_gpio(char* p_speed_char) {
    // LEFT Direction
    if (p_speed_char[0] == '0') {
        digitalWrite(LEFT_NORMAL_ROTATION, 1);
        digitalWrite(LEFT_REVERS_ROTATION, 0);
    }
    else {
        digitalWrite(LEFT_NORMAL_ROTATION, 0);
        digitalWrite(LEFT_REVERS_ROTATION, 1);
    }

    // LEFT Speed
    if (p_speed_char[2] == '0') {
        digitalWrite(LEFT_SPEED, 0);
    }
    else {
        digitalWrite(LEFT_SPEED, 1);
    }

    // RIGT Direction
    if (p_speed_char[3] == '0') {
        digitalWrite(RIGT_NORMAL_ROTATION, 1);
        digitalWrite(RIGT_REVERS_ROTATION, 0);
    }
    else {
        digitalWrite(RIGT_NORMAL_ROTATION, 0);
        digitalWrite(RIGT_REVERS_ROTATION, 1);
    }

    // RIGT Speed
    if (p_speed_char[5] == '0') {
        digitalWrite(RIGT_SPEED, 0);
    }
    else {
        digitalWrite(RIGT_SPEED, 1);
    }

    // Brake
    if (p_speed_char[2] == '0' && p_speed_char[5]) {
        digitalWrite(LEFT_NORMAL_ROTATION, 1);
        digitalWrite(LEFT_REVERS_ROTATION, 1);
        digitalWrite(LEFT_SPEED,           1);

        digitalWrite(RIGT_NORMAL_ROTATION, 1);
        digitalWrite(RIGT_REVERS_ROTATION, 1);
        digitalWrite(RIGT_SPEED,           1);
    }
}
