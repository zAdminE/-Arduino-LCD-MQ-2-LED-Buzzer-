# 🔥 ระบบตรวจจับแก๊สด้วย Arduino + LCD (MQ-2 + LED + Buzzer)

## 📌 ภาพรวมโปรเจกต์

โปรเจกต์นี้เป็นระบบตรวจจับแก๊สโดยใช้ Arduino Uno ร่วมกับเซนเซอร์ MQ-2
มีการแสดงผลผ่านจอ LCD (I2C) พร้อมไฟ LED และเสียง Buzzer แจ้งเตือน

---

## 🛠️ อุปกรณ์ที่ใช้

* Arduino Uno
* เซนเซอร์ตรวจจับแก๊ส MQ-2
* จอ LCD I2C (16x2)
* LED สีแดง (สถานะอันตราย)
* LED สีเขียว (สถานะปลอดภัย)
* ตัวต้านทาน 220Ω
* Buzzer
* สาย Jumper

---

## ⚡ การต่อวงจร

### MQ-2 Sensor

* VCC → 5V
* GND → GND
* AO → A0

---

### LCD I2C

* VCC → 5V
* GND → GND
* SDA → A4
* SCL → A5

---

### LED

* LED สีแดง → ขา D8 (ผ่านตัวต้านทาน)
* LED สีเขียว → ขา D10 (ผ่านตัวต้านทาน)
* ขาอีกด้านของ LED → GND

---

### Buzzer

* (+) → D9
* (-) → GND

---

## 🧠 หลักการทำงาน

* MQ-2 อ่านค่าความเข้มข้นของแก๊สผ่านขา Analog (A0)
* ถ้าค่าที่อ่านได้ **ต่ำกว่า threshold (500)**:

  * แสดง "DANGER!" บนจอ LCD
  * LED สีแดงติด
  * Buzzer ดัง
* ถ้าค่าสูงกว่า threshold:

  * แสดง "SAFE" บนจอ LCD
  * LED สีเขียวติด
  * Buzzer หยุด

---

## 💻 โค้ด Arduino

```cpp id="gaslcd01"
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2); 

const int gasPin = A0;
const int redLed = 8;
const int buzzer = 9;
const int greenLed = 10;
const int threshold = 500;

void setup() {
  pinMode(redLed, OUTPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(greenLed, OUTPUT);
  
  lcd.init();
  lcd.backlight();
  
  lcd.setCursor(0, 0);
  lcd.print("Gas Detector");
  lcd.setCursor(0, 1);
  lcd.print("System Warming..");
  delay(2000);
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
```

---

## ⚠️ หมายเหตุ

* ค่า threshold (500) ต้องปรับตามการใช้งานจริง
* MQ-2 ต้องวอร์มประมาณ 1–2 นาที
* ตรวจสอบ Address ของ LCD (เช่น 0x27 หรือ 0x3F)

---

## 🚀 แนวทางพัฒนาเพิ่มเติม

* แสดงค่าแก๊สแบบตัวเลขบน LCD
* เพิ่มระบบแจ้งเตือนผ่านมือถือ (ESP8266 / ESP32)
* บันทึกข้อมูลลง SD Card

---

## 📷 ตัวอย่างผลงาน

*(ใส่รูปวงจรหรือรูปตอนใช้งานจริงได้ที่นี่)*

---

## 📄 License

Open-source ใช้งานและพัฒนาต่อได้ฟรี
