#include <Servo.h>

Servo myservo;            // create servo object to control a servo

int potpin = 0;           // analog pin used to connect the potentiometer
int val = 90;             // variable to read the value from the analog pin

void setup() {
  Serial.begin(9600);
  myservo.attach(8);      // attaches the servo on pin 8 to the servo object

  myservo.write(0);
  delay(2000);
  myservo.write(180);
  delay(2000);
  myservo.write(val);
  delay(2000);
}

void loop() {
  
  // waits for the servo to get there
}
