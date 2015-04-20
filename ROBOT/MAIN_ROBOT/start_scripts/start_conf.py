#!/usr/bin/env python3
# -*- coding: utf-8 -*-

### H27 Apr 20 

import os, sys
import subprocess


#----- call_system() -----#
def call_system(cmd):
    splitted_cmd = cmd.split()
    subprocess.call(splitted_cmd)


#----- main() -----#
def main():
    # Add IP address
    cmd = "modprobe g_ether"
    call_system(cmd)
    cmd = "ip link set usb0 up"
    call_system(cmd)
    cmd = "ip addr add 192.168.7.2/24 dev usb0"
    call_system(cmd)

if __name__ == '__main__':
    try:
        main()
    except KeyboardInterrupt:
        print("\nCtrl+C -> END")

