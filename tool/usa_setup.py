#!/usr/bin/env python3
# -*- coding: utf-8 -*-

### H27 Apr 26

import os, sys
import subprocess
import shutil

SCRIPTDIR = os.path.dirname(os.path.abspath(__file__))
HOMEDIR = os.environ['HOME']
PKGFILE = os.path.join(SCRIPTDIR, 'pkglist')
ASOUNDFILE = os.path.join('/etc', 'asound.conf')
asound = """
defautls.pcm.card 1
defautls.pcm.device 0
defautls.ctl.card 1
"""
CONFFILE = os.path.join(os.path.dirname(SCRIPTDIR), 'ROBOT', 'MAIN_ROBOT', 'start_scripts')
CONFPY = os.path.join(CONFFILE, 'start_conf.py')
CONFSV = os.path.join(CONFFILE, 'start_conf.service')
SYSTEMD = os.path.join('/etc', 'systemd', 'system')
SCRIPTS = os.path.join('/opt', 'bin')

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
    open(ASOUNDFILE, "w").write(asound)


#----- settingConf() -----#
def settingConf():
    shutil.copy(CONFPY, SCRIPTS)
    shutil.copy(CONFSV, SYSTEMD)
    cmd = "systemctl enable start_conf.service"
    call_system(cmd)


#----- main() -----#
def main():
    installPkg()
    settingPcm()
    settingConf()


if __name__ == '__main__':
    try:
        main()
    except KeyboardInterrupt:
        print("\nCtrl+C -> END")

