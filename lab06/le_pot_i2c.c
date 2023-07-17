// Programa baseado no codigo disponibilizado em:
// Derek Molloy, Exploring Raspberry Pi: Interfacing to the Real World with Embedded Linux,
// Wiley 2016, ISBN 978-1-119-1868-1, http://www.exploringrpi.com/

#include<stdio.h>
#include<fcntl.h>
#include<sys/ioctl.h>
#include<linux/i2c.h>
#include<linux/i2c-dev.h>
#define BUFFER_SIZE 5      // 5 posicoes do buffer do Arduino: de 0x00 a 0x04

int main(int argc, char **argv){
   int file, i, alert=0xFF;
   printf("Iniciando o programa de comunicacao com o Arduino via I2C.\n");

   if((file=open("/dev/i2c-1", O_RDWR)) < 0){ // abrindo o dispositivo I2C
      perror("Falha ao abrir o barramento I2C.\n");
      return 1;
   }
   if(ioctl(file, I2C_SLAVE, 0x40) < 0){ // configurando o endereco do escravo
      perror("Falha de comunicacao com o Arduino.\n");
      return 1;
   }

   // verifica se foi passado um valor para o limite do alarme como argumento do programa
   if(argc==2){
     if (sscanf(argv[1],"%i",&alert)!=1) { // converte o argumento string para int
        perror("Falha ao ler o valor do limite do alarme.\n");
        return 1;
     }
     if (alert>1023 || alert<0) {
        perror("Limite do alarme fora da faixa especificada.\n");
        return 1;
     }
     char alertbuf[] = {0x02, 0, 0};    // limite do alarme com 'comando' 0x02
     alertbuf[1] = alert & 0xFF;        // byte menos significativo
     alertbuf[2] = alert >> 8;          // byte mais significativo

     printf("Ajustando limite do alarme em %d.\n", alert);
     if(write(file, alertbuf, 3)!=3){   // enviando os 3 bytes do alertbuf
        perror("Falha ao ajustar o limite do alarme!\n");
        return 1;
     }
   }
   char rec[BUFFER_SIZE], send;         // cria buffer para receber os dados
   for(i=0; i<BUFFER_SIZE; i++){        // para cada posicao no buffer
     send = (char) i;                   // converte o inteiro i para char (=1byte)
     if(write(file, &send, 1)!=1){      // enviando um byte com a posicao desejada
        perror("Falha ao enviar um dado.\n");
        return 1;
     }
     if(read(file, &rec[i], 1)!=1){     // recebendo um byte com o valor da posicao
        perror("Falha ao receber um dado.\n");
        return 1;
     }
   }
   int valor, limite, valorLED;
   valor =  rec[0] | ( rec[1] << 8 );   // converte 2 bytes de 8bits cada para 1 inteiro de 16bits
   limite =  rec[2] | ( rec[3] << 8 );
   valorLED = rec[4];
   printf("O valor lido foi %d.\n", valor);
   printf("O alarme esta ajustado em %d.\n", limite);
   printf("O LED esta ajustado em %d.\n", valorLED);

   close(file);
   return 0;
}
