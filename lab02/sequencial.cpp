#include <stdio.h>
#include <wiringPi.h>

// LED_AMARELO Pin - wiringPi pin 27 is BCM_GPIO 16.
// LED_VERMELHO Pin - wiringPi pin 28 is BCM_GPIO 20.
// LED_VERDE Pin - wiringPi pin 29 is BCM_GPIO 21.
// Check lib documentation to see the respectives Wiring pins to GPIO

#define	LED_AMARELO	27
#define	LED_VERMELHO 28
#define LED_VERDE 29


int main (void)
{
  printf ("ta funcionando?\n") ;

  wiringPiSetup () ;
  pinMode (LED_AMARELO, OUTPUT) ;
  pinMode (LED_VERMELHO, OUTPUT) ;
  pinMode (LED_VERDE, OUTPUT) ;
  
int i = 0;
  while (i<5)
  {
    digitalWrite (LED_VERMELHO, HIGH) ;
    delay (2000) ;
    digitalWrite (LED_VERMELHO, LOW) ;
      
    digitalWrite (LED_VERDE, HIGH) ;
    delay (1000) ;
    digitalWrite (LED_VERDE, LOW) ;
      
    digitalWrite (LED_AMARELO, HIGH) ;
    delay (1000) ;
    digitalWrite (LED_AMARELO, LOW) ;
    i = i+1;
  }
  return 0 ;
}
