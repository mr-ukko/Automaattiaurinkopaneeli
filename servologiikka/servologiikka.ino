#include <ESP32Servo.h>

Servo myservo;  // create servo object to control a servo  // analog pin used to connect the potentiometer
int val;    // variable to read the value from the analog pin

void setup() {
  myservo.attach(15);
  val = 0;  // attaches the servo on pin 9 to the servo object
}

void loop() {
  if (analogRead(2) > analogRead(4)){
    val = val + 10;
  }else{
    val = val - 10;
  }
  if (val < 10 ){val = 10;}
  if (val > 160 ){val = 160;}
  myservo.write(val);
  delay(1500);                        // waits for the servo to get there
}