#!/usr/bin/env python2


import serial


class OpenSerial(object):

    def __init__(self, port):
        self.xbee = serial.Serial(port, 9600)

    def send_serial_cmd(self, cmd):
        for i in range(1):
            self.xbee.write(cmd)


def main():

    port = raw_input("Port :")
    ard = OpenSerial(port)

    while True:
        cmd = raw_input("Please type command :")
        if (len(cmd) > 100):
            print("Bye")
            break
        ard.send_serial_cmd(cmd)


if __name__ == '__main__':
    main()
