#ifndef BUTTON_H
#define BUTTON_H

#include <Arduino.h>

class BUTTON 
{
  
  public:

  BUTTON(byte _pin, byte _state = 0, unsigned int _dreb = 10);
  BUTTON(byte* btn_ptr, byte _state, unsigned int _dreb);
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
  byte isNOT();       // 
  
  typedef void(*CallBack)();
  void setCallBack(CallBack func_ptr);
  void setBeepCallBack(CallBack func_ptr);
  void setHoldCallBack(CallBack func_ptr);
  void setClickCallBack(CallBack func_ptr);
  private:
  
  void onHandle();            // действие обработчика кнопки
  byte         pin_number;                 // номер пина кнопки
  byte         pin_dreb;                   // 
  const byte   pin_pressed_state;          // состояние пина при котором кнопка считается нажатой (0-low; 1-high)
  unsigned int previousTime = 0;           // вспомогательная таймера
  unsigned int pin_holdTime        = 1000; // вспомогательная таймера  
  unsigned int pin_hold_counter    = 0;    // 
  byte         pin_state_flag      = 0;    // 
  unsigned int pin_dreb_counter    = 0;    // 
  byte         pin_onPressed_flag  = 0;    // 
  byte         pin_onReleased_flag = 0;    // 
  byte         pin_onHold_flag     = 0;    // 
  byte         pin_onClick_flag    = 0;    //
  byte*        btn                 = 0;    // указатель виртуальной кнопки
  
  CallBack cb_func;
  CallBack beep_func;
  CallBack hold_func;
  CallBack click_func;
};

#endif // BUTTON_H
