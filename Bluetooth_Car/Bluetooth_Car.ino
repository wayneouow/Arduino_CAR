//*******************************************************************************
//    第5堂 手機與PC遙控實驗
//   
//    開發環境：Arduino IDE 1.6.5 以上
//    測試使用開發板型號：Arduino UNO R3 / Arduino Genuino
//    台灣物聯科技有限公司：https://www.taiwaniot.com.tw
//    業務諮詢: 0971-209-389
//    客服專線: 06-2596159
//    傳真電話: 06-2803781
//*******************************************************************************

// L298N 馬達驅動板
// 宣告 MotorA 為右邊
// 宣告 MotorB 為左邊
#include<Servo.h>
#define MotorA_I1     8  //定義 I1 接腳
#define MotorA_I2     9  //定義 I2 接腳
#define MotorB_I3    10  //定義 I3 接腳
#define MotorB_I4    11  //定義 I4 接腳
#define MotorA_PWMA    7  //定義 PWMA (PWM調速) 接腳
#define MotorB_PWMB    6  //宣告 PWMB (PWM調速) 接腳
#define Rled    12
#define Lled    13

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

void loop()
{
  int cmd = Serial.read();  // 讀取藍芽訊號並於下方進行判斷
    
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
        
  ////////////////////////////////////////////////////////
  //  您可以額外再自行定義指令，搭配藍芽或 PC端遙控軟體
  //  新增的指令可以採用 case 來宣告特定接收字元運作，並
  //  使用 break; 來終止。
  ////////////////////////////////////////////////////////

    case 'T':  // 自我檢測
        break;
        
    case 'J':  // 舞蹈
        break;
        
    case 'N':  // 超音波測距查詢
        break;
  }
}
