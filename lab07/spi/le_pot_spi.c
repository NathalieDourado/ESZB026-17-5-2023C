/******************************************************************
 * Programa baseado no codigo disponivel em:
 * http://robotics.hobbizine.com/raspiduino.html
 * 
 * Configura a RaspberryPi como mestre e se comunica
 * via SPI com um escravo Arduino, recebendo 1.000 valores deste.
 ******************************************************************/

#include <sys/ioctl.h>        // para ioctl()
#include <linux/spi/spidev.h> // para spi*()
#include <fcntl.h>            // para O_RDWR
#include <stdio.h>            // para printf()
#include <string.h>           // para memset()

#define NRO_MEDIDAS 1000

/******************************************************************
 * Declaracao das variaveis globais
 ******************************************************************/
int fd;                       // ponteiro para "/dev/spidev0.0"

/******************************************************************
 * spiTxRx()
 * Transmite um byte via SPI, e retorna um byte como resposta
*******************************************************************/
int spiTxRx(unsigned char txDat)
{
  unsigned char rxDat;
  struct spi_ioc_transfer spi;               // definido em spidev.h
  
  memset (&spi, 0, sizeof (spi));            // 'zera' o conteudo do struct
  spi.tx_buf        = (unsigned long)&txDat; // guarda o endereco do byte enviado
  spi.rx_buf        = (unsigned long)&rxDat; // guarda o endereco do byte recebido
  spi.len           = 1;                     // guarda o nro de bytes transmitidos
  ioctl (fd, SPI_IOC_MESSAGE(1), &spi);      // executa a comunicacao
  
  return rxDat;                              // retorna byte recebido
}

/******************************************************************
 * Main
 ******************************************************************/
int main (void)
{
   int i;
   unsigned int speed = 4000000;   // velocidade de comunicacao = 4MHz
   unsigned char result, result2;
   int vetor_medidas[NRO_MEDIDAS];
   FILE *fp_saida;
   fd = open("/dev/spidev0.0", O_RDWR);
   ioctl (fd, SPI_IOC_WR_MAX_SPEED_HZ, &speed);

   for ( i == 0; i < 10000; i++ ) // tenta 10000 vezes iniciar a coleta
   {
	   spiTxRx('i');              // envia o byte 'j'
	   result = spiTxRx(0);       // le a resposta do Arduino
	   if ( result == 'j' )       // se conseguiu iniciar a coleta
	   {
		   printf("Iniciando coleta na tentativa %d\n",i+1);
		   break;                 // sai do for(...)
	   }
	   usleep(10); // aguarda 10microsegundos para a proxima tentativa
   }
   if ( result == 'j' )  // se conseguiu iniciar a coleta
   {
       usleep(1200000);  // aguarda 1,2s a coleta terminar
       // solicita medidas, a 1a resposta eh ignorada ja que a comunicacao
       // eh sincrona (ao mesmo tempo que envia 'e', ja le uma resposta)
       spiTxRx('e');
       for ( i = 0; i < NRO_MEDIDAS; i++ ) // le valores medidos
       {
           result = spiTxRx('e');        // le byte menos significativo
           result2 = spiTxRx('e');       // le byte mais significativo
           vetor_medidas[i] = result | ( result2 << 8 );
       }
       
       fp_saida = fopen ("/home/pi/le_pot_spi_medidas.txt", "w+");
       for ( i = 0; i < NRO_MEDIDAS; i++ )
       {
		   fprintf(fp_saida,"%f %f\n", i/1000.0, vetor_medidas[i]*5.0/1023.0);
	   }
	   fclose(fp_saida);
   }
   else {
	   printf("Nao foi possivel ler os dados do barramento SPI.\n");
	   return 1;
   }
   
   return 0;
}
