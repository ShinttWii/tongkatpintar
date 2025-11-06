#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define TRIG_PIN 26
#define ECHO_PIN 27
#define BUZZER_PIN 19

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  Serial.begin(115200);
  lcd.init();
  lcd.backlight();
  
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  lcd.setCursor(0, 0);
  lcd.print("Tongkat Pintar");
  lcd.setCursor(0, 1);
  lcd.print("Tunanetra Ready");
  delay(2000);
  lcd.clear();
}

void loop() {
  long duration;
  float distance;
 


  // kirim pulsa trigger ultrasonic
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  // baca waktu pantulan echo
  duration = pulseIn(ECHO_PIN, HIGH);
  distance = (duration * 0.0343) / 2;  // konversi ke cm

  Serial.print("Jarak: ");
  Serial.print(distance);
  Serial.println(" cm");

  lcd.setCursor(0, 0);
  lcd.print("Jarak: ");
  lcd.print(distance);
  lcd.print(" cm   ");

  // logika peringatan buzzer
  if (distance <= 50 && distance > 30) {
    tone(BUZZER_PIN, 400, 100);  // suara pelan
    lcd.setCursor(0, 1);
    lcd.print("Peringatan: Dekat ");
  } 
  else if (distance <= 30 && distance > 10) {
    tone(BUZZER_PIN, 600, 150);  // sedikit lebih nyaring
    lcd.setCursor(0, 1);
    lcd.print("AWAS! Halangan    ");
  } 
  else if (distance <= 10 && distance > 0) {
    tone(BUZZER_PIN, 800, 200);  // lebih sering bunyi
    lcd.setCursor(0, 1);
    lcd.print("SANGAT DEKAT!     ");
  } 
  else {
    noTone(BUZZER_PIN);
    lcd.setCursor(0, 1);
    lcd.print("Aman               ");
  }

  delay(300);
}
