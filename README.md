# smartBUTTON
discrete and virtual button arduino library

Supported functions:

- BUTTON(byte _pin, byte _state = 0, unsigned int _dreb = 10);     // digitalPin number, state pin pressed, debounce time (cycles);
- BUTTON(byte* btn_ptr, byte _state = 0, unsigned int _dreb = 10); // pointer to variable of the virtual button
- void setHoldTime(unsigned int _hold = 1000);                     // set hold time (cycles)
- void setDreb(unsigned int _dreb = 50);                           // set debounce time (cycles)
- void handle();                                                   // handle of uses button;
- void setCallBack(CallBack func_ptr);                             // set callback function for onClick and onHold

- bool isIT(;        // return the active state pin
- bool isNOT();      // return the non active state pin
- bool isPressed();  // return true while button pressed (after debounce)
- bool isReleased(); // return true while button released (after debounce)
- bool onPressed();  // return transition flag at the pressed state (the flag is reset after the function call)
- bool onReleased(); // return transition flag at the released state (the flag is reset after the function call)
- bool onClick();    // return true when clicked button (pressed less than hold time)
- bool onHold();     // return transition flag when hold button
- bool isHold();     // return true while button is hold
- bool rst();        // reset all flags (desirable to use at the end of the processing cycle buttons)

//////////////////////////////////////////////////////////
//  HOW TO USE:
//////////////////////////////////////////////////////////
#include "BUTTON.h"

#define BTN_PIN  5                         // pin of digital button
byte btn_state = 0;                        // state of virtual button

unsigned long previousMillis = 0;          // 
const long interval          = 1000;       // 

// add digital button
BUTTON digitalBTN(BTN_PIN);                // simple definition
//BUTTON digitalBTN(BTN_PIN, HIGH);        // detect "HIGH" when pressed (default "LOW")
//BUTTON digitalBTN(BTN_PIN, HIGH, 20);    // reinit debounce (default 10)

// add virtual button
//BUTTON virtualBTN(&btn_state);           // simple definition
BUTTON virtualBTN(&btn_state, HIGH,);      // detect "HIGH" when pressed (default "LOW")
//BUTTON virtualBTN(&btn_state, HIGH, 20); // reinit debounce (default 10)

void setup() {
  Serial.begin(115200);
  digitalBTN.setHoldTime(1500);             // set hold time if necessary (default 1000)
  virtualBTN.setHoldTime(1500);             // set hold time if necessary (default 1000)
  //digitalBTN.setDreb(50);                 // We can override debounce at any time
  //virtualBTN.setDreb(50);                 // We can override debounce at any time
}

void loop() {

  unsigned long currentMillis = millis();
  if (currentMillis - previousMillis >= interval) {
    previousMillis = currentMillis;
    myLoop_1ms();
  }
  
}

void myLoop_1ms() {
  
  // 1. First handle button:
  digitalBTN.handle();
  virtualBTN.handle();
  
  // 2. Then query the state:
  if(digitalBTN.onClick()) Serial.println("digitalBTN.onClick");
  if(virtualBTN.onClick()) Serial.println("digitalBTN.onClick");
  if(digitalBTN.onHold())  Serial.println("digitalBTN.onHold");
  if(virtualBTN.onHold())  Serial.println("digitalBTN.onHold");
  
  // 3. And reset all flags if necessary:
  digitalBTN.rst();
  virtualBTN.rst();
  
}
