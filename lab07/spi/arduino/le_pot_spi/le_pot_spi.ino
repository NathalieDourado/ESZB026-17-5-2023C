#include <SPI.h>

#define NRO_MEDIDAS 1000

//////////////////////////////////////////////////////////////////////////////////
// Define variaveis globais
const int PinoPotenciometro = A0;       // pino analogico ligado ao potenciometro
int vetor_medidas[NRO_MEDIDAS];
unsigned char inicia_coleta = 0;
int contador = 0;                       // nro de bytes enviados

//////////////////////////////////////////////////////////////////////////////////
void setup (void)
{
    SPI.setDataMode(SPI_MODE0); // configura SPI em modo 0
    pinMode(MISO, OUTPUT);      // define o pino MISO como saida, ja que o Arduino eh escravo
    SPCR |= bit (SPE);          // habilita o barramento SPI
    SPI.attachInterrupt();      // liga interrupcao para SPI
}

//////////////////////////////////////////////////////////////////////////////////
// Funcao de interrupcao do barramento SPI
ISR (SPI_STC_vect)  
{
    unsigned char byteRecebido = SPDR;      // le um byte do barramento SPI
    
    switch ( byteRecebido ){
        case 'e':                           // solicitando dados, enviar...
            if ( contador < NRO_MEDIDAS*2 ) // x2 porque cada int sao 2 bytes
            {
                if ( (contador % 2) == 0 )  // contador par
                {
                    SPDR = vetor_medidas[contador/2] & 0xFF; // envia byte menos significativo
                }
                else                        // contador impar
                {
                    SPDR = vetor_medidas[(contador-1)/2] >> 8; // envia byte mais significativo
                }
                contador++;
            }
            break;

        case 'i':                           // inicia coleta
            SPDR = 'j';                     // responde 'j', indicando que entendeu comando
            inicia_coleta = 1;
            contador = 0;
            break;
            
        default:                            // outro byte recebido, ignora...
            break;
    }
}

//////////////////////////////////////////////////////////////////////////////////
void loop (void)
{
  int i;
  if ( inicia_coleta == 1 )
  {
    for ( i = 0 ; i < NRO_MEDIDAS ; i ++ ){
      // A funcao AnalogRead() demora 100 microssegundos para ser executada,
      // o que possibilita ate 10.000 amostras/segundo com essa abordagem
      vetor_medidas[i] = analogRead(PinoPotenciometro); // le dado com ADC de 10-bit
      delayMicroseconds(900);     // atraso adicional para 1.000 medidas por segundo
    }
    inicia_coleta = 0;
  }
}
