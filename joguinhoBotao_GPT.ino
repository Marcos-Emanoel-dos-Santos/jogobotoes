#define botAz 13
const int verde[] = {12, 11, 10};
const int vermelho[] = {7, 8, 9};
#define rgbVm 6
#define rgbVd 5
#define rgbAz 3
#define botVm 2

int pontoVm = 0;
int pontoAz = 0;
int cor[] = {0, 0, 0};
long numRand;
int clicar;

void defCor(int corAleatoria, int cor[3]) {
  if(corAleatoria == 0){
    cor[0] = 230; cor[1] = 250; cor[2] = 0; clicar = 0;  // Amarelo
  } else if (corAleatoria == 1) {
    cor[0] = 0; cor[1] = 250; cor[2] = 0; clicar = 1;  // Verde
  }
}

void clique(int jogador, int adversario) {
  if(clicar == 1){ // Verde
    if(jogador == botVm){
      pontoVm++;
      delay(200);
    };
    if(jogador == botAz){
      pontoAz++;
      delay(200);
    };
  }
  else if(clicar == 0){ // Amarelo
    if(jogador == botVm){
      pontoAz++;
      delay(200);
    }
    if(jogador == botAz){
      pontoVm++;
      delay(200);
    };
  };
}

void setup(){
  randomSeed(analogRead(0));
  Serial.begin(9600);

  int arrayOutputs[] = {3, 5, 6, 7, 8, 9, 10, 11, 12};
  for (int i = 0; i < 9; i++) {
    pinMode(arrayOutputs[i], OUTPUT);
  }
  pinMode(botVm, INPUT);
  pinMode(botAz, INPUT);
}

void loop(){
  while (pontoVm < 3 && pontoAz < 3) {
    numRand = random(2);
    defCor(numRand, cor);

    unsigned long tempo = millis();
    int br = 1;
    while(millis() < tempo + 700 && br == 1){
      analogWrite(rgbVm, cor[0]);
      analogWrite(rgbVd, cor[1]);
      analogWrite(rgbAz, cor[2]);

      if(digitalRead(botVm) == HIGH){
        clique(botVm, botAz);
        br = 0;
      }
      if(digitalRead(botAz) == HIGH){
        clique(botAz, botVm);
        br = 0;
      }

      for (int i = 0; i < 3; i++) {
      digitalWrite(vermelho[i], LOW);
      digitalWrite(verde[i], LOW);
      }
      for (int i = 0; i < pontoVm; i++) {
        digitalWrite(vermelho[i], HIGH);
      }
      for (int i = 0; i < pontoAz; i++) {
        digitalWrite(verde[i], HIGH);
      }
      
    }
    analogWrite(rgbVm, 0);
    analogWrite(rgbVd, 0);
    analogWrite(rgbAz, 0);

    for (int i = 0; i < 3; i++) {
      digitalWrite(vermelho[i], LOW);
      digitalWrite(verde[i], LOW);
    }
    for (int i = 0; i < pontoVm; i++) {
      digitalWrite(vermelho[i], HIGH);
    }
    for (int i = 0; i < pontoAz; i++) {
      digitalWrite(verde[i], HIGH);
    }

    Serial.print("Estado Vermelho: ");
    Serial.println(digitalRead(botVm));
    Serial.print("Estado Verde: ");
    Serial.println(digitalRead(botAz));
    delay(random(6)*400);
  }
  if(pontoAz == 3){
    analogWrite(rgbVm, 0);
    analogWrite(rgbVd, 0);
    analogWrite(rgbAz, 250);
    delay(750);
    analogWrite(rgbVm, 0);
    analogWrite(rgbVd, 0);
    analogWrite(rgbAz, 0);
    delay(750);
  }
  else if(pontoVm == 3){
    analogWrite(rgbVm, 250);
    analogWrite(rgbVd, 0);
    analogWrite(rgbAz, 0);
    delay(750);
    analogWrite(rgbVm, 0);
    analogWrite(rgbVd, 0);
    analogWrite(rgbAz, 0);
    delay(750);
  }
}
