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

#define SensorLeft    A1  
#define SensorRight   A0  
#define detectled     5

#define US_Trig  A5  
#define US_Echo  A4  

#define Servo_Pin    A2  
#define servo_delay  250 
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


boolean USstate=0;

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
  analogWrite(MotorA_PWMA,150);    
  analogWrite(MotorB_PWMB,150);    
  
  pinMode(LaserPIN,OUTPUT);

  pinMode(SensorLeft,   INPUT); 
  pinMode(SensorRight,  INPUT);
  pinMode(detectled,OUTPUT);
  pinMode(US_Trig, OUTPUT);
  pinMode(US_Echo, INPUT);
  myservo.attach(Servo_Pin);
  myservo.write(90);
}

void advance(int a)    // 前進
{
    digitalWrite(MotorA_I1,HIGH);   
    digitalWrite(MotorA_I2,LOW);
    digitalWrite(MotorB_I3,HIGH);   
    digitalWrite(MotorB_I4,LOW);
    delay(a * 100);
}

void turnR(int d)    //右轉
{
    digitalWrite(MotorA_I1,LOW);    
    digitalWrite(MotorA_I2,HIGH);
    digitalWrite(MotorB_I3,HIGH);   
    digitalWrite(MotorB_I4,LOW);
    delay(d * 100);
}

void turnL(int e)    //左轉
{
    digitalWrite(MotorA_I1,HIGH);   
    digitalWrite(MotorA_I2,LOW);
    digitalWrite(MotorB_I3,LOW);    
    digitalWrite(MotorB_I4,HIGH);
    delay(e * 100);
}    

void stopRL(int f)  //停止
{
    digitalWrite(MotorA_I1,HIGH);   
    digitalWrite(MotorA_I2,HIGH);
    digitalWrite(MotorB_I3,HIGH);   
    digitalWrite(MotorB_I4,HIGH);
    delay(f * 100);
}

void back(int g)    //後退
{
    digitalWrite(MotorA_I1,LOW);    
    digitalWrite(MotorA_I2,HIGH);
    digitalWrite(MotorB_I3,LOW);    
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

void music()//生日快樂歌
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

int detection()    
{
    int Car_Direction = 0;
    int F_Distance = 0;
    int R_Distance = 0;
    int L_Distance = 0;
    F_Distance = Ask_Distance(90);  
    
    if(F_Distance < 10)  
    {
         stopRL(1);
         back(2);
         myservo.write(90);
         alarm();
    }
    if(F_Distance < 25)  
    {
        stopRL(1);
        R_Distance = Ask_Distance(30);    
        myservo.write(90);
        L_Distance = Ask_Distance(150);  
        myservo.write(90);
        if ((L_Distance < 10) && (R_Distance < 10))  
        {
            Car_Direction = Bgo;  
        }
        else if(L_Distance > R_Distance)  
        {
            Car_Direction = Lgo;  
        }
        else
        {
            Car_Direction = Rgo;  
        }         
    }
    else
    {
        Car_Direction = Fgo;     
    }
    return Car_Direction;
}  

int Ask_Distance(int dir)  
{
    myservo.write(dir);  
    delay(servo_delay);  
    
    digitalWrite(US_Trig, LOW);   
    delayMicroseconds(2);
    digitalWrite(US_Trig, HIGH); 
    delayMicroseconds(10);
    digitalWrite(US_Trig, LOW);  
    float distance = pulseIn(US_Echo, HIGH);
    distance = distance / 5.8 / 10;  
    Serial.print("Distance:"); 
    Serial.println(distance); 
    Serial.print('\n');
    return distance;
}

void loop()
{  
  char cmd = Serial.read();  
  
  int SL = digitalRead(SensorLeft);
  int SR = digitalRead(SensorRight);
  
  if((SL == HIGH) && (SR == HIGH))  
  {
      digitalWrite(detectled, HIGH);
  }
  else
      digitalWrite(detectled, LOW);
    
       
  switch(cmd)  
  {
    case 'B':  
      back(5);
      Bledlight();
      break;
 
    case 'L': 
      turnL(5);
      Lledlight();
      break;
        
    case 'R':  
      turnR(5);
      Rledlight();
      break;
      
    case 'F':  
      advance(5);
      Fledlight();
      break;
        
    case 'S':  
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
        USstate=1;
        while(USstate==1){
            switch(detection())  
            {
                case Bgo:    
                    back(2);                 
                    turnL(1);               
                    Serial.print(" Reverse "); 
                    break;
             
                case Lgo:    
                    back(1);                
                    turnL(2);                 
                    Serial.print(" Left ");   
                    break;
                    
                case Rgo:    
                    back(1);                   
                    turnR(2);                
                    Serial.print(" Right ");   
                    break;
                    
                case Fgo:    
                    advance(1);                  
                    Serial.print(" Advance ");  
                    Serial.print("   ");
                    break;
            }
            char com=Serial.read();
            if(com=='S'){
              stopRL(5);
              Sledlight();
              myservo.write(90);
              break;
            }
              
        }
        
            break;  
  }
   
}
