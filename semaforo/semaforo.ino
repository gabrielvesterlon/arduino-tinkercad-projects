// definindo variáveis
const int carroVermelho = 13;
const int carroAmarelo = 12;
const int carroVerde = 11;
const int pedVermelho = 7;
const int pedVerde = 6;
const int botao = 2;



//acontece sempre ao inicializar
void setup() {
  //botão entrada
  pinMode(botao,INPUT);
  
  //leds saída
  pinMode(carroVermelho,OUTPUT);
  pinMode(carroAmarelo,OUTPUT);
  pinMode(carroVerde,OUTPUT);
  pinMode(pedVermelho,OUTPUT);
  pinMode(pedVerde,OUTPUT);
  
  //estado default; carros andando e pedestres esperam
  digitalWrite(carroVerde,1);
  digitalWrite(pedVermelho,1);
}

void loop() {
  //verifica se o botão foi pressionado
  int leitura = digitalRead(botao);
  
  if(leitura == 1){
    delay(2000); //espera de 1 segundo
    mudarSemaforo();
  }
}

void mudarSemaforo() {
  //1. amarelo para carros
  digitalWrite(carroVerde,0);
  digitalWrite(carroAmarelo,1);
  delay(2000);
  
  //2. vermelho para carros; verde para pedestres
  digitalWrite(carroAmarelo,0);
  digitalWrite(carroVermelho,1);
  delay(2000);
  digitalWrite(pedVermelho,0);
  digitalWrite(pedVerde,1);
  
  //3. tempo para pedestres atravessarem
  delay(5000);
  
  //4. pisca o verde para pedestres (aviso de fechamento)
  for (int i=0;i<3;i++){
    digitalWrite(pedVerde,0);
    delay(500);
    digitalWrite(pedVerde,1);
    delay(500);
  }
  
  //5. volta ao estado inicial
  digitalWrite(pedVerde,0);
  digitalWrite(pedVermelho,1);
  delay(2000);
  digitalWrite(carroVermelho,0);
  digitalWrite(carroVerde,1);
}

