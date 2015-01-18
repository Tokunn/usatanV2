#include "../include/write_tire_speed_value.hpp"

#define DUTY_TIME 750000


/*----- initialize() -----*/
TireSpeedvalueGPIO::TireSpeedvalueGPIO() {
    pinMode(LEFT_NORMAL_ROTATION, OUTPUT);
    pinMode(LEFT_REVERS_ROTATION, OUTPUT);
    //pinMode(LEFT_SPEED,           OUTPUT);
    pinMode(LEFT_SPEED,           AOUTPUT);

    pinMode(RIGT_NORMAL_ROTATION, OUTPUT);
    pinMode(RIGT_REVERS_ROTATION, OUTPUT);
    //pinMode(RIGT_SPEED,           OUTPUT);
    pinMode(RIGT_SPEED,           AOUTPUT);
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
        digitalWrite(LEFT_NORMAL_ROTATION, HIGH);
        digitalWrite(LEFT_REVERS_ROTATION, LOW);
    }
    else {
        digitalWrite(LEFT_NORMAL_ROTATION, LOW);
        digitalWrite(LEFT_REVERS_ROTATION, HIGH);
    }

    // LEFT Speed
    if (p_speed_char[2] == '0') {
        analogWrite(LEFT_SPEED, 1000000);
    }
    else {
        analogWrite(LEFT_SPEED, DUTY_TIME);
    }

    // RIGT Direction
    if (p_speed_char[3] == '0') {
        digitalWrite(RIGT_NORMAL_ROTATION, HIGH);
        digitalWrite(RIGT_REVERS_ROTATION, LOW);
    }
    else {
        digitalWrite(RIGT_NORMAL_ROTATION, LOW);
        digitalWrite(RIGT_REVERS_ROTATION, HIGH);
    }

    // RIGT Speed
    if (p_speed_char[5] == '0') {
        analogWrite(RIGT_SPEED, 1000000);
    }
    else {
        analogWrite(RIGT_SPEED, DUTY_TIME);
    }

    // Brake
    if (p_speed_char[2] == '0' && p_speed_char[5] == '0') {
        digitalWrite(LEFT_NORMAL_ROTATION, LOW);
        digitalWrite(LEFT_REVERS_ROTATION, LOW);
        analogWrite(LEFT_SPEED,           1000000);

        digitalWrite(RIGT_NORMAL_ROTATION, LOW);
        digitalWrite(RIGT_REVERS_ROTATION, LOW);
        analogWrite(RIGT_SPEED,           1000000);
    }
}
