#!/bin/bash
echo "Installing config..."
sudo cp ./wallz.conf /etc/apache2/mods-available/wallz.conf
echo "Compiling module..."
sudo apxs2 -cia mod_wallz.c
echo "Restarting apache... This may take a while..."
sudo service apache2 restart
echo "Cleaning up..."
sudo rm ./.libs/*
sudo rm -rf ./.libs
sudo rm ./mod_wallz.la
sudo rm ./mod_wallz.lo
sudo rm ./mod_wallz.slo

