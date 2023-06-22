#!/bin/bash

# script baseado no código disponibilizado em:
# Derek Molloy, Exploring Raspberry Pi: Interfacing to the Real World with Embedded Linux,
# Wiley 2016, ISBN 978-1-119-1868-1, http://www.exploringrpi.com/
#
# Script usado para chavear um pino da GPIO na frequencia mais alta
# possivel usando Bash
echo 23 > /sys/class/gpio/export
sleep 0.5
echo "out" > /sys/class/gpio/gpio23/direction
COUNTER=0
while [ $COUNTER -lt 100000 ]; do
    echo 1 > /sys/class/gpio/gpio23/value
    let COUNTER=COUNTER+1
    echo 0 > /sys/class/gpio/gpio23/value
done
echo 23 > /sys/class/gpio/unexport
