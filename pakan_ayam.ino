#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include "DHT.h"
#include <DS3231.h>
#include <Servo.h>

#define waktu t.hour
#define pb digitalRead(A0)
#define water analogRead(A1)
#define suhu dht.readTemperature()
#define jam t.hour
#define menit t.min
#define detik t.sec
#define lon digitalWrite(4, LOW)
#define lof digitalWrite(4, HIGH)
#define ion digitalWrite(5, LOW)
#define iof digitalWrite(5, HIGH)
#define oon digitalWrite(6, LOW)
#define oof digitalWrite(6, HIGH)
#define son digitalWrite(7, LOW)
#define sof digitalWrite(7, HIGH)
#define sopen servo.write(40);
#define sclose servo.write(0)

LiquidCrystal_I2C lcd(0x27, 16, 2);
DHT dht(2, DHT11);
DS3231  rtc(SDA, SCL);
Servo servo;

float suhu_bawah = 24.00;
float suhu_atas = 32.00;

Time t;

boolean kon;

void setup() {
  Serial.begin(9600);
  lcd.begin();
  dht.begin();
  rtc.begin();

  servo.attach(9);

  pinMode(A0, INPUT_PULLUP);
  pinMode(A1, INPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);

  sclose;
  lof; iof; oof; sof;

  lcd.clear();
  lcd.print("Pa Deni kemana?");
  delay(3000);
  lcd.clear();
}

void loop(){
  t = rtc.getTime();

  if(!pb){
    sopen; son;
    while(!pb){}
    sclose; sof;
  }

  if(suhu < suhu_bawah){lon;}
  else if(suhu > suhu_atas){ion; oon;}
  else{lof; iof; oof;}

  if((millis()%4000) < 2000){
    lcd.setCursor(0,0);
    lcd.print("    ");
    lcd.print(rtc.getDOWStr());
    lcd.print("   ");
    lcd.setCursor(0,1);
    lcd.print("    ");
    lcd.print(rtc.getTimeStr());
    lcd.print("    ");
  }
  else{
    lcd.setCursor(0,0);
    lcd.print("  Suhu : ");
    lcd.print(suhu);
    lcd.print("  ");
    if(suhu < suhu_bawah){
      lcd.setCursor(0,1);
      lcd.print("Pemanas Aktif   ");
    }
    else if(suhu > suhu_atas){
      lcd.setCursor(0,1);
      lcd.print("Pendingin Aktif ");
    }
    else{
      lcd.setCursor(0,1);
      lcd.print("     Normal     ");
    }
  }

  if(waktu == 7 or waktu == 9 or waktu == 11 or waktu == 13 or waktu == 15){
    if(!kon){
      sopen;
      delay(3000);
      sclose;
    }
    kon = true;
  }
  else{kon = false;}

  if(water < 500){son;}
  else if(water > 600){sof;}
}
