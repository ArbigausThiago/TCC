//CALIBRAR A VOLTAGEM DO SERSOR
/*
                                                                                  
                                                                                  ////PARA FAZER////  

                                                                                  
                                                                          VER O QUANTO DE CORRENTE É 500 PPM                                                    
                                                                                                                                                                                                           
                                                                                                     
                                                      FAZER A ROTINA DO PROJETO(com base do Ph necessario)
                                                      -ficar desligado por um dia , e depois vai ver se precisa ou nao de nutriente(if...else)


                                                      
                                                    
                                                       

                                                      
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////                                                      
                                                                                ///ANOTAÇÃO///

                                                                                                                             
                                                      COMANDO QUE VE A MEDIA, VAI PEGAR AS 10 LEITURAS E FAZER UMA MEDIA DISTO EM 10 EM 10 SEGUNDOS
                                                      -https://www.aranacorp.com/pt/implementar-uma-media-movel-no-arduino/
                                                      -https://labdegaragem.com/forum/topics/duvida-como-fazer-m-dia-de-leitura-de-sensor
                                                      -https://labduino.blogspot.com/2011/08/calculando-media-com-o-arduino.html           
                                                                                                
                                                     
                                                      
                                                     //////////////// CALIBRAÇÃO DA TENSÃO 2.500 --ISSO/////////////////////////
                                                     

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////                                                      
                                                                              /// MEDIDAS ///
                                                                              
                                                                    arduino UNO
                                                      AGUA DESTILADA -- 5.000 5.300
                                                      AGUA NORMAL--5.000 5.700
                                                      REFRI --2.700 2.890

                                                                   arduino Mega
                                                      AGUA DESTILADA -- 5.600 5.800
                                                      AGUA NORMAL-- 6.800 7.100  em contato com os outros, fica entre 5.300 5.500
                                                      REFRI --2.000 2.200
                                                      AGUA COM LIMAO -- 2.200 2.450




//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                                            INFORMAÇÕES NECESSARIAS PRA ESSE KRL
//INT NUMEROS INTEIROS
//FLOAT NUMERO QUEBRADO
//DOUBLE MAIS PRECISO QUE O INT
unsigned int; se a leitura for de 0 até 65535


                                                      
                                                      
*/


#include <LiquidCrystal.h> //biblioteca LCD
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);//pinos utilizados LCD

///////////////////////////////////////TESTE////////////////////////////
/*/////////////////////NAO PRECISA//////////////////////////////////////  
#include <EEPROM.h>
#include "DFRobot_PH.h"  
DFRobot_PH ph;
//#define PH_PIN A1
*/
////////////////////////////////////////////////
 

////////////////////////////////NAO SEI SE VOU USAR///////////////////////// 

                    //USAR DEPOIS
int ledSinal = 8;//para mostrar se estiver funcionando (4:40 min)
int ledPh = 9;//vai ligar se estiver precisando de Ph



int ph_pin = A0; //porta do sersor    A7 NO MEGA



//////////////////////////////////////////////PRA FAZER A MEDIA//////////////////////////////////////////////////////////////


///unsigned int;//se a leitura for de 0 até 65535


float PPM;
///////////////////////////////////////////////////////////////////////////////////////////////////////////

float voltage,phValue,temperature = 25;//MUDAR  
int calculo =  1.000000;//valor do PPM, um milivolt é igual a 11.000000e-03 PPM 

//float Po, voltagem;// USANDO JA 
///////////////////////////////////////////////////////////////////////////

void setup()
{
  Serial.begin(9600);
  lcd.begin(16, 2);//coluna e linha 
  //ph.begin();//TIRAR DEPOIS
}


void loop() 
{      
/////////////////////////////MENSAGEM PRINCIPAL NO LCD///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  lcd.setCursor(1, 0);// vai aparecer na coluna 3 e linha 0
  lcd.print("VALORES");

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                     
                     

                     
/////////////////////////////////////////////////////////////////////////////////                    
                     int medir = analogRead(ph_pin);  //vai ler a variavel
                     Serial.print("medição: ");//MEDIDA
                     Serial.print(medir);
////////////////////////////////MEDIR A VOLTAGEM/////////////////////////////////
                     double voltagem = 5.0 / 1024.0 * medir;  //converter a medida e aparecer no CMD   double voltagem = 5 / 1024.0 * medir;
                     Serial.print("\tVoltagem: ");
                     Serial.print(voltagem, 3);
/////////////////////////////////MEDIR O PH//////////////////////////////////////
                     float Po;
                     Po = 7 + ((2.5 - voltagem) / 0.18);//variavel para o Ph //lcd.print((int)223);
                     Serial.print(" \tPH:");
                     Serial.print(Po, 3); 
////////////////////////////////////////////////////////////////////////////////

                     //                                       MEDIR O PPM

  PPM = (voltage * calculo); //calculo para descobrir o PPM com base na voltagem
  Serial.print("     \tPPM:");
  Serial.print(PPM);







///////////////////////////////////MEDIR A TEMPERATURA//////////////////////////
/*         //ARRUMAR AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA TIRARRRRRRRRRRRRRRRRRRR
 static unsigned long timepoint = millis();
 if(millis()-timepoint>1000U){      
  timepoint = millis();
  temperature = readTemperature();           // converte o valor de temperatura
  voltagem = analogRead(ph_pin)/1024.0*5000;
  Po = ph.readPH(voltagem,temperature);  // converter tensão em pH com compensação de temperatura

    Serial.print("      temperatura:");//jeito que vai aparecer no CMD
    Serial.print(temperature,1);  //usar isso para o lCD       
    }*/
///////////////////////////////////////////////////////////////////////////    

//////////////////////////////////////////////////////////////////////////
  Serial.println("");
  delay(1000);//tempo que vai aparecer as mensagens 
/////////////////////////////////////////////////////////////////////////////














////////////////////////////////////DISPLAY LCD///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//valor do Ph que vai aparecer no Ph    
/*
  lcd.setCursor(9, 0);//vai aparecer na coluna 3 e lina 1
  lcd.print("Ph=");
  lcd.setCursor(12, 0);
  lcd.print(Po,2); 
  */
//////////////////////voltgem que vai aparecer no LCD 
  lcd.backlight();
  lcd.setCursor(3, 0);
  lcd.print("HIDROPONIA");

lcd.setCursor(4, 1);
lcd.print("Volt=");
lcd.setCursor(8, 1);
lcd.print(voltagem, 3); 
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////  
//////////////////temperatura que vai aparecer no LCD  
/*
lcd.setCursor(12,10);
lcd.print("^C=");//temperatura
lcd.setCursor(16,1);
lcd.print(temperature, 1);*/
//////////////////////////////////////////////////////////////////////////





                                                                            
                                  //ADICONAR NA OUTTA PROGRAMAÇÃO
///////////////////////////////////////TESTE//////////////////////////////////////////////////////////////////////////////////////////////////////// /

/*  
 if(Po>=7) { //se o Ph estiver maior ou igual a 7 vai mostrar que esta bom
  lcd.setCursor(2, 1);
  lcd.print("REGULADO");   //ledSinal vai ligar quando o Ph estiver regulado CONDIÇÃO 1
  digitalWrite(ledSinal, HIGH);
  //delay(5000);//nao sei se é necessario
  }
else if(Po<=6) {//se o Ph estiver meneor ou igual a 6, vai mostrar que precisa de ajsutes
  lcd.setCursor(2, 0);
  lcd.print("PRECISA");
  lcd.setCursor(2, 1);
  lcd.print("CUIDADO");
  digitalWrite(ledPh, HIGH);
  digitalWrite(ledSinal, HIGH);
}
else(Po<5.5); { //se Ph estiver menor que 7, ira aparecer uma mensagem e o led vermelho vai acender
  lcd.setCursor(2, 1);
  lcd.print("ALERTA");
  digitalWrite(ledPh, HIGH);
  //delay(5000);
 }*/
  
 }
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////





////////////////////////////////////////TESTE///////////////////////////////////
            //////TIRARRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRRR//////////
/*float readTemperature()
{
  //codigo da temperatura do sensor, caso queira usar outro sensor para medir a temperatura
}*/
