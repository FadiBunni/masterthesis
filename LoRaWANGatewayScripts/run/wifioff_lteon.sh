#!/bin/sh
#turn on ppp
sudo pon rnet
sleep 0.5
#set ppp at default route, assuming highest priority - check using sudo ip r
sudo route add default dev ppp0
sleep 0.5
#restart LoRaWAN Gateway sx1308
#sudo systemctl restart lrgateway.service
#restart LoRaWAN Gateway sx1302
sudo systemctl restart lrgateway1302.service
