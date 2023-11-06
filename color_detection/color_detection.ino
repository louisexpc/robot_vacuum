//Blue tooth communication setting
#include <SoftwareSerial.h>
SoftwareSerial BT(11,10);//TX:11,RX:10
int motorLeft = 6;
int motorLeft2 = 9;
int motorRight = 3;
int motorRight2 = 5;
char val;

//Rpi Serial communication setting
int motorPin = 7;
int LED=13;                            //or buzzer
bool motorOn = true;
unsigned long lastActionTime = 0;
const unsigned long delayTime = 5000;



void setup() {
  //Rpi Serial communication setting
  Serial.begin(9600);
  pinMode(motorPin, OUTPUT);
  pinMode(LED,OUTPUT);

  digitalWrite(motorPin, HIGH);       //HIGH: close , LOW: OPEN
  digitalWrite(LED, LOW);

  //wheel motor setting
  //Blue tooth communication setting
  BT.begin(9600);
  BT.print("BT is ready");
  pinMode(motorLeft, OUTPUT);
  pinMode(motorLeft2, OUTPUT);
  pinMode(motorRight, OUTPUT);
  pinMode(motorRight2, OUTPUT);
  analogWrite(motorLeft2,0);
  analogWrite(motorRight2,0);

}

void loop() {
  //接收rpi辨識結果來開關吸塵器
  if (Serial.available() > 0) {
    String data = Serial.readStringUntil('\n');
    data.trim(); // 去除前後空格

    if (data == "stop") {
    
      lastActionTime = millis();
      // 接收Rpi 辨識結果並啟動buzzer
      digitalWrite(LED,HIGH);
    } else if (data == "active") {
      digitalWrite(LED,LOW);
      motorOn = true;
    }
  }
  
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
  analogWrite(motorLeft, 200);
  analogWrite(motorLeft2,0);
  analogWrite(motorRight, 0);
  analogWrite(motorRight2,200);
}
void backward(){
  analogWrite(motorLeft, 0);
  analogWrite(motorLeft2,200);
  analogWrite(motorRight, 200);
  analogWrite(motorRight2,0);
}
void right(){
  analogWrite(motorLeft, 150);
  analogWrite(motorLeft2,0);
  analogWrite(motorRight, 0);
  analogWrite(motorRight2,0);
}
void left(){
  analogWrite(motorLeft, 0);
  analogWrite(motorLeft2,0);
  analogWrite(motorRight, 0);
  analogWrite(motorRight2,150);
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