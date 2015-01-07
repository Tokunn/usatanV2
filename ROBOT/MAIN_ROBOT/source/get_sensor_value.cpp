#include "../include/get_sensor_value.hpp"


#include <iostream>
#include <stdlib.h>


/*----- initialize() -----*/
SensorValue::SensorValue() {
    fd = open(SENSOR_SERIAL_PORT, O_RDWR);
}


/*----- get_sensor_value() -----*/
int SensorValue::get_sensor_value() {
    int value;
    do {
        recive_serial(sensor_value);
        value = comv_sensor_value(sensor_value);
    } while (value < 0);
    return value;
}


/*----- recive_serial() -----*/
void SensorValue::recive_serial(char* p_sensor_value) {
    read(fd, p_sensor_value, sizeof(p_sensor_value));
    p_sensor_value[2] = '\0';
}


/*----- comv_sensor_value() -----*/
int SensorValue::comv_sensor_value(const char* p_sensor_value) {
    char *endptr;
    int raw_sensor_value = strtol(p_sensor_value, &endptr, 16);
    int int_sensor_value;
    if (raw_sensor_value >= 0x10) {
        int_sensor_value = raw_sensor_value - 0x10;
    }
    else { // dust data
        return -1;
    }
    if ((int_sensor_value <= 0x3F) && (int_sensor_value >= 0x0)) {
        // 0x3F = 0b111111      0x0 = 0b000000
        return int_sensor_value;
    }
    else {
        return -1;
    }
}
