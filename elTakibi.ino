#include <Servo.h>

Servo servoMotor;

const int trigPin = 3;
const int echoPin = 2;

long mesafe;
int aci;

void setup() {
  servoMotor.attach(12);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void loop() {
  // Mesafe sensörü ile nesnenin mesafesini ölçme
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  mesafe = pulseIn(echoPin, HIGH) * 0.034 / 2;

  // Elin konumuna göre servo motoru hareket ettirme
  aci = map(mesafe, 5, 30, 0, 180); // Mesafeyi 5-30 cm aralığından 0-180 derece aralığına dönüştür
  aci = constrain(aci, 0, 180); // Açıyı 0-180 derece aralığında tut
  
  // 90 derece ile başlayıp 0-90 ve 90-180 aralığında eşit paylaşılmış hareket
  if (aci <= 90) {
    servoMotor.write(map(aci, 0, 90, 90, 0));
  } else {
    servoMotor.write(map(aci, 90, 180, 90, 180));
  }

  delay(100);
}
