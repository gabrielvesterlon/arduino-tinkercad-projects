#include <Wire.h>

#include <LiquidCrystal_I2C.h>

//ajustando para endereço 0x20
LiquidCrystal_I2C lcd(0x20, 16,2);

const int sensorPin = A0;
const int buzzerPin = 8;

void setup(){
  lcd.init(); //inicializa o display
  lcd.backlight(); //luz de fundo
  pinMode(buzzerPin, OUTPUT);
  
  lcd.setCursor(0,0);
  lcd.print("Lendo Temp...");
  delay(1000);
}

void loop(){
  //lógica p ler o sensor TMP36
  int leitura = analogRead(sensorPin);
  float tensao = leitura * (5.0 / 1024.0);
  float temperatura = (tensao - 0.5) * 100;
  
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Temp.: ");
  lcd.print(temperatura);
  lcd.print(" C");
  
  //alarme p caso a temperatura suba mto
  if (temperatura > 35.0){
    lcd.setCursor(0,1);
    lcd.print("ALERTA: QUENTE!");
    tone(buzzerPin, 800, 500);
  }
  
  delay(1000); //espera 1 segundo para próxima leitura
}
