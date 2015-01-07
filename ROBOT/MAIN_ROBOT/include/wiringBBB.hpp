#include <stdio.h>
#include <stdlib.h>

typedef enum{
    OUTPUT
}DIRECTION;

typedef enum{
    LOW = 0,
    HIGH = 1
}STATE;

void pinMode(int pin, DIRECTION direction);
void digitalWrite(int pin, STATE state);
