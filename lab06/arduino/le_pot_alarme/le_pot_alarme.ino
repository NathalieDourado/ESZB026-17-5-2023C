// Programa baseado no codigo disponibilizado em:
// Derek Molloy, Exploring Raspberry Pi: Interfacing to the Real World with Embedded Linux,
// Wiley 2016, ISBN 978-1-119-1868-1, http://www.exploringrpi.com/

#include <Wire.h>                  // Inclui bibliotecas da I2C, ou Two-Wire Interface (TWI)
const byte enderecoEscravo = 0x40; // guarda o endereco escravo do Arduino
const int PinoPotenciometro = A0;  // pino analogico ligado ao potenciometro
const int pinoLED = LED_BUILTIN;   // pino do LED do alarme (LED na placa do Arduino)
int dadoRecebido;                  // guarda o dado recebido
int limiteAlarme = 0;              // limite do alarme
int valorPot = 0;                  // guarda o valor lido no potenciometro
byte buffer[5];                    // guarda o valor lido, limite de alarme e valor do LED
 
void setup(){
  pinMode(pinoLED, OUTPUT);        // usar um LED como alarme
  TWBR=10000L;                     // a frequencia do i2c: 10000L = 10kHz
  Wire.begin(enderecoEscravo);     // configura o Arduino como um dispositivo escravo
  Wire.onReceive(funcaoDadoRecebido); // ajusta a funcao chamada ao receber um dado
  Wire.onRequest(funcaoResposta);  // ajusta a funcao chamada para responder
  Serial.begin(9600, SERIAL_8N1);         // opcional, para debug
  Serial.println("Fim da configuracao!"); // opcional, para debug
}

void enviaDadosPelaSerial(){              // opcional, para debug
  Serial.print("Valor lido: "); Serial.print(valorPot);
  Serial.print("; limite do alarme: "); Serial.print(limiteAlarme);
  Serial.print("; e buffer = 0x");
  Serial.print(buffer[0],HEX); Serial.print(" "); // byte menos significativo do valor lido
  Serial.print(buffer[1],HEX); Serial.print(" "); // byte mais significativo do valor lido
  Serial.print(buffer[2],HEX); Serial.print(" "); // byte menos significativo do alarme
  Serial.print(buffer[3],HEX); Serial.print(" "); // byte mais significativo do alarme
  Serial.println(buffer[4],HEX);                  // valor ajustado no LED
}

void loop(){                       // Le o valor no potenciometro a cada 1 segundo
  valorPot = analogRead(PinoPotenciometro); // le dado com ADC de 10-bit
  buffer[0] = valorPot & 0xFF;     // byte menos significativo
  buffer[1] = valorPot >> 8;       // byte mais significativo
  if (valorPot >= limiteAlarme) {  // verifica limite de alarme
     digitalWrite(pinoLED, HIGH);  // liga o LED do alarme
     buffer[4] = 0x01;
  }
  else {
     digitalWrite(pinoLED, LOW);   // desliga o LED do alarme
     buffer[4] = 0x00;
  }
  enviaDadosPelaSerial();          // opcional, para debug
  delay(1000);
}                     
 
void funcaoDadoRecebido(int x){    // funcao chamada ao receber um dado
  dadoRecebido = Wire.read();      // le um byte de dado pelo TWI
  
  if( dadoRecebido == 0x02 && x == 3 ){  // se for alteracao do limite do alarme
    byte dado1 = Wire.read();      // le byte menos significativo
    byte dado2 = Wire.read();      // le byte mais significativo
    int valorRecebido =  dado1 | ( dado2 << 8 );
    if ( valorRecebido >= 0 && valorRecebido <= 1023) {
      buffer[2] = dado1;
      buffer[3] = dado2;
      limiteAlarme = valorRecebido;
    }
  }
}
 
void funcaoResposta(){             // funcao chamada para responder
  byte resposta = 0x00;
  if ( dadoRecebido >= 0x00 && dadoRecebido <= 0x04 ){
    resposta = buffer[dadoRecebido];
  }
  delay(1);                        // pode ser necessario em velocidades de comunicacao mais altas
  Wire.write(resposta);            // envia um byte de dado pelo TWI
}
