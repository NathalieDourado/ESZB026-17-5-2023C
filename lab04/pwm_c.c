#include <stdio.h>
#include <wiringPi.h>
#include <softPwm.h>

int main(){
	int pino_PWM = 23;                         // pwm por software na GPIO23
	int brilho;
	int range = 100;                           // periodo do PWM = 100us*range
	wiringPiSetupGpio();                       // usar a numeracao GPIO, nao WPi
	pinMode(pino_PWM,OUTPUT);	           // configura GPIO23 como saida
	softPwmCreate(pino_PWM, 1, range);         // inicializa PWM por software
	while (1) {
		for (brilho = 0; brilho < range; brilho++) {
		  softPwmWrite (pino_PWM, brilho); // altera o duty cycle do PWM
		  delay (10) ;                     // aguarda 10ms
                }
		for (brilho = range; brilho > 0; brilho--) {
		  softPwmWrite (pino_PWM, brilho);
		  delay (10);
		}
	}
}
