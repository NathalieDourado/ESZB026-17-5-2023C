#!/bin/bash

cd /sys/class/gpio

echo 16 >export  #habilita a saida da porta do LED amarelo
sleep 1
echo 20 >export  #habilita a saida da porta do LED vermelho
sleep 1
echo 21 >export  #habilita a saida da porta do LED verde
sleep 1

x=1

while [ $x -le 5 ]
do

 cd gpio20
 echo out > direction
 echo 1 > value
 sleep 2
 echo 0 > value
 cd ..

 cd gpio21
 echo out > direction
 echo 1 > value
 sleep 1
 echo 0 > value
 cd ..

 cd gpio16
 echo out > direction
 echo 1 > value
 sleep 1
 echo 0 > value
 cd ..

 x=$(( $x + 1 ))
done

echo 16 > unexport
sleep 1
echo 20 > unexport
sleep 1
echo 21 > unexport
