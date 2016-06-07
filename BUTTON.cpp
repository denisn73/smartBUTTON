#include "BUTTON.h"

BUTTON::BUTTON(byte _pin, byte _state, unsigned int _dreb) :
pin_number(_pin),
pin_pressed_state(_state),
pin_dreb(_dreb),
pin_state_flag(0),
pin_dreb_counter(0),
pin_onPressed_flag(0),
pin_onReleased_flag(0),
pin_onHold_flag(0),
previousTime(0),
pin_holdTime(1000),
pin_hold_counter(0)
{
  pinMode(pin_number, INPUT);
  if(pin_pressed_state) digitalWrite(pin_number, LOW);
  else                  digitalWrite(pin_number, HIGH);
  pin_dreb = _dreb;
}



void BUTTON::setHoldTime(unsigned int _time) {
  pin_holdTime = _time;
}

void BUTTON::setDreb(unsigned int _dreb) {
  pin_dreb = _dreb;
}

void BUTTON::handle() {
  unsigned long currentTime = micros();
  if(currentTime - previousTime >= 1000) {
    previousTime = currentTime;
    onHandle();
  }  
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
    }
    if(pin_hold_counter <= pin_holdTime) pin_hold_counter++;
    if(pin_hold_counter == pin_holdTime) pin_onHold_flag = 1;
  } else {
    if(pin_state_flag) {
      if(pin_dreb_counter < pin_dreb) pin_dreb_counter++;
      else {
        pin_dreb_counter = 0;
        pin_state_flag = false;
        pin_onReleased_flag = true;
        pin_onPressed_flag = false;
      }
    } else {
      pin_dreb_counter = 0;
    }
    pin_onHold_flag = 0;
    pin_hold_counter = 0;
  }
}

byte BUTTON::isIT() {
  return (digitalRead(pin_number) == pin_pressed_state);
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
  if(onReleased() && pin_hold_counter < pin_holdTime) {
	cb_func();
	return true;
  }
  return false;
}

byte BUTTON::onHold() {
  if(pin_onHold_flag) {
	pin_onPressed_flag = false;
    pin_onHold_flag    = false;
	cb_func();
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

