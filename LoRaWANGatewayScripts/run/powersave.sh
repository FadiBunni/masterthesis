#!/bin/sh
sleep 10
sudo tvservice -o
sleep 2
sudo echo none | sudo tee /sys/class/leds/led0/trigger
sleep 2
sudo echo 0 | sudo tee /sys/class/leds/led0/brightness
sudo rfkill unblock wifi

#turn off lora_sx1308
sudo systemctl stop lrgateway.service

#turn off lora_sx1302
sudo systemctl stop lrgateway1302.service
