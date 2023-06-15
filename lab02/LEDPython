#!/usr/bin/python3

import sys
import time
import RPi.GPIO as GPIO
LED_PATH_VERMELHO = "/sys / class / gpio / gpio21 /"
LED_PATH_VERDE = "/sys / class / gpio / gpio20 /"
LED_PATH_AMARELO = "/sys / class / gpio / gpio16 /"
SYSFS_DIR = "/ sys / class / gpio /"
LED_VERMELHO = "20"
LED_VERDE = "21"
LED_AMARELO = "16"

GPIO.setmode(GPIO.BCM)
GPIO.setup(LED_VERMELHO, GPIO.OUT)
GPIO.setup(LED_VERDE, GPIO.OUT)
GPIO.setup(LED_AMARELO, GPIO.OUT)

# Função para acender um LED durante um tempo determinado
def acender_led(pino, tempo) :
GPIO.output(pino, GPIO.HIGH)
time.sleep(tempo)
GPIO.output(pino, GPIO.LOW)

# repetindo a sequência por 5 vezes
for _ in range(5) :
  acender_led(LED_VERMELHO, 2)
  acender_led(LED_VERDE, 1)
  acender_led(LED_AMARELO, 1)

# Desabilitando os pinos GPIO
GPIO.cleanup()
