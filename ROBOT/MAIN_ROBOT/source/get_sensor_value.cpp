#include "../include/get_sensor_value.hpp"


/*----- initialize() -----*/
SensorValue::SensorValue() {
    pinMode((int)NULL, AINPUT);
    for (int i = 0; i < 6; i++) {
        sensor_threshold[i] = 500;
    }
}


/*----- get_sensor_value() -----*/
int SensorValue::get_sensor_value() {
    recive_serial(sensor_value);
    int value = comv_sensor_value(sensor_value);
    return value;
}


/*----- recive_serial() -----*/
void SensorValue::recive_serial(int* p_sensor_value) {
    std::cout << "\t\t                                                                    \t\t";
    for (int i = 0; i < 6; i++) {
        p_sensor_value[i] = analogRead(i);
        std::cout << p_sensor_value[i] << ' ';
    }
    std::cout << '\n';
}


/*----- comv_sensor_value() -----*/
int SensorValue::comv_sensor_value(const int* p_sensor_value) {
    int sensor_value = 0;
    for (int i = 0; i < 6; i++) {
        if (p_sensor_value[i] > sensor_threshold[i]) {
            sensor_value = (sensor_value<<1) + 1;
        }
        else if (p_sensor_value[i] <= sensor_threshold[i]) {
            sensor_value = (sensor_value<<1) + 0;
        }
    }
    return sensor_value;
}
