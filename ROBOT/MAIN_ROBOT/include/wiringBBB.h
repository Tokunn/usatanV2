#include <stdio.h>
#include <stdlib.h>

typedef enum DIRECTION {
    OUTPUT
} DIRECTION

typedef enum STATE {
    LOW = 0,
    HIGH = 1
} STATE

void pinMode(int pin, DIRECTION direction);
void digitalWrite(int pin, STATE state);
