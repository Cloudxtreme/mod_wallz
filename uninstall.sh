#!/bin/bash
echo "Disabling mod_wallz..."
sudo a2dismod wallz
echo "Removing binary and configurations..."
sudo rm /usr/lib/apache2/modules/mod_wallz.so
sudo rm /etc/apache2/mods-available/wallz.conf
sudo rm /etc/apache2/mods-available/wallz.load
echo "Restarting apache2... This may take a while..."
sudo service apache2 restart
