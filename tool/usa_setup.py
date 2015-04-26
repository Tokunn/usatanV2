#!/usr/bin/env python3
# -*- coding: utf-8 -*-

### H27 Apr 26

import os, sys
import subprocess

SCRIPTDIR = os.path.dirname(os.path.abspath(__file__))
HOMEDIR = os.environ['HOME']
PKGFILE = os.path.join(SCRIPTDIR, 'pkglist')
ASOUNDFILE = os.path.join('/etc', 'asound.conf')
asound = """
defautls.pcm.card 1
defautls.pcm.device 0
defautls.ctl.card 1
"""

#----- call_system() -----#
def call_system(cmd):
    splitted_cmd = cmd.split()
    subprocess.call(splitted_cmd)


#----- call_pacman() -----#
def call_pacman(pkg):
    cmd = "pacman -S {0} --needed --noconfirm".format(pkg)
    call_system(cmd)


#----- installPkg() -----#
def installPkg():
    # Full system update
    call_system("pacman -Sy --noconfirm")
    # Install packages
    pkglist = open(PKGFILE).readlines()
    for i in range(len(pkglist)):
        call_pacman(pkglist[i])


#----- settingPcm() -----#
def settingPcm():
    print(ASOUNDFILE)


#----- main() -----#
def main():
    installPkg()
    settingPcm()


if __name__ == '__main__':
    try:
        main()
    except KeyboardInterrupt:
        print("\nCtrl+C -> END")

