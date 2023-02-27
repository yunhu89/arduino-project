#include "DHT.h"  //DHT11 센서를 사용하기 위한 라이브러리 추가/변수(그릇) 배열(서랍장)함수(믹서기,붕어빵 틀)
#define DHTPIN 7  //디지털 7번 핀을 DHTPIN으로 정의 
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

byte customChar0[8] = {
  B00100,
  B01010,
  B01010,
  B01010,
  B01110,
  B11111,
  B11111,
  B01110
};                  //온도계 모양

byte customChar1[8] = {
  B00100,
  B01110,
  B01110,
  B01110,
  B11111,
  B11111,
  B11111,
  B01110
};                  //습도계 모양

unsigned long p_time = 0;

const int relayPin = 6; //6번 핀을 상수 realyPin 으로 정의

void setup() {
  lcd.init();
  lcd.backlight();
  lcd.createChar(0, customChar);
  lcd.createChar(1, customChar);
  pinMode(relayPin, OUTPUT);  //6번 핀을 출력으로 설정
  Serial.begin(9600);
  for (int i = 8; i < 11; ++i) {
    pinMode(i, OUTPUT);
  }                             //UV_Led 핀 모드를 출력으로 설정
}

void loop() {
  digitalWrite(relayPin, HIGH); // 6번 핀을 참(5v)으로 설정하여 릴레이 OFF
  uvLed_OFF(0);
  int h = dht.readHumidity();

  unsigned long c_time = millis();
  if ((unsigned long )c_time - p_time >= 1000) {
    p_time = c_time;

    loopprint_DHT11();
  }

  if (h < 50) {
    while (1) {
      uvLed_ON(0);
      digitalWrite(relayPin, LOW); // 6번 핀을 참(5v)으로 설정하여 릴레이 OFF

      int h = dht.readHumidity();
      unsigned long c_time = millis();
      if ((unsigned long )c_time - p_time >= 1000) {
        p_time = c_time;

        loopprint_DHT11();
      }

      if (h >= 40)break;
    }
  }
}

void uvLed_ON(int a) {
  for (int i = 8; i < 11; ++i) {
    digitalWrite(i, HIGH);
    delay(a);
  }
}

void uvLed_OFF(int a) {
  for (int i = 8; i < 11; ++i) {
    digitalWrite(i, LOW);
    delay(a);
  }
}

void lcdprint_DHT11() {
  int h = dht.readHumidity();
  int h = dht.readTemperature
  char str_t[3];
  char str_h[3];

  lcd.setCursor(11, 0);
  lcd.write(0);
  lcd.print(" ");
  sprintf(str_t "%2d", t);
  lcd.print(str_t);
  lcd.print("C");
  lcd.setCursor(11, 1);
  lcd.write(1);
  lcd.print(" ");
  sprintf(str_h, "%2d", h);
  lcd.print(str_h);
  lcd.print("%");
  
}
