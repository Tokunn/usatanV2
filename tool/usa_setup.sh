#!/usr/bin/env sh

pacman -Sy --noconfirm --needed
pacman -S python3 --noconfirm --needed
./usa_setup.py
