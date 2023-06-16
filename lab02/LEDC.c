#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define LED_AMARELO 16
#define LED_VERMELHO 20
#define LED_VERDE 21

void writeGPIO(char filename[], char value []){
    FILE* fp;
    fp = fopen(filename, "w+");
    fprintf(fp,"%s", value);
    fclose(fp);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Uso: %s <valor>\n", argv[0]);
        return 1;
    }

    int value = atoi(argv[1]);
    int i;

    exportGPIO(LED_AMARELO);
    exportGPIO(LED_VERMELHO);
    exportGPIO(LED_VERDE);
    usleep(500000);

    for (i = 0; i < 5; i++) {
        setGPIODirection(LED_VERMELHO, "out");
        setGPIOValue(LED_VERMELHO, value);
        usleep(2000000);
        setGPIOValue(LED_VERMELHO, 0);

        setGPIODirection(LED_VERDE, "out");
        setGPIOValue(LED_VERDE, value);
        usleep(1000000);
        setGPIOValue(LED_VERDE, 0);

        setGPIODirection(LED_AMARELO, "out");
        setGPIOValue(LED_AMARELO, value);
        usleep(1000000);
        setGPIOValue(LED_AMARELO, 0);
    }

    unexportGPIO(LED_VERMELHO);
    unexportGPIO(LED_VERDE);
    unexportGPIO(LED_AMARELO);

    return 0;
}
