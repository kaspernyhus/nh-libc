/*
---------------------------------
Pushbutton module C++
---------------------------------
v1.0

Kasper Nyhus Kaae
2021
*/

#ifndef BUTTON_H_
#define BUTTON_H_

#include <cstdint>
#include <iostream>

using namespace std;


/* BTN State Machine states */
enum states {
  LISTEN,
  WAIT,
  CHECK,
  LONG,
  DOUBLE  
};


class BTN {
  private:
    bool _push_detected;
    uint8_t _state;
    uint16_t _tick_timer;
    uint8_t debounce_ticks;
    uint16_t long_press_ticks;
  
    uint8_t (*readPin)(void);
    void (*onPress)(void);
    void (*onLongPress)(void);
    void (*onDoublePress)(void);
  
  
  public:
    BTN(uint8_t (*readPin)(void), uint8_t debounce_ticks=20, uint16_t long_press_ticks=1000);
    void attachPress(void (*onPress)(void));
    void attachLongPress(void (*onLongPress)(void));
    void tick();
};


#endif /* BUTTON_H_ */