/** Programa baseado no codigo disponibilizado em:
* Derek Molloy, Exploring Raspberry Pi: Interfacing to the Real World with Embedded Linux,
* Wiley 2016, ISBN 978-1-119-1868-1, http://www.exploringrpi.com/
*/
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <termios.h>   // biblioteca para comunicacao serial
#include <stdlib.h>
#include <wiringPi.h>
#include <softPwm.h>

int main(){
   int file, count;
   int pino_PWM = 23;                         // pwm por software na GPIO23
	int brilho;
	int range = 100;                           // periodo do PWM = 100us*range
	wiringPiSetupGpio();                       // usar a numeracao GPIO, nao WPi
	pinMode(pino_PWM,OUTPUT);	           // configura GPIO23 como saida
	softPwmCreate(pino_PWM, 1, range);  
   if ((file = open("/dev/ttyACM0", O_RDWR | O_NOCTTY | O_NDELAY))<0){
      perror("UART: Falha ao abrir o arquivo.\n");
      return -1;
   }
   struct termios options;             // cria estruturas para configurar a comunicacao
   tcgetattr(file, &options);          // ajusta os parametros do arquivo

   // Configura a comunicacao
   // 115200 baud, 8-bit, enable receiver, no modem control lines
   options.c_cflag = B115200 | CS8 | CREAD | CLOCAL;
   options.c_iflag = IGNPAR | ICRNL;   // ignora erros de paridade
   tcflush(file, TCIFLUSH);            // descarta informacao no arquivo
   tcsetattr(file, TCSANOW, &options); // aplica alteracoes imediatamente
   unsigned char transmit[2] = "1\0";  // cria uma frase (\0 indica o final da mensagem)
   if ((count = write(file, &transmit, 2))<0){             // transmite a frase
      perror("Falha ao escrever na saida\n");
      return -1;
   }
   
   while (1) {
      usleep(15000); 
      unsigned char receive[7]; 
      if ((count = read(file, (void*)receive, 100))<0){  
         perror("Falha ao ler da entrada\n");
         return -1;
    }
      int valor=atoi(receive);
      softPwmWrite (pino_PWM, valor);
      printf("%d\n",valor);
                
         }
}
