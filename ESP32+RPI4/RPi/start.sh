#!/bin/bash
sleep 10
echo Running at boot
cd /home/pi/Desktop/robot_car
source robotcarenv/bin/activate
python3 RPi_Mediapipe.py
bash