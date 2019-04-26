byte al1 [8] = {
  B00100,
  B01010,
  B01110,
  B01010,
  B00000,
  B00001,
  B00001,
  B00000
};

byte al2 [8] = {
  B00100,
  B01010,
  B01110,
  B01010,
  B00000,
  B00011,
  B00011,
  B00000
};
byte al3 [8] = {
  B00100,
  B01010,
  B01110,
  B01010,
  B00000,
  B00011,
  B00011,
  B00011
};
byte nm [8] = {
  B00000,
  B00000,
  B10001,
  B11001,
  B10101,
  B10011,
  B10001,
  B00000
};
#include <EEPROM.h>
#include <Wire.h>
#include <TimeLib.h>
#include <DS1307RTC.h>
#include <LiquidCrystal.h>
LiquidCrystal lcd {12,11,5,4,3,2};
int contrast = 9;
int brightness = 10;
int brightnessbutton = 7;
int setb = A2;
int button = 8;
int buzzerPin = 6;
int led = 13;
uint8_t mal1 = 0;
uint8_t mal2 = 1;
uint8_t mal3 = 2;
uint8_t mal1h = 3;
uint8_t mal1m = 4;
uint8_t mal1s = 5;
uint8_t mal2h = 6;
uint8_t mal2m = 7;
uint8_t mal2s = 8;
uint8_t mal3h = 9;
uint8_t mal3m = 10;
uint8_t mal3s = 11;
uint8_t mbright = 12;
int a1h = EEPROM.read(mal1h);
int a1m = EEPROM.read(mal1m);
int a1s = EEPROM.read(mal1s);
int a2h = EEPROM.read(mal2h);
int a2m = EEPROM.read(mal2m);
int a2s = EEPROM.read(mal2s);
int a3h = EEPROM.read(mal3h);
int a3m = EEPROM.read(mal3m);
int a3s = EEPROM.read(mal3s);
bool alarm1 = EEPROM.read(mal1);
bool alarm2 = EEPROM.read(mal2);
bool alarm3 = EEPROM.read(mal3);
bool b_max = EEPROM.read(mbright);

void setup() {
  
  pinMode(buzzerPin,OUTPUT);
  pinMode(button,INPUT_PULLUP);
  pinMode(led,OUTPUT);
  pinMode(brightnessbutton,INPUT_PULLUP);
  pinMode(brightness,OUTPUT);
  pinMode(setb,INPUT_PULLUP);
   lcd.begin(16,2);
   
   lcd.setCursor(2,0);
   lcd.print("ALARM CLOCK");
   lcd.setCursor(4,1);
   lcd.print("WELCOME");
   if(b_max == false) {
    analogWrite(brightness,1);
    analogWrite(contrast,120);
   }
   else {
    analogWrite(brightness,255);
    analogWrite(contrast,120);
   }
  
  
  
   
   delay(1000);
  lcd.createChar (0, al1);    
  lcd.createChar (1, al2);    
  lcd.createChar (2, al3);
  lcd.createChar (3, nm);
  
  
}

void loop() {
  
  tmElements_t tm;
  if(b_max == false) {
      digitalWrite(led,LOW);
    }
   else {
    digitalWrite(led,HIGH);
   }
    

  if (RTC.read(tm)) {
    if(digitalRead(brightnessbutton) == LOW && b_max == true && digitalRead(button) == HIGH) {
      
      lcd.clear();
      lcd.setCursor(3,0);
      lcd.print("NIGHT MODE");
      lcd.setCursor(7,1);
      lcd.print("ON");
       for(int i = 255; i > 1; i--) {
        analogWrite(brightness,i);
        delay(2);
      }
      
      
      b_max = false;
      EEPROM.write(mbright,b_max);
      
      delay(745);
      
    }
    if(digitalRead(brightnessbutton) == LOW && b_max == false && digitalRead(button) == HIGH) {
     
      lcd.clear();
      lcd.setCursor(3,0);
      lcd.print("NIGHT MODE");
      lcd.setCursor(7,1);
      lcd.print("OFF");
      for(int i = 1; i < 255; i++) {
        analogWrite(brightness,i);
        delay(2);
      }
      
      
      b_max = true;
      EEPROM.write(mbright,b_max);
      delay(745);
      
    }
    if(digitalRead(button) == LOW && alarm2 == false && digitalRead(brightnessbutton) == LOW) {
      lcd.clear();
      alarm2 = true;
      lcd.setCursor(5,0);
      lcd.print("ALARM 2");
      lcd.setCursor(7,1);
      lcd.print("ON");
      EEPROM.write(mal2,alarm2);
      delay(1000);
      if(digitalRead(setb) == LOW) {
        delay(1000);
        a2h = DisplaySetHour(a2h);
        EEPROM.write(mal2h, a2h);
        delay(500);
        a2m = DisplaySetMinute(a2m);
        EEPROM.write(mal2m, a2m);
        delay(500);
        a2s = DisplaySetSec(a2s);
        EEPROM.write(mal2s, a2s);
      }
      lcd.clear();
      lcd.setCursor(4,0);
    print2digits(a2h);
    lcd.print(':');
    print2digits(a2m);
    lcd.print(':');
    print2digits(a2s);
    delay(1000);
    }
    if(digitalRead(button) == LOW && alarm2 == true && digitalRead(brightnessbutton) == LOW) {
      lcd.clear();
      alarm2 = false;
      lcd.setCursor(5,0);
      lcd.print("ALARM 2");
      lcd.setCursor(7,1);
      lcd.print("OFF");
      EEPROM.write(mal2,alarm2);
      delay(1000);
      if(digitalRead(setb) == LOW) {
        delay(1000);
        a2h = DisplaySetHour(a2h);
        EEPROM.write(mal2h, a2h);
        delay(500);
        a2m = DisplaySetMinute(a2m);
        EEPROM.write(mal2m, a2m);
        delay(500);
        a2s = DisplaySetSec(a2s);
        EEPROM.write(mal2s, a2s);
      }
      lcd.clear();
      lcd.setCursor(4,0);
    print2digits(a2h);
    lcd.print(':');
    print2digits(a2m);
    lcd.print(':');
    print2digits(a2s);
    delay(1000);
    }
    if(digitalRead(button) == LOW && digitalRead(brightnessbutton) == HIGH) {
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("RELEASE - ALARM1");
      lcd.setCursor(1,1);
      lcd.print("HOLD - ALARM 3");
      delay(1500);
      if(digitalRead(button) == LOW) {
        if(alarm3 == false) {
        lcd.clear();
      alarm3 = true;
      lcd.setCursor(5,0);
      lcd.print("ALARM 3");
      lcd.setCursor(7,1);
      lcd.print("ON");
      EEPROM.write(mal3, alarm3);
      delay(1000);
      if(digitalRead(setb) == LOW) {
        delay(1000);
        a3h = DisplaySetHour(a3h);
        EEPROM.write(mal3h, a3h);
        delay(500);
        a3m = DisplaySetMinute(a3m);
        EEPROM.write(mal3m, a3m);
        delay(500);
        a3s = DisplaySetSec(a3s);
        EEPROM.write(mal3s, a3s);
      }
      lcd.clear();
      lcd.setCursor(4,0);
    print2digits(a3h);
    lcd.print(':');
    print2digits(a3m);
    lcd.print(':');
    print2digits(a3s);
    delay(1000);
        }
        else if(alarm3 == true) {
          lcd.clear();
      alarm3 = false;
      lcd.setCursor(5,0);
      lcd.print("ALARM 3");
      lcd.setCursor(7,1);
      lcd.print("OFF");
      EEPROM.write(mal3, alarm3);
      delay(1000);
      if(digitalRead(setb) == LOW) {
        delay(1000);
        a3h = DisplaySetHour(a3h);
        EEPROM.write(mal3h, a3h);
        delay(500);
        a3m = DisplaySetMinute(a3m);
        EEPROM.write(mal3m, a3m);
        delay(500);
        a3s = DisplaySetSec(a3s);
        EEPROM.write(mal3s, a3s);
      }
      lcd.clear();
      lcd.setCursor(4,0);
    print2digits(a3h);
    lcd.print(':');
    print2digits(a3m);
    lcd.print(':');
    print2digits(a3s);
    delay(1000);
      
        }
      }
     else if (digitalRead(button) == HIGH) {
        if(alarm1 == false) {
        lcd.clear();
      alarm1 = true;
      lcd.setCursor(5,0);
      lcd.print("ALARM 1");
      lcd.setCursor(7,1);
      lcd.print("ON");
      EEPROM.write(mal1,alarm1);
      delay(1000);
      if(digitalRead(setb) == LOW) {
        delay(1000);
        a1h = DisplaySetHour(a1h);
        EEPROM.write(mal1h,a1h);
        delay(500);
        a1m = DisplaySetMinute(a1m);
        EEPROM.write(mal1m,a1m);
        delay(500);
        a1s = DisplaySetSec(a1s);
        EEPROM.write(mal1s,a1s);
      }
      lcd.clear();
      lcd.setCursor(4,0);
    print2digits(a1h);
    lcd.print(':');
    print2digits(a1m);
    lcd.print(':');
    print2digits(a1s);
    delay(1000);
        }
        else if(alarm1 == true) {
          lcd.clear();
      alarm1 = false;
      lcd.setCursor(5,0);
      lcd.print("ALARM 1");
      lcd.setCursor(7,1);
      lcd.print("OFF");
      EEPROM.write(mal1, alarm1);
      delay(1000);
      if(digitalRead(setb) == LOW) {
        delay(1000);
        a1h = DisplaySetHour(a1h);
        EEPROM.write(mal1h,a1h);
        delay(500);
        a1m = DisplaySetMinute(a1m);
        EEPROM.write(mal1m,a1m);
        delay(500);
        a1s = DisplaySetSec(a1s);
        EEPROM.write(mal1s,a1s);
      }
      lcd.clear();
      lcd.setCursor(4,0);
    print2digits(a1h);
    lcd.print(':');
    print2digits(a1m);
    lcd.print(':');
    print2digits(a1s);
    delay(1000);
        }
      }
      
      
    }
    
    
    lcd.clear();
  
    lcd.setCursor(4,0);
    print2digits(tm.Hour);
    if((tm.Second)%2 == 1)
      lcd.print(':');
      lcd.setCursor(7,0);
    print2digits(tm.Minute);
    if((tm.Second)%2 == 1)
      lcd.print(':');
      lcd.setCursor(10,0);
    print2digits(tm.Second);
    if(alarm1 == true) {
      lcd.setCursor(13,0);
      lcd.print(char(0));
    }
    if(alarm2 == true) {
      lcd.setCursor(14,0);
      lcd.print(char(1));
    }
    if(alarm3 == true) {
      lcd.setCursor(15,0);
      lcd.print(char(2));
    }
    if(b_max == false) {
      lcd.setCursor(0,0);
      lcd.print(char(3));
    }
    lcd.setCursor(3,1);
    print2digits(tm.Day);
    lcd.print('/');
    print2digits(tm.Month);
    lcd.print('/');
    lcd.print(tmYearToCalendar(tm.Year));
   
    
    if(alarm1 == true) {
    //ALARM 1
    if(tm.Hour == a1h){                        
      if(tm.Minute == a1m){
        if(tm.Second == a1s)  {
          lcd.clear();
      lcd.setCursor(5,1);
      lcd.print("ALARM");
      while(digitalRead(button) == HIGH) {
      digitalWrite(buzzerPin,HIGH);
      digitalWrite(led,HIGH);
      }
      digitalWrite(buzzerPin,LOW);
      digitalWrite(led,LOW);
        }
      }
    }
    }
    if(alarm2 == true) {
      if(tm.Hour == a2h){                           
      if(tm.Minute == a2m){
        if(tm.Second == a2s)  {
          lcd.clear();
      lcd.setCursor(5,1);
      lcd.print("ALARM");
       while(digitalRead(button) == HIGH) {
        
      digitalWrite(buzzerPin,HIGH);
      digitalWrite(led,HIGH);
      }
      digitalWrite(buzzerPin,LOW);
      digitalWrite(led,LOW);
        }
      }
    }
    }
    if(alarm3 == true) {
     if(tm.Hour == a3h){                           
      if(tm.Minute == a3m){
        if(tm.Second == a3s)  {
          lcd.clear();
      lcd.setCursor(5,1);
      lcd.print("ALARM");
       while(digitalRead(button) == HIGH) {
        
      digitalWrite(buzzerPin,HIGH);
      digitalWrite(led,HIGH);
      }
      digitalWrite(buzzerPin,LOW);
      digitalWrite(led,LOW);
        }
      }
    }
    }
      
    
      digitalWrite(led,LOW);
      
    }
    
    

else  {
  analogWrite(brightness,255);
  if(RTC.chipPresent())  {
    
        lcd.clear();
        
          lcd.setCursor(5,0);
         
        lcd.print("ERROR");
        lcd.setCursor(0,1);
        lcd.print("REINITIALIZE RTC");
        while(!RTC.read(tm)) 
        {
          
        }
    }
    
    
     
   
    
    
  
  else  {
    lcd.clear();
    lcd.setCursor(5,0);
    lcd.print("ERROR");
    lcd.setCursor(2,1);
    lcd.print("RTC NOT FOUND");
    while(!RTC.chipPresent()) { }
      }
}
delay(1000);
}


int DisplaySetHour(int hourupg)
{
delay(1000);
  while (digitalRead(setb) == HIGH) {
  lcd.clear();
  
  if(digitalRead(brightnessbutton)==LOW)
  {
    if(hourupg==23)
    {
      hourupg=0;
    }
    else
    {
      hourupg=hourupg+1;
    }
  }
   if(digitalRead(button)==LOW)
  {
    if(hourupg==0)
    {
      hourupg=23;
    }
    else
    {
      hourupg=hourupg-1;
    }
  }
  lcd.setCursor(0,0);
  lcd.print("Set Hour:");
  lcd.setCursor(0,1);
  print2digits(hourupg);
  delay(200);
  }
  return hourupg;
  
  
}

int DisplaySetMinute(int minupg)
{
  delay(1000);
  while (digitalRead(setb) == HIGH) {
  lcd.clear();
  if(digitalRead(brightnessbutton)==LOW)
  {
    if (minupg==59)
    {
      minupg=0;
    }
    else
    {
      minupg=minupg+1;
    }
  }
   if(digitalRead(button)==LOW)
  {
    if (minupg==0)
    {
      minupg=59;
    }
    else
    {
      minupg=minupg-1;
    }
  }
  lcd.setCursor(0,0);
  lcd.print("Set Minutes:");
  lcd.setCursor(0,1);
  print2digits(minupg);
  delay(200);
  }
  return minupg;
}
int DisplaySetSec(int secupg)
{
  delay(1000);
  while (digitalRead(setb) == HIGH) {
  lcd.clear();
  if(digitalRead(brightnessbutton)==LOW)
  {
    if (secupg==59)
    {
      secupg=0;
    }
    else
    {
      secupg++;
    }
  }
   if(digitalRead(button)==LOW)
  {
    if (secupg==0)
    {
      secupg=59;
    }
    else
    {
      secupg--;
    }
  }
  lcd.setCursor(0,0);
  lcd.print("Set Seconds:");
  lcd.setCursor(0,1);
  print2digits(secupg);
  delay(200);
  }
  return secupg;
}
void print2digits(int number) {
  if (number >= 0 && number < 10) {
    lcd.write('0');
  }
  lcd.print(number);
}
