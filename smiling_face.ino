#include <Servo.h>

Servo myservo;

void setup() {
  Serial.begin(9600);
  myservo.attach(9); // The servo motor pin is connected to pin 9
}

void loop() {
  if (Serial.available() > 0) {
    char data = Serial.read();
    if (data == '1') {
      myservo.write(90); // moving the servo to centre position(90 degrees).
    } else if (data == '0') {
      myservo.write(0); // "Moving the servo to the initial position (0 degrees).
    }
  }
}
