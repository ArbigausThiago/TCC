////////////////CALIBRAR A VOLTAGEM APENAS///////////////////

 
int pH_Value; 
float Voltage;
//float Po;
void setup() 
{ 
  Serial.begin(9600);
  pinMode(pH_Value, INPUT); 
} 
 
void loop() 
{ 
  pH_Value = analogRead(A0); //porta do sensor A0
  Voltage = pH_Value * (5.0 / 1023.0); 
  Serial.println(Voltage); 
  delay(1000);
  
 /* Po = 7 + ((2.5 - Voltage) / 0.18); //calcular o Ph, a partir do 7, pq é a medida exata
  Serial.print("/tPH:"); 
  Serial.print(Po,3);
 */



  
}
