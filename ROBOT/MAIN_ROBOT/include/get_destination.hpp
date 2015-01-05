#ifndef HEAD_GET_DESTINATION
#define HEAD_GET_DESTINATION


// Serial
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <termios.h>
#include <unistd.h>


// String
#include <string>


// Serial Config
#include "serial_config.hpp"


/*===== Destination =====*/
class Destination
{
    public:
        Destination();
        int get_position();
        int get_all_count();

    private:
        void recive_serial(std::string* string_destination);
        int comv_destination_string2int(
                const std::string* pose_string,
                const std::string* string_destination);

        int fd;
        int all_count;
        int pose_position[6];
        std::string pose_string[6];
        std::string string_destination;
};


#endif // HEAD_GET_DESTINATION
