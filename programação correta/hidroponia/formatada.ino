//=============================================================================================================================================================================================
/*
                                                                         /// MEDIDAS ///

                                                                    arduino UNO
                                                      AGUA DESTILADA -- 5.000 5.300
                                                      AGUA NORMAL--5.000 5.700
                                                      REFRI --2.700 2.890

                                                                   arduino Mega
                                                      AGUA DESTILADA -- 5.600 5.800
                                                      AGUA NORMAL-- 6.800 7.100  - certo
                                                      REFRI --2.000 2.200
                                                      AGUA COM LIMAO -- 2.200 2.450

///////////////////////////////////////////////////
          ANOTAÇÃO
   SENSOR DE PH - 2,5V
   SENSOR DE CONDUT - 5V
   LCD - 5V
   RELE - 5V
///////////////////////////////////////////////                                                      
                                                      
*/
//=============================================================================================================================================================================================
//                                          BIBLIOTECA
//LCD NORMAL
//#include <LiquidCrystal.h> //biblioteca LCD
//LiquidCrystal lcd(12, 11, 5, 4, 3, 2);//pinos utilizados LCD

//lcd I2C
#include <LiquidCrystal_I2C.h>//roxo scl - azul sda
#include <Wire.h>
LiquidCrystal_I2C lcd(0x27, 16, 2); //modulo de display utilizado
//=============================================================================================================================================================================================



//===============================================================================================
//                                           VARIAVEIS 
//SENSOR
int ph_pin = A0; //porta do sersor
int ConduPin = A1; //porta do sensor de condutividade

//VARIAVEIS DE LEITURA
int VQ; //variaveis pro sensor
float voltage;
float Po; 
float dia;//variavel para armazenar o dia 

//PARA TEMPO
int T =0;
int descloro = 0;
int cloro = 0;
int nutri = 0;

//ALERTAS
int ledRuim = 10; //mostrar se o Ph esta baixo
int ledLigado = 8; //mostrar o Ph bom

//RELE
int releNutri = 7 ;      //para dispensar o Nutriente in1
int releDescloro = 6;   //para dispensar o descloro in2
int releCloro = 5;      //para dispensar o cloro in3  
 
//OUTRA ROTINA
void condutiv();
//===============================================================================================




//===============================================================================================
//////////////////////////////////////////////////////////////////////////////
/*                              INFORMAÇÕES NECESSARIAS PRA ESSE KRL
  -INT NUMEROS INTEIROS
  -FLOAT NUMERO QUEBRADO
  -DOUBLE MAIS PRECISO QUE O INT
  -unsigned int; se a leitura for de 0 até 65535.
  -FOR; se acontecer uma condição, ele vai fazer um bloco de comandos.
  -WHILE; vai fazer uma ação ate aontecer a condição delcarada.
  https://www.inf.pucrs.br/~pinho/LaproI/ComandosDeRepeticao/Repeticao.html
  https://www-arduino-cc.translate.goog/reference/en/language/structure/control-structure/dowhile/?_x_tr_sl=en&_x_tr_tl=pt&_x_tr_hl=pt-BR&_x_tr_pto=sc
//////////////////////////////////////////////////////////////////////////////
*/

//===============================================================================================
void setup(){
  analogReference(DEFAULT);
  Serial.begin(9600);

  //OUTRA ROTINA
  VQ = determineVQ(ConduPin);
  delay(1000);

  //LCD
  lcd.begin(16, 2);//coluna e linha
  lcd.init();//para iniciar o LCD I2C

  //ALERTAS
  pinMode(ledLigado, OUTPUT);//LED
  pinMode(ledRuim, OUTPUT);//LED  

 //PARA O RELE
  pinMode(releNutri, OUTPUT);//nutriente
  pinMode(releDescloro, OUTPUT);//diminuir o cloro
  pinMode(releCloro, OUTPUT);//para aumentar o cloro
  
}
//===============================================================================================




//===============================================================================================
void loop(){
//                                       COM A VARIAVEL MEDIR
  /*
    int medir = analogRead(ph_pin);  //vai ler a variavel
    Serial.print("medição: ");//MEDIDA
    Serial.print(medir);
  
  
    voltage = 5.0 / 1024.0* medir;//calculo pra voltagem
    Serial.print("/tVoltagem:");//mostrar o valor inteiro
    Serial.print(voltage, 3);
  */
//===============================================================================================
//                                      MEDIR A VOLTAGEM

  //CALCULA A VOLTAGEM
  ph_pin = analogRead(A0); //mostrar so dois digitos
  voltage = ph_pin * (5.0 / 1023.0);
  
   Serial.print("\tVoltagem:");
   Serial.println(voltage);
     
//===============================================================================================



//===============================================================================================
//                                      MEDIR O PH         

  //CALCULA O Ph                                        
  Po = 7 + ((2.5 - voltage) / 0.18); 
  
   Serial.print("\tPH:");
   Serial.println(Po);//mostrar so dois digitos
   
/////////////////////////////////////////////////////////////////
//PARA CHAMAR  A FUNÇÃO DO SENSOR DE CONDUTIVIDADE
{
   condutiv();
   } 
/////////////////////////////////////////////////////////////////
  Serial.println("");
  delay(2000); //tempo que vai aparecer as mensagens
//===============================================================================================



//===============================================================================================
//                                   FAZER A ROTINA
//                                       RELE
  //CONTADOR PARA FAZER A LEITURA DIARIA 
  if (millis() >=  dia + 1000000){
    T = 1;
    dia = millis();//reseta
    Serial.println("\tLigou rele");
  }
  
  if( T == 1 ){
  //DIMINUIR O Ph in2
    if(Po >= 7.00 & descloro == 0){
       digitalWrite(releDescloro, HIGH);
       Serial.println("\tAcionou descloro");
       delay(8000);
       Serial.println("");
       
    //PARA DESLIGAR
       digitalWrite(releDescloro, LOW);
       descloro = 1;   
       Serial.println("\tDesligou descloro");
       Serial.println("");
    }
    
  //AUMENTAR O Ph in3
    if(Po <= 4.50 & cloro == 0){
       digitalWrite(releCloro, HIGH);
       Serial.println("\tAcionou Cloro");
       delay(8000);
       
    //PARA DESLIGAR
       digitalWrite(releCloro, LOW);
       cloro = 1;
       Serial.println("\tDesligou cloro");
       Serial.println("");
    }
    
  //QUANDO FALTA NUTRIENTE in1
    if(readCurrent(ConduPin) <= 1.000 & nutri == 0){
       digitalWrite(releNutri, HIGH);
       Serial.println("\tAcionou nutriente");
       delay(4000);
       
    //PARA DESLIGAR
       digitalWrite(releNutri, LOW);
       nutri = 1;
       Serial.println("\tDesligou nutriente");
       Serial.println("");
    }   
    
  //para reiniciar
    T =0;
    
  //PARA DESLIGAR O RELE 
    descloro = 0;
    cloro = 0;
    nutri = 0;
    
    Serial.println("\tDesligou rele");
  }  
//================================================================================================



//================================================================================================
//                                   PARTE DO LCD INTEIRA
//MENSAGEM PRINCIPAL
  lcd.backlight();
  lcd.setCursor(3, 0);
  lcd.print("HIDROPONIA");

  
//valor do Ph que vai aparecer no Ph
  lcd.setCursor(0, 1);//vai aparecer na coluna 3 e lina 1
  lcd.print("Ph=");
  lcd.setCursor(3, 1);
  lcd.print(Po, 2);

  lcd.setCursor(7, 1);
  lcd.print(" ");


//corrente que vai aparecer no LCD
  lcd.setCursor(8, 1);
  lcd.print("mA=");
  lcd.setCursor(11, 1);
  lcd.print(readCurrent(ConduPin), 3);

  lcd.setCursor(15, 0);
  lcd.print("  ");
}
//===============================================================================================






//==============================================================================================================================================================================================
                                          //PARA O SENSOR DE CONDUTIVIDADE
void condutiv(){
//////////////////////////////////////////////////////////////////////////////
  Serial.print("\tLeitu:  "); 
  Serial.print(readCurrent(ConduPin), 3);
  Serial.println(" mA");
  delay(150);
}
//////////////////////////////////////////////////////////////////////////////
//AONDE VAI MOSTRAR A MEDIA 
 
  int determineVQ(int PIN) {
  Serial.print("Estimando a Media de coeficiente de tensao:");
  long VQ = 0;


//LE 10000 VEZES E ESTABILIZA O VALOR
  for (int i = 0; i < 10000; i++) {
    VQ += abs(analogRead(PIN));
    delay(1);
  }
//////////////////////////////////////////////////////////////////////////////
//CALCULA O VALOR E MANDA PARA O INICIO

  VQ /= 10000;
  Serial.print(map(VQ, 0, 1023, 0, 5000)); Serial.println("  mV");
  return int(VQ);
}
//////////////////////////////////////////////////////////////////////////////
//VAI ORDENAR QUAL TIPO DE CORRENTE É

float readCurrent(int PIN) {//ver se é corrente continua ou alternada 
  int current = 0;
  int sensitivity = 100;//muda para 100 se for ACS712-20A ou para 66 for ACS712-5A
  //le 200 vezes
  for (int i = 0; i < 200; i++) {
    current += abs(analogRead(PIN) - VQ);
    delay(1);
  }
  current = map(current / 200, 0, 1023, 0, 5000);
  return float(current) / sensitivity;
}
//////////////////////////////////////////////////////////////////////////////
//===============================================================================================================================================================================================
