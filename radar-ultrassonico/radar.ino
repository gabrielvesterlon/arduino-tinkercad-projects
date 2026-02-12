#include <Wire.h>
#include <LiquidCrystal_I2C.h>


LiquidCrystal_I2C lcd(0x20,16,2);

const int trigPin = 9;
const int echoPin = 10;
const int buzzerPin = 8;
const int ledRed = 11;
const int ledGreen = 12;
const int ledBlue = 13;


void setup(){
  lcd.init(); // inicializa o chip interno do display
  lcd.backlight(); // liga o fundo azul do display
  
  pinMode(trigPin,OUTPUT); // define o gatilho como saída (envia o pulso)
  pinMode(echoPin,INPUT); // define o eco como entrada (recebe o pulso)
  pinMode(buzzerPin, OUTPUT); 
  pinMode(ledRed, OUTPUT);
  pinMode(ledGreen, OUTPUT);
  pinMode(ledBlue, OUTPUT);
  
  
  lcd.setCursor(0,0);
  lcd.print("Radar de re");
  delay(1000);
}

void loop(){
  // inicio da medição
  digitalWrite(trigPin, 0); // garante o pino do gatilho começando desligado
  delayMicroseconds(2);
  digitalWrite(trigPin, 1); // envia pulso sonoro de alta frequência
  delayMicroseconds(10);
  digitalWrite(trigPin, 0); // desliga o pulso
  
  // a função pulseIn mede qt tempo o pino echoPin ficou ligado (esperando o sinal voltar)
  long duracao  = pulseIn(echoPin, 1);
  
  // cálculo da distância em cm, v = s/t > s = v*t: (tempo* velocidade do som)/2
  // usamos 0.034 pois 340m/s vira 0.034 cm/ms
  // divide por 2 pq o som vai, bate no objeto e volta
  
  int distancia = (duracao*0.034)/2;
  // fim da medição
  
  // mensagem no display
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Dist.: ");
  lcd.print(distancia);
  lcd.print(" cm");
  
  //lógica de alerta
 if (distancia < 20){ //distancia pequena
    digitalWrite(ledRed,1);
    digitalWrite(ledGreen,0);
   	digitalWrite(ledBlue,0);
    tone(buzzerPin, 2000); 
    delay(300);
    noTone(buzzerPin); // desliga para efeito bip bip
    delay(100);
    lcd.setCursor(0,1); // segunda linha do lcd
    lcd.print("Cuidado!");
  }
  else if (distancia >=20 && distancia <50){ //distancia média
    digitalWrite(ledRed,0);
    digitalWrite(ledGreen,0);
    digitalWrite(ledBlue,1);
    tone(buzzerPin,2000);
    delay(300);
    noTone(buzzerPin);
    delay(300);
    lcd.setCursor(0,1);
    lcd.print("Cuidado!");
  }
  else {
    digitalWrite(ledGreen,1);
    digitalWrite(ledRed,0);
    digitalWrite(ledBlue,0);
    noTone(buzzerPin);
    lcd.setCursor(0,1);
    lcd.print("Livre");
    delay(500);
  }
}

    
