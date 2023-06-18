#!/bin/bash

LED_AMARELO=16  # Usar uma variável facilita alterações futuras na porta usada
LED_VERMELHO=20
LED_VERDE=21

VALUE=$1      # Argumento fornecido ao executar o script
i=0

echo $LED_AMARELO > /sys/class/gpio/export
echo $LED_VERMELHO > /sys/class/gpio/export
echo $LED_VERDE > /sys/class/gpio/export
sleep 0.5

while [ $i -lt 5 ]
  do
    echo "out" > /sys/class/gpio/gpio$LED_VERMELHO/direction
    echo $VALUE > /sys/class/gpio/gpio$LED_VERMELHO/value
    sleep 2
    echo 0 > /sys/class/gpio/gpio$LED_VERMELHO/value

    echo "out" > /sys/class/gpio/gpio$LED_VERDE/direction
    echo $VALUE > /sys/class/gpio/gpio$LED_VERDE/value
    sleep 1
    echo 0 > /sys/class/gpio/gpio$LED_VERDE/value

    echo "out" > /sys/class/gpio/gpio$LED_AMARELO/direction
    echo $VALUE > /sys/class/gpio/gpio$LED_AMARELO/value
    sleep 1
    echo 0 > /sys/class/gpio/gpio$LED_AMARELO/value

    i=$((i+1))
  done
  
echo $LED_VERMELHO > /sys/class/gpio/unexport
echo $LED_VERDE > /sys/class/gpio/unexport
echo $LED_AMARELO > /sys/class/gpio/unexport
