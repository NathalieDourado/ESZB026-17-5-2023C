/** Programa baseado no código disponibilizado em:
* Derek Molloy, Exploring Raspberry Pi: Interfacing to the Real World with Embedded Linux,
* Wiley 2016, ISBN 978-1-119-1868-1, http://www.exploringrpi.com/
*/
// Nao otimize este codigo usando -O3

#include <wiringPi.h>
#include <iostream>
using namespace std;
#define LED_GPIO  23                   // Usando LED na GPIO23, pino 16

int main() {
   wiringPiSetupGpio();                // usar a numeracao GPIO, nao WPi
   cout << "Iniciando o chaveamento do LED" << LED_GPIO << endl;
   pinMode(LED_GPIO, OUTPUT);          // ajusta a GPIO23 como saida
   for(int x = 0; x < 2000000; x++){     // 2000000 iteracoes
      digitalWrite(LED_GPIO, HIGH);    // LED ligado
      for(int i=0; i<50; i++) { }      // incluindo atraso
      digitalWrite(LED_GPIO, LOW);     // LED desligado
      for(int i=0; i<49; i++) { }      // incluindo atraso
   }
   return 0;                           // saindo
}
