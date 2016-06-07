#include <BUTTON.h>

BUTTON btn1(5);
BUTTON btn2(6, LOW);

void setup() {  
  Serial.begin(9600);
  btn1.setDreb(50);
  btn2.setDreb(50);
  btn1.setHoldTime(1000);
  btn2.setHoldTime(1000);
}

void loop() {  
  btn1.handle();
  btn2.handle();
  
  if(btn1.onPressed()) Serial.println("btn1 onPressed");
  if(btn2.onPressed()) Serial.println("btn2 onPressed");
  
  if(btn1.onReleased()) Serial.println("btn1 onReleased");
  if(btn2.onReleased()) Serial.println("btn2 onReleased");
  
  if(btn1.onHold()) Serial.println("btn1 onHold");
  if(btn2.onHold()) Serial.println("btn2 onHold");
  
  if(btn1.onClick()) Serial.println("btn1 onClick");
  if(btn2.onClick()) Serial.println("btn2 onClick");
  
}
