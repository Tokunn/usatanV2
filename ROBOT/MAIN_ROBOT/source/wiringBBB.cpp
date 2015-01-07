#include "../include/wiringBBB.hpp"


/*----- pinMode() -----*/
void pinMode(int pin, DIRECTION direction) {
    FILE *fp_export;
    FILE *fp_pindirection;

    char pin_char[5];
    char export_path[] = "/sys/class/gpio/export";

    char direction_path[40];

    sprintf(pin_char, "%d", pin);
    fp_export = fopen(export_path, "w");
    fputs(pin_char, fp_export);
    fclose(fp_export);

    sprintf(direction_path, "/sys/class/gpio%d/direction", pin);
    fp_pindirection = fopen(direction_path, "w");

    // OUTPUT
    if (direction == OUTPUT) {
        fputs("out", fp_pindirection);
    }

    fclose(fp_pindirection);
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
