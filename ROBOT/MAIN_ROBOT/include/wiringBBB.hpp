#ifndef HEAD_WIRINGBBB
#define HEAD_WIRINGBBB


#include <stdio.h>
#include <stdlib.h>
#include <iostream>

typedef enum{
    OUTPUT,
    AINPUT
}DIRECTION;

typedef enum{
    LOW = 0,
    HIGH = 1
}STATE;

void pinMode(int pin, DIRECTION direction);
void digitalWrite(int pin, STATE state);
int analogRead(int pin);

#endif // HEAD_WIRINGBBB
