//Rpi Serial communication setting
int motorPin = 7;
int LED=13;
bool motorOn = true;
unsigned long lastActionTime = 0;
const unsigned long delayTime = 5000;


void setup() {
  //Rpi Serial communication setting
  Serial.begin(9600);
  pinMode(motorPin, OUTPUT);
  pinMode(LED,OUTPUT);

  digitalWrite(motorPin, HIGH);
  digitalWrite(LED, HIGH);
}

void loop() {
  //接收rpi辨識結果來開關吸塵器
  if (Serial.available() > 0) {
    String data = Serial.readStringUntil('\n');
    data.trim(); // 去除前後空格

    if (data == "stop") {
      digitalWrite(motorPin, LOW);
      motorOn = false;
      lastActionTime = millis();
      // 接收Rpi 辨識結果並閃爍LED 停止 vacuum motor
      digitalWrite(LED,LOW);
      delay(100);
      digitalWrite(LED,HIGH);
      delay(100);

    } else if (data == "active") {
      digitalWrite(motorPin, HIGH);
      digitalWrite(LED,HIGH);
      motorOn = true;
    }
  }

  // 檢查是否需要恢復動作
  if (!motorOn && ((millis() - lastActionTime )>= delayTime)) {

    digitalWrite(motorPin, HIGH);
    digitalWrite(LED,HIGH);
    motorOn = true;
  }
}