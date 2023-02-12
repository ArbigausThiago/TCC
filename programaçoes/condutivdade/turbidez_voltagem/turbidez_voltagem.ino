#include <Wire.h>

// Define o pino de Leitura do Sensor
int SensorTurbidez = A0;
 
// Inicia as variáveis
int i;
float voltagem;
float NTU;

void setup(){
  Serial.begin(9600);
}


void loop(){
  voltagem = 0;

  // Realiza a soma dos "i" valores de voltagem
for (i = 0; i < 800; i++) {
voltagem += ((float)analogRead(SensorTurbidez) / 1023) * 5;
}

// Realiza a média entre os valores lidos na função for acima
voltagem = voltagem / 800;

Serial.print("Leitura V: ");
Serial.println(voltagem);

delay(2000);

}
