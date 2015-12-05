#include "../include/get_frontsensor_value.hpp"


/*----- initialize() -----*/
FrontsensorValue::FrontsensorValue() {
    pinMode((int)NULL, AINPUT);
    sensor_threshold = 0;
}

/*----- get_sensor_value() -----*/
int FrontsensorValue::get_sensor_value() {
    recive_serial(&sensor_value);
    int value = comv_sensor_value(&sensor_value);
    return value;
}

/*----- recive_serial() -----*/
void FrontsensorValue::recive_serial(int* p_sensor_value) {
    std::cout << "\t";
    *p_sensor_value = analogRead(FRONTSENSOR_PINNUM);
    std::cout << *p_sensor_value << '\n';
}

/*----- comv_sensor_value() -----*/
int FrontsensorValue::comv_sensor_value(const int* p_sensor_value) {
    int sensor_value = 0;
    if (*p_sensor_value > sensor_threshold) {
        sensor_value = 0;
    }
    else if (*p_sensor_value <= sensor_threshold) {
        sensor_value = 1;
    }
    return sensor_value;
}
