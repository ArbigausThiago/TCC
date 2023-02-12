#include <Wire.h>
#include <LiquidCrystal.h> //biblioteca LCD
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);//pinos utilizados LCD

//como fazer pra ele ler ter algo que acione


//mudar depois 
//float phValue, temperature; //variaveis  (APAGAR QUANDO FOR MANDAR PARA A OUTRA PROGRAMAÇÃO)

float Po, voltagem, temperature ;//CERTO(TIRAR DEPOIS)

////////////////////////////////     NAO SEI SE VOU USAR
int ledSinal = 8;//para mostrar se estiver funcionando (4:40 min)
int ledPh = 9;//vai ligar se estiver precisando de Ph
///////////////////////////////

void setup() 
{
  lcd.begin(16, 2);//coluna e linha 
}

void loop() {

//lcd.clear();//limpar oq esta no display
  
//MENSAGEM PRINCIPAL 
  lcd.setCursor(1, 0);// vai aparecer na coluna 3 e linha 0
  lcd.print("VALORES");



//valor do Ph que vai aparecer no Ph    ADICIONAR NA OUTRA PROGRAMAÇÃO -- CERTO
  lcd.setCursor(9, 0);//vai aparecer na coluna 3 e lina 1
  lcd.print("Ph=");
  lcd.setCursor(12, 1);
  lcd.print(Po,2); 


//voltgem que vai aparecer no LCD  ADICONAR  NA OUTRA PROGRAMAÇÃO --CERTO
lcd.setCursor(1, 1);
lcd.print("Volt=");
lcd.setCursor(6, 1);
lcd.print(voltagem, 3); 


  
//temperatura que vai aparecer no LCD  ADICIONAR NA OUTRA PROGRAMAÇÃO --CERTO
/*
lcd.setCursor(12,10);
lcd.print("^C=");//temperatura
lcd.setCursor(16,1);
lcd.print(temperature, 1);
*/


  
  
//////////////////////////////////////////////////////// TESTE//////////////
/*
 if(Po<7){ //se Ph estiver menor que 7, ira aparecer uma mensagem e o led vermelho vai acender
  lcd.setCursor(2, 1);
  lcd.print("ALERTA");
  digitalWrite(ledPh, HIGH);
  delay(5000);
 }

 if(Po>7){ //ledSinal vai ligar quando o Ph estiver regulado
  lcd.setCursor(2, 1);
  lcd.print("REGULADO");
  digitalWrite(ledSinal, HIGH);
  delay(5000);//nao sei se é necessario
  }
 */
  //FAZER A ROTINA
  
 }
