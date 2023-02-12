int VQ; //variaveis pro sensor
int ConduPin = A1;

void setup() {
  analogReference(DEFAULT);//tensão de referência para a entrada analógica
  Serial.begin(9600);
  VQ = determineVQ(ConduPin);
  delay(1000);
}

void loop() {
  Serial.print("Leitura: "); //aonde vai mostrar a leitura
  Serial.print(readCurrent(ConduPin), 3);
  Serial.println(" mA");
  delay(150);
}

int determineVQ(int PIN) {
  Serial.print("Estimando a Media de coeficiente de tensao:");
  long VQ = 0;


  //le 1000 amostra para estabilizar o valor
  for (int i = 0; i < 10000; i++) {
    VQ += abs(analogRead(PIN));
    delay(1);
  }

  //calcula o valor e manda para o começo
  VQ /= 10000;
  Serial.print(map(VQ, 0, 1023, 0, 5000)); Serial.println(" mV");
  return int(VQ);
}

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
