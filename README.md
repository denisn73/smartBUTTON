# smartBUTTON
discrete and virtual button arduino library

Supported functions:

- BUTTON(byte _pin, byte _state = 0, unsigned int _dreb = 10); // digitalPin number, state pin pressed, debounce time (cycles);
- void setHoldTime(unsigned int _hold = 1000);                 // set hold time (cycles)
- void setDreb(unsigned int _dreb = 50);                       // set debounce time (cycles)
- void handle();                                               // handle of uses button;
- void setCallBack(CallBack func_ptr);                         // set callback function for onClick and onHold

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
