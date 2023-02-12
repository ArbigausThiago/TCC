#include <LiquidCrystal_I2C.h>//roxo scl - azul sda
#include <Wire.h>
LiquidCrystal_I2C lcd(0x27, 16, 2); //modulo de display utilizado

int ph_pin = A0; //porta do sersor
int ConduPin = A1; //porta do sensor de condutividade
int VQ; //variaveis pro sensor
float voltage;
float Po; 


//===============================================================================================
void setup(){
  analogReference(DEFAULT);//tensão de referência para a entrada analógica
  Serial.begin(9600);
  
  
  lcd.begin(16, 2);//coluna e linha
  lcd.init();//para iniciar o LCD I2C
}




void loop(){
//===============================================================================================
//                                      MEDIR A VOLTAGEM
  ph_pin = analogRead(A0); //mostrar so dois digitos
  voltage = ph_pin * (5.0 / 1023.0);
  Serial.print("\tVoltagem:");
  Serial.println(voltage);

  //===============================================================================================
//                                      MEDIR O PH         
                                          
  Po = 7 + ((2.5 - voltage) / 0.18); //calcular o Ph, a partir do 7, pq é a medida exata
   Serial.print("\tPH:");
   Serial.println(Po);//mostrar so dois digitos

   Serial.println("");
  delay(2000); //tempo que vai aparecer as mensagens

//===============================================================================================

lcd.backlight();
lcd.setCursor(3, 0);
lcd.print("HIDROPONIA");

lcd.setCursor(4, 1);
lcd.print("Volt=");
lcd.setCursor(8, 1);
lcd.print(voltage, 3); 
}
     
