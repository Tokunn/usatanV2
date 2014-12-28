#!/usr/bin/env python2


import serial
import time
import sys


def main():

    xbeeport = raw_input("Xbee-Port :")

    xbee = serial.Serial(xbeeport, 9600) 

    sys.stdout.write("\'")
    while True:

        mes = xbee.read()

        if (mes != '\0'):
            sys.stdout.write(mes)
        else:
            sys.stdout.write("\'\n\'")



if __name__ == '__main__':
    main()
