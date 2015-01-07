#ifndef HEAD_GET_SENSOR_VALUE
#define HEAD_GET_SENSOR_VALUE


// Serial
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>

// Serial Config
#include "serial_config.hpp"


/*===== SensorValue =====*/
class SensorValue
{
    public:
        SensorValue();
        int get_sensor_value();

    private:
        void recive_serial(char* p_sensor_value);
        int comv_sensor_value(const char* p_sensor_value);

        int fd;
        char sensor_value[10];
};

#endif // HEAD_GET_SENSOR_VALUE
