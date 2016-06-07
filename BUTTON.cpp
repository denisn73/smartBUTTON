#include "BUTTON.h"

BUTTON::BUTTON(byte _pin, byte _state, unsigned int _dreb) :
pin_number(_pin),
pin_pressed_state(_state),
pin_dreb(_dreb)
{
  pinMode(pin_number, INPUT);
  if(pin_pressed_state) digitalWrite(pin_number, LOW);
  else                  digitalWrite(pin_number, HIGH);
}

BUTTON::BUTTON(byte* btn_ptr, byte _state, unsigned int _dreb) :
pin_pressed_state(_state),
pin_dreb(_dreb),
btn(btn_ptr)
{
}

void BUTTON::setHoldTime(unsigned int _time) {
  pin_holdTime = _time;
}

void BUTTON::setDreb(unsigned int _dreb) {
  pin_dreb = _dreb;
}

void BUTTON::handle() {
  //unsigned long currentTime = micros();
  //if(currentTime - previousTime >= 1000) {
  //  previousTime = currentTime;
    onHandle();
  //}  
}

void BUTTON::onHandle() {
  if( isIT() ) {
    if(!pin_state_flag) {
      if(pin_dreb_counter < pin_dreb) pin_dreb_counter++;
      else {
        pin_dreb_counter = 0;
        pin_state_flag = true;
        pin_onPressed_flag = true;
        pin_onReleased_flag = false;
      }
    } else {
      pin_dreb_counter = 0;
      if(pin_hold_counter <= pin_holdTime) pin_hold_counter++;
      if(pin_hold_counter == pin_holdTime) pin_onHold_flag = 1;
    }    
  } else {
    if(pin_state_flag) {
      if(pin_dreb_counter < pin_dreb) pin_dreb_counter++;
      else {
        pin_dreb_counter = 0;
        pin_state_flag = false;
        pin_onReleased_flag = true;
        pin_onPressed_flag = false;
        if(pin_hold_counter < pin_holdTime) pin_onClick_flag = true;
        pin_hold_counter = 0;        
      }
    } else {
      pin_dreb_counter = 0;
      pin_onHold_flag = 0;
//      pin_hold_counter =0;
    }    
  }
}

byte BUTTON::isIT() {
  if(btn) return (*btn == pin_pressed_state);
  else    return (digitalRead(pin_number) == pin_pressed_state);
}

byte BUTTON::isNOT() {
  if(btn) return (*btn != pin_pressed_state);
  else    return (digitalRead(pin_number) != pin_pressed_state);
}

byte BUTTON::isPressed() {
  return pin_state_flag;
}

byte BUTTON::isReleased() {
  return !pin_state_flag;
}

byte BUTTON::onPressed() {
  if(pin_onPressed_flag) {
    pin_onPressed_flag  = false;
    pin_onReleased_flag = false;
    return true;
  }
  return false;
}

byte BUTTON::onReleased() {
  if(pin_onReleased_flag) {
    pin_onPressed_flag  = false;
    pin_onReleased_flag = false;
    return true;
  }
  return false;
}

byte BUTTON::onClick() {
  if(pin_onClick_flag) {
      pin_onClick_flag = false;
      pin_onReleased_flag = false;
      pin_onPressed_flag  = false;
      if(cb_func) cb_func();
    return true;
  }
  return false;
}

byte BUTTON::onHold() {
  if(pin_onHold_flag) {
    pin_onPressed_flag = false;
    pin_onHold_flag  = false;
    if(cb_func) cb_func();
    return true;
  }
  return false;
}

byte BUTTON::isHold() {
  if(pin_hold_counter >= pin_holdTime) return true;
  return false;
}

void BUTTON::setCallBack(CallBack func_ptr) { 
  cb_func = func_ptr; 
}

