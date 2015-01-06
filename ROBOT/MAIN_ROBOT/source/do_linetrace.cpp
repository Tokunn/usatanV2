#include "../include/do_linetrace.hpp"


/*----- initialize() -----*/
LineTrace::LineTrace() {
    // Master Speed
    master_speed = 1;

    /* command init */
    for (int i = 0; i <= 0x3F; i++) {
        command[i][0] = 0;
        command[i][1] = 0;
    }

    // Out of line
    command[0x00][0] = 0;
    command[0x00][1] = 0;

    // Line in right side
    command[0x01][0] = 1;
    command[0x01][1] = 0;

    command[0x03][0] = 1;
    command[0x03][1] = 0;

    command[0x02][0] = 1;
    command[0x02][1] = 0;

    command[0x06][0] = 1;
    command[0x06][1] = 0;

    // Line in front
    command[0x04][0] = 1;
    command[0x04][1] = 1;

    command[0x0C][0] = 1;
    command[0x0C][1] = 1;

    command[0x08][0] = 1;
    command[0x08][1] = 1;

    // Line in left side
    command[0x18][0] = 0;
    command[0x18][1] = 1;

    command[0x10][0] = 0;
    command[0x10][1] = 1;

    command[0x30][0] = 0;
    command[0x30][1] = 1;

    command[0x20][0] = 0;
    command[0x20][1] = 1;

    // Destination positions
    command[0x3F][0] = 1;
    command[0x3F][1] = 1;
}


/*----- set_sensor_value() -----*/
void LineTrace::set_sensor_value(int* p_sensor_value) {
    sensor_value = *p_sensor_value;
}


/*----- get_tire_speed_value() -----*/
int LineTrace::get_tire_speed_value() {
    return comp_command(&sensor_value, command);
}


/*----- comp_command() -----*/
int LineTrace::comp_command(const int* p_sensor_value, const int (*p_command)[2]) {
    int return_command = 0;

    return_command += p_command[*p_sensor_value][0] * master_speed * 1000;
    // If command[][0] = 11, return_command = 011000
    return_command += p_command[*p_sensor_value][1] * master_speed;
    // If command[][1] = 11, return_command = 011011

    if (p_command[*p_sensor_value][0] < 0) {
        return_command += 100000;
        // If return_command = 011011, return_command = 111011
    }
    if (p_command[*p_sensor_value][1] < 0) {
        return_command += 100;
        // If return_command = 111011, return_command = 111111;
    }

    return return_command;
}
