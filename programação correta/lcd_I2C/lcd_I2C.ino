#include <LiquidCrystal_I2C.h>
#include <Wire.h>
LiquidCrystal_I2C lcd(0x27,16,2);//modulo de display utilizado


float Po, voltagem, temperature ;

void setup()
{
  lcd.init();//para iniciar o LCD
 
}
void loop()
{
  //MENSAGEM PRINCIPAL
  lcd.backlight();
  lcd.setCursor(1, 0);
  lcd.print("VALORES");

  //valor do Ph que vai aparecer no Ph    ADICIONAR NA OUTRA PROGRAMAÇÃO -- CERTO
  lcd.setCursor(9, 0);//vai aparecer na coluna 3 e lina 1
  lcd.print("Ph=");
  lcd.setCursor(12, 0);
  lcd.print(Po,2); 

  //voltgem que vai aparecer no LCD  ADICONAR  NA OUTRA PROGRAMAÇÃO --CERTO
  lcd.setCursor(7, 1);
  lcd.print("Volt=");
  lcd.setCursor(12, 1);
  lcd.print(voltagem, 3); 
}
