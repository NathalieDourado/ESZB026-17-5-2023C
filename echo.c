/** Programa baseado no codigo disponibilizado em:
* Derek Molloy, Exploring Raspberry Pi: Interfacing to the Real World with Embedded Linux,
* Wiley 2016, ISBN 978-1-119-1868-1, http://www.exploringrpi.com/
*/
#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<termios.h>   // biblioteca para comunicacao serial

int main(){
   int file, count;
   if ((file = open("/dev/ttyUSB0", O_RDWR | O_NOCTTY | O_NDELAY))<0){
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
   unsigned char transmit[23] = "Testando a comunicacao\0";  // cria uma frase (\0 indica o final da mensagem)
   if ((count = write(file, &transmit, 23))<0){             // transmite a frase
      perror("Falha ao escrever na saida\n");
      return -1;
   }
   usleep(100000);                     // Espera 100ms pela resposta do Arduino
   unsigned char receive[100];         // cria um buffer para receber os dados
   if ((count = read(file, (void*)receive, 100))<0){        // recebe os dados
      perror("Falha ao ler da entrada\n");
      return -1;
   }
   if (count==0) printf("Nao houve resposta!\n");
   else printf("Foram lidos [%d] caracteres: %s\n",count,receive);
   close(file);
   return 0;
}
