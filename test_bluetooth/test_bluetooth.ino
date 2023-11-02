#include <SoftwareSerial.h>
SoftwareSerial BT(11,10);//TX:11,RX:10
int motorLeft = 6;
int motorLeft2 = 9;
int motorRight = 3;
int motorRight2 = 5;
int motorPin = 7;
char val;

void setup() {
  //wheel motor setting
  pinMode(motorLeft, OUTPUT);
  pinMode(motorLeft2, OUTPUT);
  pinMode(motorRight, OUTPUT);
  pinMode(motorRight2, OUTPUT);
  pinMode(motorPin, OUTPUT);
  analogWrite(motorLeft2,0);
  analogWrite(motorRight2,0);

  //Blue tooth communication setting
  BT.begin(9600);
  BT.print("BT is ready");
}

void loop() {
  // 車子馬達藍芽控制
  if(BT.available()){
    val = BT.read();
    switch(val){
      case 'f':
      forward();
      break;
      case 'l':
      left();
      break;
      case 'r':
      right();
      break;
      case 'b':
      backward();
      break;
      case 's':
      suck();
      break;
      case 'n':
      stop();
      break;
    }
  }
}

void forward(){
  analogWrite(motorLeft, 0);
  analogWrite(motorLeft2,100);
  analogWrite(motorRight, 100);
  analogWrite(motorRight2,0);
}
void backward(){
  analogWrite(motorLeft, 100);
  analogWrite(motorLeft2,0);
  analogWrite(motorRight, 0);
  analogWrite(motorRight2,100);
}
void left(){
  analogWrite(motorLeft, 0);
  analogWrite(motorLeft2,100);
  analogWrite(motorRight, 0);
  analogWrite(motorRight2,0);
}
void right(){
  analogWrite(motorLeft, 0);
  analogWrite(motorLeft2,0);
  analogWrite(motorRight, 100);
  analogWrite(motorRight2,0);
}
void stop(){
  analogWrite(motorLeft, 0);
  analogWrite(motorLeft2,0);
  analogWrite(motorRight, 0);
  analogWrite(motorRight2,0);
  digitalWrite(motorPin, HIGH);
}
void suck(){
  digitalWrite(motorPin, LOW);
}