#define SensorLeft    A1  //定義 左感測器 輸入腳
#define SensorRight   A0  //定義 右感測器 輸入腳
#define detectled     5

void setup()
{
  Serial.begin(115200);
  
  pinMode(SensorLeft,   INPUT); 
  pinMode(SensorRight,  INPUT);
  pinMode(detectled,OUTPUT);
}



void loop() 
{
  
  int SL = digitalRead(SensorLeft);
  int SR = digitalRead(SensorRight);
  
  if((SL == HIGH) && (SR == HIGH))  
  {
      digitalWrite(detectled, HIGH);
  }
  else
      digitalWrite(detectled, LOW);
}
