#ifndef HEAD_WRITE_TIRE_SPEED_VALUE
#define HEAD_WRITE_TIRE_SPEED_VALUE

// GPIO
#include "wiringBBB.hpp"
#include <stdio.h>


// GPIO Config
#include "gpio_config.hpp"


/*===== TireSpeedvalueGPIO =====*/
class TireSpeedvalueGPIO
{
    public:
        TireSpeedvalueGPIO();
        void write_speed(int speed);

    private:
        void comv_speed_i2a(char* p_speed_char, int* p_speed);
        void write_gpio(char* p_speed_char);
};

#endif // HEAD_WRITE_TIRE_SPEED_VALUE
