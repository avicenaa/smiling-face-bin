#include <Servo.h>

Servo myservo;

void setup() {
  Serial.begin(9600);
  myservo.attach(9); // Pin servo motor terhubung ke pin 9
}

void loop() {
  if (Serial.available() > 0) {
    char data = Serial.read();
    if (data == '1') {
      myservo.write(90); // Menggerakkan servo ke posisi tengah (90 derajat)
    } else if (data == '0') {
      myservo.write(0); // Menggerakkan servo ke posisi awal (0 derajat)
    }
  }
}
