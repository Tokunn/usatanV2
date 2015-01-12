#ifndef HEAD_GET_SENSOR_VALUE
#define HEAD_GET_SENSOR_VALUE

// Standard
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

// GPIO
#include "wiringBBB.hpp"

// GPIO Config
#include "gpio_config.hpp"


/*===== SensorValue =====*/
class SensorValue
{
    public:
        SensorValue();
        int get_sensor_value();

    private:
        void recive_serial(int* p_sensor_value);
        int comv_sensor_value(const int* p_sensor_value);

        int fd;
        int sensor_value[6];
        int sensor_threshold[6];
};

#endif // HEAD_GET_SENSOR_VALUE
