#!/bin/bash                  #identifica para rodar o sistema em Bash shell

cd /sys/class/gpio           #direciona a pasta em que comanda o GPIO

echo 16 >export              #habilita a saida da porta do LED amarelo
sleep 1                      #delay de 1 segundo para garantir a abertura das portas
echo 20 >export              #habilita a saida da porta do LED vermelho
sleep 1
echo 21 >export              #habilita a saida da porta do LED verde
sleep 1

x=1                          #cria uma variavel para fazer o loop 5 vezes

while [ $x -le 5 ]           #cria o loop
do

 cd gpio20                   #move para a saida do LED vermelho
 echo out > direction        #indica que o pino sera usado como saida
 echo 1 > value              #ativa o LED
 sleep 2                     #deixa o LED ativado por 2 segundos
 echo 0 > value              #desativa o LED
 cd ..                       #retorna para a pasta anterior

 cd gpio21                   #move para a saida do LED verde
 echo out > direction
 echo 1 > value
 sleep 1                     #deixa o LED ativado por 1 segundos
 echo 0 > value
 cd ..

 cd gpio16                   #move para a saida do LED amarelo
 echo out > direction
 echo 1 > value
 sleep 1
 echo 0 > value
 cd ..

 x=$(( $x + 1 ))            #adiciona 1 a variavel criada
done

echo 16 > unexport          #desabilita a saida da porta do LED amarelo
sleep 1
echo 20 > unexport          #desabilita a saida da porta do LED vermelho
sleep 1
echo 21 > unexport          #desabilita a saida da porta do LED verde