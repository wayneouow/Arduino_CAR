#include "pitches.h"
#include<Servo.h>
#define MotorA_I1     8  //定義 I1 接腳
#define MotorA_I2     9  //定義 I2 接腳
#define MotorB_I3    10  //定義 I3 接腳
#define MotorB_I4    11  //定義 I4 接腳
#define MotorA_PWMA    7  //定義 PWMA (PWM調速) 接腳
#define MotorB_PWMB    6  //宣告 PWMB (PWM調速) 接腳
#define Rled    12
#define Lled    13

#define LaserPIN 3

#define SensorLeft    A1  //定義 左感測器 輸入腳
#define SensorRight   A0  //定義 右感測器 輸入腳
#define detectled     5

#define US_Trig  A5  //定義超音波模組 Trig 腳位
#define US_Echo  A4  //定義超音波模組 Echo 腳位

#define Servo_Pin      A2  
#define servo_delay  100 
Servo myservo;            
#define Fgo  8  
#define Rgo  6  
#define Lgo  4  
#define Bgo  2  

int tempo = 140;
int buzzer = 4;
int melody[] = {

  NOTE_C4,4, NOTE_C4,8, 
  NOTE_D4,-4, NOTE_C4,-4, NOTE_F4,-4,
  NOTE_E4,-2, NOTE_C4,4, NOTE_C4,8, 
  NOTE_D4,-4, NOTE_C4,-4, NOTE_G4,-4,
  NOTE_F4,-2, NOTE_C4,4, NOTE_C4,8,

  NOTE_C5,-4, NOTE_A4,-4, NOTE_F4,-4, 
  NOTE_E4,-4, NOTE_D4,-4, NOTE_AS4,4, NOTE_AS4,8,
  NOTE_A4,-4, NOTE_F4,-4, NOTE_G4,-4,
  NOTE_F4,-2,
 
};
int notes = sizeof(melody) / sizeof(melody[0]) / 2;
int wholenote = (60000 * 4) / tempo;
int divider = 0, noteDuration = 0;
int defaultdegree =45;

void setup()
{
  Serial.begin(9600); 
  
  pinMode(MotorA_I1,OUTPUT);
  pinMode(MotorA_I2,OUTPUT);
  pinMode(MotorB_I3,OUTPUT);
  pinMode(MotorB_I4,OUTPUT);
  pinMode(MotorA_PWMA,OUTPUT);
  pinMode(MotorB_PWMB,OUTPUT);
  pinMode(Rled,OUTPUT);
  pinMode(Lled,OUTPUT);
  analogWrite(MotorA_PWMA,150);    //設定馬達 (右) 轉速
  analogWrite(MotorB_PWMB,150);    //設定馬達 (左) 轉速

  pinMode(LaserPIN,OUTPUT);

  pinMode(SensorLeft,   INPUT); 
  pinMode(SensorRight,  INPUT);
  pinMode(detectled,OUTPUT);

  myservo.attach(Servo_Pin);
  myservo.write(45);
}

void advance(int a)    // 前進
{
    digitalWrite(MotorA_I1,HIGH);   //馬達（右）順時針轉動
    digitalWrite(MotorA_I2,LOW);
    digitalWrite(MotorB_I3,HIGH);   //馬達（左）逆時針轉動
    digitalWrite(MotorB_I4,LOW);
    delay(a * 100);
}

void turnR(int d)    //右轉
{
    digitalWrite(MotorA_I1,LOW);    //馬達（右）逆時針轉動
    digitalWrite(MotorA_I2,HIGH);
    digitalWrite(MotorB_I3,HIGH);   //馬達（左）逆時針轉動
    digitalWrite(MotorB_I4,LOW);
    delay(d * 100);
}

void turnL(int e)    //左轉
{
    digitalWrite(MotorA_I1,HIGH);   //馬達（右）順時針轉動
    digitalWrite(MotorA_I2,LOW);
    digitalWrite(MotorB_I3,LOW);    //馬達（左）順時針轉動
    digitalWrite(MotorB_I4,HIGH);
    delay(e * 100);
}    

void stopRL(int f)  //停止
{
    digitalWrite(MotorA_I1,HIGH);   //馬達（右）停止轉動
    digitalWrite(MotorA_I2,HIGH);
    digitalWrite(MotorB_I3,HIGH);   //馬達（左）停止轉動
    digitalWrite(MotorB_I4,HIGH);
    delay(f * 100);
}

void back(int g)    //後退
{
    digitalWrite(MotorA_I1,LOW);    //馬達（右）逆時針轉動
    digitalWrite(MotorA_I2,HIGH);
    digitalWrite(MotorB_I3,LOW);    //馬達（左）順時針轉動
    digitalWrite(MotorB_I4,HIGH);
    delay(g * 100);     
}

void Rledlight()    // 右轉方向燈
{
    digitalWrite(Rled,HIGH);
    digitalWrite(Lled,LOW);       
}

void Lledlight()    // 左轉方向燈
{
    digitalWrite(Lled,HIGH);
    digitalWrite(Rled,LOW);       
}

void Fledlight()    // 前進方向燈
{
    digitalWrite(Lled,LOW);
    digitalWrite(Rled,LOW);       
}

void Bledlight()    // 倒退方向燈
{
    digitalWrite(Lled,HIGH);
    digitalWrite(Rled,HIGH);       
}

void Sledlight()    // 倒退方向燈
{
    digitalWrite(Lled,LOW);
    digitalWrite(Rled,LOW);       
}

void fire()    // 前進
{
    digitalWrite(LaserPIN, HIGH);      
    delay(500);                      
    digitalWrite(LaserPIN, LOW);                    
}

void music()
{
  for (int thisNote = 0; thisNote < notes * 2; thisNote = thisNote + 2) {

    divider = melody[thisNote + 1];
    if (divider > 0) {
      noteDuration = (wholenote) / divider;
    } else if (divider < 0) {
      noteDuration = (wholenote) / abs(divider);
      noteDuration *= 1.5; 
    }
    tone(buzzer, melody[thisNote], noteDuration * 0.9);
    delay(noteDuration);
    noTone(buzzer);
  }
}

void alarm()
{
  int toneVal;
  for(int x=0; x<100; x++){
    toneVal = 500+(x*10);
    tone(buzzer, toneVal);
    delay(2);
  }
  noTone(buzzer);
}

int Ask_Distance(int d)  // 測量距離 
{
    myservo.write(d);  
    delay(servo_delay);  
    float duty,distance;
    digitalWrite(US_Trig, HIGH);   
    delayMicroseconds(30);
    digitalWrite(US_Trig, LOW);  
  
    duty = pulseIn(US_Echo, HIGH);  
    distance = duty / 5.8 / 10;  
    delay(100);
    Serial.print("Distance:"); //輸出距離（單位：公分）
    Serial.println(distance); //顯示距離
    Serial.print('\n');
    return distance;
   
}
    
void detection()    
{
    for(defaultdegree;defaultdegree<=90;defaultdegree+=10){
      int F_Distance;
      F_Distance = Ask_Distance(defaultdegree);  
      if(F_Distance < 10) 
      {
          digitalWrite(Lled,HIGH);
          digitalWrite(Rled,HIGH);
          alarm();
      }
      else{
          digitalWrite(Lled,LOW);
          digitalWrite(Rled,LOW);
      }
    }
    digitalWrite(Lled,LOW);
    digitalWrite(Rled,LOW);
    myservo.write(45);
    for(defaultdegree;defaultdegree>=0;defaultdegree-=10){
      int F_Distance;
      F_Distance = Ask_Distance(defaultdegree);  
      if(F_Distance < 10) 
      {
          digitalWrite(Lled,HIGH);
          digitalWrite(Rled,HIGH);
          alarm();
      }
      else{
          digitalWrite(Lled,LOW);
          digitalWrite(Rled,LOW);
      }    
    }
    myservo.write(45);
    digitalWrite(Lled,LOW);
    digitalWrite(Rled,LOW);
}    



void loop()
{  
  char cmd = Serial.read();  // 讀取藍芽訊號並於下方進行判斷
  
  int SL = digitalRead(SensorLeft);
  int SR = digitalRead(SensorRight);
  
  if((SL == HIGH) && (SR == HIGH))  
  {
      digitalWrite(detectled, HIGH);
  }
  else
      digitalWrite(detectled, LOW);
    
       
  switch(cmd)  // 執行藍芽對應指令
  {
    case 'B':  // 倒車
      back(5);
      Bledlight();
      break;
 
    case 'L':  // 左轉
      turnL(5);
      Lledlight();
      break;
        
    case 'R':  // 右轉
      turnR(5);
      Rledlight();
      break;
      
    case 'F':  // 前進
      advance(5);
      Fledlight();
      break;
        
    case 'S':  // 停止
        stopRL(5);
        Sledlight();
        break;

    case 'O':  // laser
        fire();
        break;
        
    case 'M':  // music
        music();
        break;
    case 'T':  
        detection();
        break;  
  }
    
}
