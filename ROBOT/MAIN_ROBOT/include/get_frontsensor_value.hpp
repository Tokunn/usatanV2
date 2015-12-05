#ifndef HEAD_GET_FRONTSENSOR_VALUE
#define HEAD_GET_FRONTSENSOR_VALUE

// Standard
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

// GPIO
#include "wiringBBB.hpp"

// GPIO Config
#include "gpio_config.hpp"


/*===== FrontsensorValue =====*/
class FrontsensorValue
{
    public:
        FrontsensorValue();
        int get_sensor_value();

    private:
        void recive_serial(int* p_sensor_value);
        int comv_sensor_value(const int* p_sensor_value);

        int fd;
        int sensor_value;
        int sensor_threshold;
};

#endif // HEAD_GET_FRONTSENSOR_VALUE
