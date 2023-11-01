int motorLeft = 6;
int motorLeft2 = 9;
int motorRight = 3;
int motorRight2 = 5;
int motorPin = 7;
int LED =13;
void setup() {

  // wheel motor setting
  pinMode(motorLeft, OUTPUT);
  pinMode(motorLeft2, OUTPUT);
  pinMode(motorRight, OUTPUT);
  pinMode(motorRight2, OUTPUT);

  analogWrite(motorLeft, 100);
  analogWrite(motorLeft2, 0);
  analogWrite(motorRight, 100);
  analogWrite(motorRight2, 0);

  // vacuum motor setting
  pinMode(motorPin,OUTPUT);
  digitalWrite(motorPin, LOW);

  //LED setting
  pinMode(LED,OUTPUT);
  digitalWrite(LED,HIGH);
  
}

void loop() {

}

