#include <LiquidCrystal.h>
#include <ESP32Servo.h>

LiquidCrystal lcd(12,17,5,18,19,21);
#define lightSensor1 34
#define lightSensor2 35
#define lightSensor3 32
#define lightSensor4 33
#define voltage 26
#define ampers 27
#define joyButton 25
#define joyY 13
#define joyX 14
bool manual;
Servo servoBottom;  // create servo object to control a servo
Servo servoTop;
int angleServoTop;    // variable that tells servo angle
int angleServoBottom;

void setup() {
  servoBottom.attach(4);
  servoTop.attach(16);
  angleServoTop = 0;
  angleServoBottom = 0;
  manual = false;
  lcd.begin(16, 2);
  lcd.clear();
}

void loop() {
  if (analogRead(lightSensor1) > analogRead(lightSensor2)){ // pitch axis 
    angleServoTop = angleServoTop + 10; 
  }else{
    angleServoTop = angleServoTop - 10;
  }
  if (angleServoTop < 10 ){angleServoTop = 10;} //Checks for over extension of servo
  if (angleServoTop > 170 ){angleServoTop = 170;}
  servoTop.write(angleServoTop);

  if (analogRead(lightSensor3) > analogRead(lightSensor4)){ // yaw axis 
    angleServoBottom = angleServoBottom + 10; 
  }else{
    angleServoBottom = angleServoBottom - 10;
  }
  if (angleServoBottom < 10 ){angleServoBottom = 10;} //Checks for over extension of servo
  if (angleServoBottom > 170 ){angleServoBottom = 170;}
  servoTop.write(angleServoBottom);

  double amps = analogRead(ampers)*(3.3/4095);
  double volts = analogRead(voltage)*(3.3/4095);
  volts = volts*4.95;
  amps = amps*1.54;

  lcd.clear(); //Clears lcd of previous values
  lcd.setCursor(0, 0); //top row text 
  lcd.print("Power in: ");
  lcd.setCursor(10, 0);
  lcd.print(volts * vamps);
  lcd.setCursor(15, 0);
  lcd.print("W");

  lcd.setCursor(0, 1); //bottom row
  lcd.print(volts);
  lcd.setCursor(4, 1);
  lcd.print("V");
  lcd.setCursor(9, 1); 
  lcd.print(amps);
  lcd.setCursor(14, 1);
  lcd.print("A");
  
  if(analogRead(joyButton)>3000){ //Manula mode activation 
    manual = true;
    while (manual = true){
      double amps = analogRead(ampers)*(3.3/4095);
      double volts = analogRead(voltage)*(3.3/4095);
      volts = volts*4.95;
      amps = amps*1.54;

      lcd.clear(); //Clears lcd of previous values
      lcd.setCursor(0, 0); //top row text 
      lcd.print("ManualMod");
      lcd.setCursor(10, 0);
      lcd.print(volts * vamps);
      lcd.setCursor(15, 0);
      lcd.print("W");

      lcd.setCursor(0, 1); //bottom row
      lcd.print(volts);
      lcd.setCursor(4, 1);
      lcd.print("V");
      lcd.setCursor(9, 1); 
      lcd.print(amps);
      lcd.setCursor(14, 1);
      lcd.print("A");

      if(analogRead(joyY)<600){ // joystic y axis to yaw 
        angleServoBottom = angleServoBottom + 20;
      }else if (analogRead(joyY)<1200){
        angleServoBottom = angleServoBottom + 15;
      }else if (analogRead(joyY)<1800){
        angleServoBottom = angleServoBottom + 10;
      }else if (analogRead(joyY)>2200 && analogRead(joyY)<2800){
        angleServoBottom = angleServoBottom - 10;
      }else if (analogRead(joyY)>2200 && analogRead(joyY)<3400){
        angleServoBottom = angleServoBottom - 15;
      }else if (analogRead(joyY)>2200 && analogRead(joyY)<4096){
        angleServoBottom = angleServoBottom - 20;
      }

      if(analogRead(joyX)<600){ // joystic X axis to pitch 
        angleServoTop = angleServoTop + 20;
      }else if (analogRead(joyX)<1200){
        angleServoTop = angleServoTop + 15;
      }else if (analogRead(joyX)<1800){
        angleServoTop = angleServoTop + 10;
      }else if (analogRead(joyX)>2200 && analogRead(joyX)<2800){
        angleServoTop = angleServoTop - 10;
      }else if (analogRead(joyX)>2200 && analogRead(joyX)<3400){
        angleServoTop = angleServoTop - 15;
      }else if (analogRead(joyX)>2200 && analogRead(joyX)<4096){
        angleServoTop = angleServoTop - 20;
      }

      if (angleServoBottom < 10 ){angleServoBottom = 10;} //Checks for over extension of servo
      if (angleServoBottom > 170 ){angleServoBottom = 170;}
      if (angleServoTop < 10 ){angleServoTop = 10;} //Checks for over extension of servo
      if (angleServoTop > 170 ){angleServoTop = 170;}
      servoTop.write(angleServoBottom);
      servoTop.write(angleServoTop);
      delay(100);

      if(analogRead(joyButton)>3000){ //Manula mode deactivation 
        delay(1500);
        if(analogRead(joyButton)>3000){manual = false;}
      }
    }
  }
  delay(1500);
}