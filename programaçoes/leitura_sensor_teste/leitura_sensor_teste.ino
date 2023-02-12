//USAR ESTE PROGRAMA 

#include "DFRobot_PH.h"
//#include "DFRobot_EC.h"  biblioteca para calibrar," enterph", "calph", "exitph"    BAIXAR
#include <EEPROM.h>

#define PH_PIN A1 //PORTA DO SENSOR
 
      
float voltage,phValue,temperature = 25;//variaveis

                                                                                  //para fazer//
                                                      //criar variavel pro valor dos sensores, usando o "CONST FLOAT"  -- FEITO
                                                      //pesquisar sobre a programação de temperatura(ver o video no teams) -- FEITO
                                                      //juntar a parte da placa LCD   -- FEITO     
                                                      //FAZER A ROTINA DO PROJETO(com base do Ph necessario)                                                                                                  
                                                      //biblioteca do "DFRobot_EC.h" --POR ENQUANTO NAO 


DFRobot_PH ph;

void setup()
{
    Serial.begin(115200);  
    ph.begin();
}

void loop()
{
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    static unsigned long timepoint = millis();
    if(millis()-timepoint>1000U){                 
        timepoint = millis();                      //tempo
        temperature = readTemperature();           // converte o valor de temperatura       (TIRAR DEPOIS)
        voltage = analogRead(PH_PIN)/1024.0*5000;  // voltagem
        phValue = ph.readPH(voltage,temperature);  // converter tensão em pH com compensação de temperatura

        
        Serial.print("temperature:");//jeito que vai aparecer no CMD
        Serial.print(temperature,1);  //usar isso para o lCD
        Serial.print("^C  pH:");
        Serial.println(phValue,2);
     }
////////////////////////////////////
//adionar a o display LCD
//se o Ph estiver < que 7, o LedPh vai acender  -- FEITO
//acender o ledSinal se estiver maior ou igual a 7
////////////////////////////////////   
     
       
    ph.calibration(voltage,temperature);           // calibrar para mandar para o CMD(monitor serial)
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


float readTemperature()
{
  //codigo da temperatura do sensor, caso queira usar outro sensor para medir a temperatura
}
