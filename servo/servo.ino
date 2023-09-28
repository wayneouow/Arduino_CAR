#include <Servo.h> 
 
Servo myservo;  
 
int pos = 90;   

void setup() 
{ 
  myservo.attach(A5);                             
  myservo.write(pos); 
              
} 

void loop() 
{ 
   
} 
