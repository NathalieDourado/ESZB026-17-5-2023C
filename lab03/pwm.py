#!/usr/bin/python3

# Script que cria um PWM por softwre na GPIO23
# para fazer um LED acender e apagar 3 vezes

import RPi.GPIO as GPIO
from time import sleep

GPIO.setmode(GPIO.BCM)
pinoPWM=23
PWM_freq_Hz=20000

GPIO.setup(pinoPWM,GPIO.OUT)
meuPWM=GPIO.PWM(pinoPWM,PWM_freq_Hz)
meuPWM.start(0)

for x in range(0,3):
    for dc in range(0,100,5):
        meuPWM.ChangeDutyCycle(dc)
        sleep(0.1)
    for dc in range(100,0,-5):
        meuPWM.ChangeDutyCycle(dc)
        sleep(0.1)

GPIO.cleanup()
