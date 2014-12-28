#!/usr/bin/env python2


import serial


class OpenSerial(object):

    def __init__(self, port):
        self.xbee = serial.Serial(port, 9600)

    def send_serial_cmd(self, cmd):
        self.xbee.write(cmd)


def main():

    port = "/dev/ttyUSB0"
    ard = OpenSerial(port)

    cmd = ["$MAJOKO\n", "$OBAKE_\n", "$KAIDAN\n", "$NEKO__\n", "$KING__\n", "$BRUNA_\n"]

    #cmd = raw_input("Please type command :")

    ard.send_serial_cmd(cmd[0])

    #for i in range(6):
        #ard.send_serial_cmd(cmd[i])


if __name__ == '__main__':
    main()
