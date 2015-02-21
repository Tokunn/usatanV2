#include "../include/get_sensor_value.hpp"


/*----- initialize() -----*/
SensorValue::SensorValue() {
    pinMode((int)NULL, AINPUT);
    //int threshold[] = { 1714, 1470, 1696, 1672, 1666, 1634 };
    //int threshold[] = { 1644, 1378, 1576, 1594, 1591, 1549 };
    //int threshold[] = { 1644, 1378, 1600, 1594, 1591, 1549 };
    int threshold[] = { 1648, 1427, 1598, 1615, 1588, 1554 };
    for (int i = 0; i < 6; i++) {
        sensor_threshold[i] = threshold[i];
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
        /*if (p_sensor_value[i] > sensor_threshold[i]) {
            sensor_value = (sensor_value<<1) + 0;
        }
        else if (p_sensor_value[i] <= sensor_threshold[i]) {
            sensor_value = (sensor_value<<1) + 1;
        }*/
        if (p_sensor_value[i] < sensor_threshold[i]) {
            sensor_value = (sensor_value<<1) + 0;
        }
        else if (p_sensor_value[i] >= sensor_threshold[i]) {
            sensor_value = (sensor_value<<1) + 1;
        }
    }
    return sensor_value;
}
