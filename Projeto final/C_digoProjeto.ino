#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Tone.h>
#define SCREEN_WIDTH 128 // OLED display width, em pixels
#define SCREEN_HEIGHT 64
//Declaração para conexão I2C
#define OLED_RESET  -1 //Reseta o pin
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#include "img.h"
#include "tone.h"


const int pinoPrimeiraChave = 10;
const int pinoSegundaChave = 9;
const int pinoTerceiraChave = 6;
const int pinoQuartaChave = 7;
const int pinoQuintaChave = 8;
const int pinoLed = 12;
const int buzzer = 13;
const int pinoButton = 11;
const int pinoMagDigital = 5;
const int pinoMagAnalog = A0;
const int pinoOledSCL = A4;
const int pinoOledSDA = A5;

void setup() {
pinMode(pinoPrimeiraChave, INPUT_PULLUP); //DEFINE O PINO COMO ENTRADA / "_PULLUP" É PARA ATIVAR O RESISTOR INTERNO
pinMode(pinoSegundaChave, INPUT_PULLUP);
pinMode(pinoTerceiraChave, INPUT_PULLUP);
pinMode(pinoQuartaChave, INPUT_PULLUP);
pinMode(pinoQuintaChave, INPUT_PULLUP);
pinMode(pinoMagDigital, INPUT);
pinMode(pinoLed, OUTPUT); //Define como saída
pinMode(buzzer, OUTPUT); //Define como saída
pinMode(pinoButton, INPUT);
digitalWrite(pinoButton, LOW);
digitalWrite(buzzer, LOW); //Buzzer inicia desligado
digitalWrite(pinoLed, LOW); //Led inicia desligado
display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
display.clearDisplay();
Serial.begin(115200); // Inicializa a comunicação serial com taxa de transmissão de 9600 bps
configureToneTimer();
}


void loop(){
  byte valor_d=digitalRead(pinoMagDigital);
  int valor_a=analogRead(pinoMagAnalog);
  byte chave1=digitalRead(pinoPrimeiraChave);
  byte chave2=digitalRead(pinoSegundaChave);
  byte chave3=digitalRead(pinoTerceiraChave);
  byte chave4=digitalRead(pinoQuartaChave);
  byte chave5=digitalRead(pinoQuintaChave);

  byte posicao;

  
  if(chave1==LOW and chave4==LOW){
      //Sem necessidade de alarme/
      digitalWrite(pinoLed, LOW);
      digitalWrite(buzzer, LOW);
      setFrequencytone(0); //
      display.drawBitmap(0, 0, ladoesquerdo, 128, 64, WHITE); //Atualiza oled
      display.display();
      delay(1000); //Aguarda por 1 segundo
      display.clearDisplay(); //Limpa o buffer
      posicao = 1;
  }else if (chave2==LOW && chave5==LOW){ 
      //Sem necessidade de alarme/
      digitalWrite(pinoLed, LOW);
      digitalWrite(buzzer, LOW);
      setFrequencytone(0); //
      //Serial.println("Lado direito");
      display.drawBitmap(0, 0, ladodireito, 128, 64, WHITE); //Atualiza oled
      display.display();
      delay(1000); //Aguarda por 1 segundo
      display.clearDisplay(); //Limpa o buffer
      posicao = 2;
  }else if (chave1==LOW && chave3==LOW && chave5==LOW){ 
      //Sem necessidade de alarme/
      digitalWrite(pinoLed, LOW);
      digitalWrite(buzzer, LOW);
      setFrequencytone(0); //
      //Serial.println("Diagonal esquerda");
      display.drawBitmap(0, 0, diagesquerda, 128, 64, WHITE); //Atualiza oled
      display.display();
      delay(1000); //Aguarda por 1 segundo
      display.clearDisplay(); //Limpa o buffer
      posicao = 3;
  }else if (chave2==LOW && chave3==LOW && chave4==LOW){ 
      //Sem necessidade de alarme/
      digitalWrite(pinoLed, LOW);
      digitalWrite(buzzer, LOW);
      setFrequencytone(0); //
      //Serial.println("Diagonal direita");
      display.drawBitmap(0, 0, diagdireita, 128, 64, WHITE); //Atualiza oled
      display.display();
      delay(1000); //Aguarda por 1 segundo
      display.clearDisplay(); //Limpa o buffer
      posicao = 4;
  }else if (chave1==HIGH && chave2==HIGH && chave3==HIGH && chave4==HIGH && chave5==HIGH){ 
      digitalWrite(pinoLed, HIGH);
      setFrequencytone(555); //
      //tone(buzzer,265,100);
      digitalWrite(buzzer, HIGH);
      //Serial.println("Bebê fora do berço!");
      display.drawBitmap(0, 0, foraberco, 128, 64, WHITE); //Atualiza oled
      display.display();
      delay(1000); //Aguarda por 1 segundo
      display.clearDisplay(); //Limpa o buffer
      posicao = 5;
  }else if (valor_d==1){
      digitalWrite(pinoLed, HIGH);
      digitalWrite(buzzer, HIGH);
      setFrequencytone(600); //
      //Serial.println("Alerta: Risco de asfixia!");
      display.drawBitmap(0, 0, asfixia, 128, 64, WHITE); //Atualiza oled
      display.display();
      delay(1000); //Aguarda por 1 segundo
      display.clearDisplay(); //Limpa o buffer
      posicao = 6;
  }else if (chave1==LOW){ 
      digitalWrite(pinoLed, HIGH);
      digitalWrite(buzzer, LOW);
      setFrequencytone(0); //
      //Serial.println("Atenção: risco de queda!");
      display.drawBitmap(0, 0, riscoqueda, 128, 64, WHITE); //Atualiza oled
      display.display();
      delay(1000); //Aguarda por 1 segundo
      display.clearDisplay(); //Limpa o buffer
      posicao = 7;
  }else if (chave5==LOW){ 
      digitalWrite(pinoLed, HIGH);
      digitalWrite(buzzer, LOW);
      setFrequencytone(0); //
      //Serial.println("Atenção: risco de queda!");
      display.drawBitmap(0, 0, riscoqueda, 128, 64, WHITE); //Atualiza oled
      display.display();
      delay(1000); //Aguarda por 1 segundo
      display.clearDisplay(); //Limpa o buffer
      posicao = 8;
  }else if (chave2==LOW){ 
      digitalWrite(pinoLed, HIGH);
      digitalWrite(buzzer, LOW);
      setFrequencytone(0); //
      //Serial.println("Atenção: risco de queda!");
      display.drawBitmap(0, 0, riscoqueda, 128, 64, WHITE); //Atualiza oled
      display.display();
      delay(1000); //Aguarda por 1 segundo
      display.clearDisplay(); //Limpa o buffer
      posicao = 9;
  }else if (chave4==LOW){
      digitalWrite(pinoLed, HIGH);
      digitalWrite(buzzer, LOW);
      setFrequencytone(0); //
      //Serial.println("Atenção: risco de queda!");
      display.drawBitmap(0, 0, riscoqueda, 128, 64, WHITE); //Atualiza oled
      display.display();
      delay(1000); //Aguarda por 1 segundo
      display.clearDisplay(); //Limpa o buffer
      posicao = 10;
  }else if (chave3==LOW){
      //Sem necessidade de alarme/
      digitalWrite(pinoLed, LOW);
      digitalWrite(buzzer, LOW);
      setFrequencytone(0); //
      //Serial.println("No centro");
      display.drawBitmap(0, 0, nocentro, 128, 64, WHITE); //Atualiza oled
      display.display();
      delay(1000); //Aguarda por 1 segundo
      display.clearDisplay(); //Limpa o buffer
      posicao = 11;
  }
  else{
    //Sem necessidade de alarme/
    digitalWrite(buzzer, LOW);
      setFrequencytone(0); //
    //Serial.println("Erro no sistema!");
    display.drawBitmap(0, 0, errosistema, 128, 64, WHITE); //Atualiza oled
    display.display();
    delay(1000); //Aguarda por 1 segundo
    display.clearDisplay(); //Limpa o buffer
    posicao = 99;
  }

  if( Serial.available() ){
      byte charIn = Serial.read();
      if (charIn == '1'){ 
          Serial.write(chave1);
          Serial.write(chave2);
          Serial.write(chave3);
          Serial.write(chave4);
          Serial.write(chave5);
          Serial.write(valor_d);
          Serial.write(posicao);
      }
  }
  
}
