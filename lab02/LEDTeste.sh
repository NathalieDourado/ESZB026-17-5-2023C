#!/bin/bash

LED_AM=16  
echo $LED_AM >> "/sys/class/gpio/export"
echo $1 >> "/sys/class/gpio/gpio$LED_AM/value"
sleep 3
echo $0 >> "/sys/class/gpio/gpio$LED_AM/value"
echo $LED_AM >> "/sys/class/gpio/unexport"

