#include <VarSpeedServo.h>

//Cria objeto para controlar o servo base
VarSpeedServo servo_base;
VarSpeedServo servo_inclinacao;
VarSpeedServo servo_base2;
VarSpeedServo servo_inclinacao2;

int pino_x2 = A3; //Pino ligado ao X do joystick
int pino_y2 = A2; //Pino ligado ao Y do joystick
int valor;   //Armazena o valor do eixo X
int pino_x = A4; //Pino ligado ao X do joystick
int pino_y = A5; //Pino ligado ao Y do joystick
int valor1 = 43;
int valor2 = 90;
int valor3 = 100;
int valor4 = 90;
int button = 10;
int estadoBotao = 0;
int x = 0;
int led = 13;
int led2 = 12;

void setup() {
  Serial.begin(9600);

  pinMode(button, INPUT);
  pinMode(led, OUTPUT);
  pinMode(led2, OUTPUT);
  //Define a porta a ser ligada ao servo base ******* GARRA ********
  servo_base.attach(7, 1, 180);
  //Define a porta a ser ligada ao servo inclinacao ******* LADO DIREITO DO BRAÇO ROBÓTICO *********
  servo_inclinacao.attach(6, 1, 180);
  //Define a porta a ser ligada ao servo base ******* LADO ESQUERDO DO BRAÇO ROBÓTICO *********
  servo_base2.attach(4, 1, 180);
  //Define a porta a ser ligada ao servo inclinacao ******* BASE DO BRAÇO ROBÓTICO ********
  servo_inclinacao2.attach(3, 1, 180);
}

void loop() {
  estadoBotao = digitalRead(button);
  Serial.println("Valor BUTTON: ");
  Serial.println(estadoBotao);
  if (estadoBotao == 1) {
    x = !x;
  }
  if (x == 0) {
    joystick();
    digitalWrite(led, HIGH);
    digitalWrite(led2, LOW);
  } else if (x == 1) {
    Serial.println("---------------------------------------------------------------------------");
    bluetooth();
    digitalWrite(led, LOW);
    digitalWrite(led2, HIGH);
  }
}

void joystick() {

  ///////////////////////////    GARRA DO BRAÇO ROBÓTICO  ////////////////////////////////////////
  //Recebe o valor do joystick, eixo X
  valor = analogRead(pino_x);
  //Converte o valor lido para um valor entre 1 e 180 graus
  valor = map(valor, 0, 1023, 8, 78);
  if (valor > 53 && valor1 < 78) {
    valor1 = valor1 + 3;
    Serial.println("*************************************************");
    servo_base.slowmove(valor1, 15);
  }
  else if (valor < 33 && valor1 > 20) {
    valor1 = valor1 - 3;
    Serial.println("*************************************************");
    servo_base.slowmove(valor1, 15);
  }

  ///////////////////////////  LADO DIREITO DO BRAÇO ROBÓTICO  ////////////////////////////////////////
  //Recebe o valor do joystick, eixo Y
  valor = analogRead(pino_y);
  //Converte o valor lido para um valor entre 1 e 180 graus
  valor = map(valor, 0, 1023, 1, 180);
  if (valor > 100 && valor2 < 180) {
    valor2 = valor2 + 3;
    Serial.println("*************************************************");
    servo_inclinacao.slowmove(valor2, 15);
  }
  else if (valor < 80 && valor2 > 30) {
    valor2 = valor2 - 3;
    servo_inclinacao.slowmove(valor2, 15);  Serial.println("*************************************************");
  }


  ///////////////////////////    LADO ESQUERDO DO BRAÇO ROBÓTICO  ////////////////////////////////////////
  //Recebe o valor do joystick, eixo X
  valor = analogRead(pino_x2);
  //Converte o valor lido para um valor entre 1 e 180 graus
  valor = map(valor, 0, 1023, 20, 180);
  //Move o servo base para a posicao definida pelo joystick
  if (valor > 110 && valor3 < 180) {
    valor3 = valor3 + 3;  Serial.println("*************************************************");
    servo_base2.slowmove(valor3, 15);
  }
  else if (valor < 90 && valor3 > 20) {
    valor3 = valor3 - 3;  Serial.println("*************************************************");
    servo_base2.slowmove(valor3, 15);
  }


  ///////////////////////////    BASE DO BRAÇO ROBÓTICO  ////////////////////////////////////////
  //Recebe o valor do joystick, eixo Y
  valor = analogRead(pino_y2);
  //Converte o valor lido para um valor entre 1 e 180 graus
  valor = map(valor, 0, 1023, 1, 180);
  Serial.println(valor4);
  //Move o servo inclinacao para a posicao definida pelo joystick
  if (valor > 100 && valor4 < 180) {
    valor4 = valor4 + 3;  Serial.println("*************************************************");
    servo_inclinacao2.slowmove(valor4, 15);
  } 
  else if (valor < 80 && valor4 > 0) {
    valor4 = valor4 - 3;  Serial.println("*************************************************");
    servo_inclinacao2.slowmove(valor4, 15);
  }
  delay(100);
}

void bluetooth() {
  valor = Serial.read();
  Serial.print("Valor:  ");
  Serial.println(valor);
  if (valor == 2) {
    valor1 = valor1 + 3;
    servo_base.slowmove(valor1, 15);
  }
  else if (valor == 1) {
    valor1 = valor1 - 3;
    servo_base.slowmove(valor1, 15);
  }
  else if (valor == 3) {
    valor2 = valor2 + 3;
    servo_inclinacao.slowmove(valor2, 15);
  }
  else if (valor == 4) {
    valor2 = valor2 - 3;
    servo_inclinacao.slowmove(valor2, 15);
  }
  ////////////////////////////////////////////////////////////////////////////
  else if (valor == 5) {
    valor3 = valor3 + 3;
    servo_base2.slowmove(valor3, 15);
  }
  else if (valor == 6) {
    valor3 = valor3 - 3;
    servo_base2.slowmove(valor3, 15);
  }
  else if (valor == 7) {
    valor4 = valor4 + 3;
    servo_inclinacao2.slowmove(valor4, 15);
  }
  else if (valor == 8) {
    valor4 = valor4 - 3;
    servo_inclinacao2.slowmove(valor4, 15);
  }
  delay(100);
}
