#!/bin/bash

sudo cp /home/pi/startup_gpios.service /etc/systemd/system/
#sudo cp /home/pi/file_sync.service /etc/systemd/system/
sudo cp /home/pi/startup_lartos.service /etc/systemd/system/
sudo systemctl daemon-reload
sudo systemctl enable startup_gpios.service
sudo systemctl enable startup_lartos.service
sudo systemctl start startup_gpios.service
sudo systemctl start startup_lartos.service
sudo systemctl status startup_lartos.service
sudo systemctl status startup_gpios.service

