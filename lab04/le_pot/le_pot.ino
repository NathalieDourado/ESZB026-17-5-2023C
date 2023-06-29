const int analogInPin = A0;                  // o potenciômetro esta ligado ao pino A0

void setup(){
   // Configura a serial: baud rate de 115200, 8-bit, sem paridade, 1 stop bit
   Serial.begin(115200, SERIAL_8N1);
}

void loop(){
   int valor = analogRead(analogInPin);      // le valor no pino A0 usando conversor ADC de 10-bit
   int potencial = (valor/1023.0f)*100.0f; // converte o valor lido em potencial
   Serial.print(potencial);
   Serial.print("\n");
   delay(100);
}
