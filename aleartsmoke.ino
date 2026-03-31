#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); 

const int gasPin = A0;
const int redLed = 8;
const int buzzer = 9;
const int greenLed = 10;
const int threshold = 500; // ค่ากลางที่คุณทดสอบแล้ว

void setup() {
  pinMode(redLed, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(greenLed, OUTPUT);
  
  lcd.init();         // เริ่มต้นหน้าจอ
  lcd.backlight();    // เปิดไฟหน้าจอ
  
  lcd.setCursor(0, 0);
  lcd.print("Gas Detector");
  lcd.setCursor(0, 1);
  lcd.print("System Warming..");
  delay(2000); // รอวอร์มเครื่องแป๊บหนึ่ง
  lcd.clear();
}

void loop() {
  int gasValue = analogRead(gasPin);
  
  lcd.setCursor(0, 0);
  
  if (gasValue < threshold) {
    lcd.print("STATUS: DANGER! ");
    digitalWrite(redLed, HIGH);
    digitalWrite(greenLed, LOW);
    tone(buzzer, 1000);
  } 
  else {
    lcd.print("STATUS: SAFE 🙂 ");
    digitalWrite(redLed, LOW);
    digitalWrite(greenLed, HIGH);
    noTone(buzzer);
  }

  delay(500);
}