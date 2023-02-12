#include <Wire.h>
#include <LiquidCrystal_I2C.h>
 
// Inicia o Display LCD 16x2 através do endereço 0x27
LiquidCrystal_I2C lcd(0x27, 16, 2);
 
// Define o pino de Leitura do Sensor
int SensorTurbidez = A0;
 
// Inicia as variáveis
int i;
float voltagem;
float NTU;
 
 
void setup() {
// Inicia o display LCD
lcd.init();
lcd.backlight();
Serial.begin(9600);
}
 
void loop() {
// Inicia a leitura da voltagem em 0
voltagem = 0;
 
// Realiza a soma dos "i" valores de voltagem
for (i = 0; i < 800; i++) {
voltagem += ((float)analogRead(SensorTurbidez) / 1023) * 5;
}
 
// Realiza a média entre os valores lidos na função for acima
voltagem = voltagem / 800;
voltagem = ArredondarPara(voltagem, 1);
 
// Se Voltagem menor que 2.5 fixa o valor de NTU
if (voltagem < 2.5) {
NTU = 3000;
}
 
else if (voltagem > 4.2) {
NTU = 0;
voltagem = 4.2;
}
 
// Senão calcula o valor de NTU através da fórmula
else {
NTU = -1120.4 * square(voltagem) + 5742.3 * voltagem - 4353.8;
}
//////////////////////////
Serial.print("Leitura: ");
Serial.print(voltagem);
Serial.print(" V ");
delay(2000);

 Serial.print("  ");
 
 Serial.print(NTU);
 Serial.print(" NTU");
 delay(2000);

Serial.println("");
///////////////////////// 
// Imprime as informações na tela do LCD
lcd.clear();
lcd.setCursor(0, 0);
lcd.print("Leitura: ");
lcd.print(voltagem);
lcd.print(" V");
 
// Imprime as informações na tela do LCD
lcd.setCursor(3, 1);
lcd.print(NTU);
lcd.print(" NTU");
delay(10);
}
 
// Sistema de arredendamento para Leitura
float ArredondarPara( float ValorEntrada, int CasaDecimal ) {
float multiplicador = powf( 10.0f, CasaDecimal );
ValorEntrada = roundf( ValorEntrada * multiplicador ) / multiplicador;
return ValorEntrada;
}
