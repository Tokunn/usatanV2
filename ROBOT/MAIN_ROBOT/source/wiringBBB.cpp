#include "../include/wiringBBB.hpp"


/*----- pinMode() -----*/
void pinMode(int pin, DIRECTION direction) {

    // OUTPUT
    if (direction == OUTPUT) {
        // export
        char pin_char[5];
        char export_path[] = "/sys/class/gpio/export";
        FILE *fp_export;
        sprintf(pin_char, "%d", pin);
        fp_export = fopen(export_path, "w");
        fputs(pin_char, fp_export);
        fclose(fp_export);
        // direction
        char out_char[] = "out";
        char direction_path[40];
        FILE *fp_pindirection;
        sprintf(direction_path, "/sys/class/gpio/gpio%d/direction", pin);
        fp_pindirection = fopen(direction_path, "w");
        fputs(out_char, fp_pindirection);
        fclose(fp_pindirection);
    }
    // ANALOG INPUT
    if (direction == AINPUT) {
        char analog_input_char[] = "cape-bone-iio";
        char slots_path[] = "/sys/devices/bone_capemgr.9/slots";
        FILE *fp_slots;
        fp_slots = fopen(slots_path, "w");
        fputs(analog_input_char, fp_slots);
        fclose(fp_slots);
    }
}


/*----- digitalWrite() -----*/
void digitalWrite(int pin, STATE state) {
    FILE *fp_value;

    char value_path[40];

    sprintf(value_path, "/sys/class/gpio/gpio%d/value", pin);
    fp_value = fopen(value_path, "w");

    // LOW
    if (state == LOW) {
        fputs("0", fp_value);
    }
    // HIGH
    else if (state == HIGH) {
        fputs("1", fp_value);
    }

    fclose(fp_value);
}


/*----- analogRead() -----*/
int analogRead(int pin) {
    char analog_input_pin_path[40];
    char analog_input_get_char[40];
    FILE *fp_analog_pin;
    sprintf(analog_input_pin_path, "/sys/devices/ocp.3/helper.15/AIN%d", pin);
    fp_analog_pin = fopen(analog_input_pin_path, "r");
    fgets(analog_input_get_char, 40, fp_analog_pin);
    fclose(fp_analog_pin);
    int value = atoi(analog_input_get_char);
    return value;
}
