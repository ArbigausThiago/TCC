//POR ENQUANTO NAO USAR

#include "DFRobot_PH.h" //biblioteca do sensor de Ph
#include <OneWire.h>  //biblioteca do sensor
#include <DallasTemperature.h> // para medir a temperatura 
 ////////////////////////////////
#define sensor_ds18b20 2 //pin 2 sensor ds18b20
 ///////////////////////////////
OneWire oneWire(sensor_ds18b20);
 
DallasTemperature sensors(&oneWire);
 
int sensorPin = A0;//porta do sensor

float voltagem,valorph,temperatura; //voltagem   mediçãoPh  temperatura
DFRobot_PH ph;
 
void setup()
{
   Serial.begin(9600);  
   ph.begin(); 
   sensors.begin(); 
}
 
void loop()
{
  sensors.requestTemperatures(); 
  static unsigned long timepoint = millis();
    if(millis()-timepoint>1000U){ // tempo que vai passar as informaçoes no monitor serial                 
        timepoint = millis();//tempo
        voltagem = analogRead(sensorPin)/1024.0*5000;
        temperatura = sensors.getTempCByIndex(00);
        valorph = ph.readPH(voltagem,temperatura); 
/////////////////////////////////////////////////////////////////////////
        Serial.print("Celsius temperatura: ");
        Serial.print(temperatura,1);                                         
        Serial.print("^C  pH:");                                 //usar como exemplo
        Serial.println(valorph,2);
/////////////////////////////////////////////////////////////////////////
    }
    ph.calibration(voltagem,temperatura); 
}
