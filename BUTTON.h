#ifndef BUTTON_H
#define BUTTON_H

#include <Arduino.h>

class BUTTON 
{
  public:

  BUTTON(byte _pin, byte _state = 0, unsigned int _dreb = 10);
  void setHoldTime(unsigned int _hold = 1000); // задает время срабатывания удержания кнопки
  void setDreb(unsigned int _dreb = 50);       // задает антидребезг кнопки
  void handle();      // обработчик кнопки
  byte isPressed();   // если нажата
  byte isReleased();  // если отпущена
  byte onPressed();   // при нажатии кнопки
  byte onReleased();  // при отпускании кнопки
  byte onClick();     // если клацнули (нажали и отпустили до срабатывания удержания)
  byte onHold();      // если сработало удержание
  byte isHold();      // удерживается
  byte isIT();        // 
  
  typedef void(*CallBack)();
  void setCallBack(CallBack func_ptr);
  private:
  
  void onHandle();                  // действие обработчика кнопки
  unsigned int previousTime;        // вспомогательная таймера
  byte         pin_number;          // номер пина кнопки
  byte         pin_dreb;            // 
  const byte   pin_pressed_state;   // состояние пина при котором кнопка считается нажатой (0-low; 1-high)
  unsigned int pin_holdTime;        // вспомогательная таймера  
  unsigned int pin_hold_counter;    // 
  byte         pin_state_flag;      // 
  unsigned int pin_dreb_counter;    // 
  byte         pin_onPressed_flag;  // 
  byte         pin_onReleased_flag; // 
  byte         pin_onHold_flag;     // 
  
  CallBack cb_func;
};

#endif // BUTTON_H
