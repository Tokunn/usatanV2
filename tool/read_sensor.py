#!/usr/bin/env python3
# -*- coding: utf-8 -*-

### UsatanV2 Sensor threshould
### H27 Ap2 22

import os, sys


#----- PinMode_DIN -----#
def PinMode_DIN(pin):
    export_path = "/sys/class/gpio/export"
    open(export_path, 'w').write("{0}".format(pin))
    direction_path = "/sys/class/gpio/gpio{0}/direction".format(pin)
    open(direction_path, 'w').write("in")


#----- PinMode_AIN -----#
def PinMode_AIN():
    slots_path = "/sys/devices/bone_capemgr.9/slots"
    open(slots_path, 'w').write("cape-bone-iio")


#----- analogRead() -----#
def analogRead(pin):
    pin_path = "/sys/devices/ocp.3/helper.15/AIN{0}".format(pin)
    return int(open(pin_path).readline())


#----- main() -----#
def main():
    PinMode_AIN()
    # Sample 1
    value1 = [0, 0, 0, 0, 0, 0]
    input('Enter1 >')     # wait
    for i in range(6):
        value1[i] = analogRead(i)
    print(value1)
    # Sample 2
    value2 = [0, 0, 0, 0, 0, 0]
    input('Enter2 >')     # wait
    for i in range(6):
        value2[i] = analogRead(i)
    print(value2)
    # Threshould
    threshould = [0, 0, 0, 0, 0, 0]
    for i in range(6):
        threshould[i] = (value1[i] + value2[i]) / 2
    print("Threshould")
    print(threshould)


if __name__ == '__main__':
    try:
        main()
    except KeyboardInterrupt:
        print("\nCtrl+C -> END")

