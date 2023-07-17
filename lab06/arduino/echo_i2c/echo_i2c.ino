// Programa baseado no codigo disponibilizado em:
// Derek Molloy, Exploring Raspberry Pi: Interfacing to the Real World with Embedded Linux,
// Wiley 2016, ISBN 978-1-119-1868-1, http://www.exploringrpi.com/

#include <Wire.h>                  // Inclui bibliotecas da I2C, ou Two-Wire Interface (TWI)

const byte slaveAddr = 0x44;       // guarda o endereco escravo do Arduino
int dado;                          // guarda o dado recebido
 
void setup() {                     // configura o Arduino
  TWBR=10000L;                     // a frequencia do i2c: 10000L = 10kHz
  Wire.begin(slaveAddr);           // configura o Arduino como um dispositivo escravo
  Wire.onReceive(receiveData);     // ajusta a funcao chamada ao receber um dado
  Wire.onRequest(respondData);     // ajusta a funcao chamada para responder
}

void loop() {                       
  delay(1000);                     // loop a cada segundo, nao precisa fazer nada
}                     
 
void receiveData(int x){           // funcao chamada ao receber um dado
  dado = Wire.read();              // le um endereco da RaspberryPi
}
 
void respondData(){                // funcao chamada para responder
  delay(1);                        // pode ser necessario em velocidades de comunicacao mais altas
  Wire.write(dado);                // envia o endereco recebido de volta para a RasberryPi
}
