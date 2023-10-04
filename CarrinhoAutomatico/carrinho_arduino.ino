#include <Servo.h>

Servo servoSensor;

//definido a posição dos pinos no arduino
int trigPin = 3;
int echoPin = 2;
int enA = 11;
int in1 = 10;
int in2 = 9;
int in3 = 8;
int in4 = 7;
int enB = 6;

int distanciaDireita, distanciaEsquerda;
float distancia = 0.0;
int velocidadeMotorUm = 80;
int velocidadeMotorDois = 80;
//Variaveis de Distancia
float duracao = 0.0;
float CMFrente = 0.0;

//Distancia direita
float CMDireita = 0.0;
//Distancia Esquerda
float CMEsquerda = 0.0;
//Contador Ré
int contador = 0;

void setup() {
  //inicializa a serial
  Serial.begin(9600);
  //pino que defini o servo
  servoSensor.attach(5);
  //servoSensor.write(90);
  // Define os pinos como entrada e saida
  pinMode(enA, OUTPUT);
  pinMode(enB, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {

  //comando para ligar o sonar
  servoSensor.write(90);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duracao = pulseIn(echoPin, HIGH);
  CMFrente = (duracao / 58.8);
  Serial.print("Distancia em CM Frente: \n");
  Serial.println(CMFrente);
  delay(500);

  frente();

  if(CMFrente <= 20){
    parar();
    delay(2000);
    direita();
    delay(500);
    esquerda();
    delay(500);
  }
    else if(CMDireita < 20){
      viraEsquerda();
      delay(5);
    }
    else if(CMEsquerda < 20){
      viraDireita();
      delay(5);
    }
    else if(CMDireita < 20 && CMEsquerda < 20 && CMFrente < 20){
      paraTras();
      delay(5);
    }
}
//Aqui vira a direita o sonar
void direita() {
  //Vira servo para direita e mede distancia.
  servoSensor.write(0);
  delay(500);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duracao = pulseIn(echoPin, HIGH);
  CMDireita = (duracao / 58.8);
  Serial.print("Distancia em CM Direita: ");
  Serial.println(CMDireita);
  delay(500);
}
//Aqui vira a esquerda o sonar
void esquerda() {
  //Vira servo para esquerda e mede distancia.
  servoSensor.write(180);
  delay(500);
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duracao = pulseIn(echoPin, HIGH);
  CMEsquerda = (duracao / 58.8);
  Serial.print("Distancia em CM Esquerda: ");
  Serial.println(CMEsquerda);
  delay(500);
}
//Aqui faz o robo parar.
void parar() {
  Serial.print("Robo: Parar");
  digitalWrite(in1, LOW);  //Ponte h para
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  analogWrite(enA, velocidadeMotorUm);  //velocidade dos motores
  analogWrite(enB, velocidadeMotorDois);
  delay(100);
}
//Aqui faz ele ir para frente
void frente() {
  Serial.print("Robo: Anda para frete \n");
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);  //controla a ponte h para ir pra frente
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  analogWrite(enA, velocidadeMotorUm);  //velocidade dos motores
  analogWrite(enB, velocidadeMotorDois);
}
//Aqui faz ele voltar para tras
void paraTras() {
  Serial.print("Robo: Anda Para tras");
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  delay(300);
  analogWrite(enA, velocidadeMotorUm);
  analogWrite(enB, velocidadeMotorDois);
}
//Aqui vira ele para direita
void viraDireita() {
  Serial.print("Robo: vira direita");
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
  delay(300);
  analogWrite(enA, velocidadeMotorUm);
  analogWrite(enB, velocidadeMotorDois);
}
//Aqui vira ele para esquerda
void viraEsquerda() {
  Serial.print("Robo: Vira esquerda");
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  delay(300);
  analogWrite(enA, velocidadeMotorUm);
  analogWrite(enB, velocidadeMotorDois);
}
//Aqui o carinho vira em 180 e volta
void retorna() {
  Serial.print("Robo: gira 180");
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  delay(200);
  analogWrite(enA, velocidadeMotorUm);
  analogWrite(enB, velocidadeMotorDois);
}