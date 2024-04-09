#include <LiquidCrystal.h>
LiquidCrystal lcd(13,12,25,26,27,14);
int pin = 35;
int pin2 = 34;

void setup()
{
    lcd.begin(16, 2);
    lcd.clear();
}

void loop()
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Erotus");
  lcd.setCursor(0, 1);
  double voltage1 = analogRead(pin)*(3.3/4095);
  lcd.print(voltage1);
  double voltage2 = analogRead(pin2)*(3.3/4095);
  lcd.setCursor(6, 1);
  lcd.print(voltage2);
  voltage1 = voltage1*4.95;
  voltage2 = voltage2*1.54;
  lcd.setCursor(8, 0);
  lcd.print(voltage1 - voltage2);
  delay(500);

}
