#include "button.h"


/**
 * BTN constructor
 * 
 * @param readPin button pin callback
 * @param debounce_ticks default 20(ms)
 * @param long_press_ticks default 1000(ms)
**/
BTN::BTN(uint8_t (*readPin)(void), uint8_t debounce_ticks, uint16_t long_press_ticks) 
  : _push_detected(false), _state(LISTEN), _tick_timer(0)
{
  readPin = readPin;
  debounce_ticks = debounce_ticks;
  long_press_ticks = long_press_ticks;
}


/**
 * BTN attach press function callback
 * 
 * @param onPress callback
**/
void BTN::attachPress(void (*onPress)(void))
{
  onPress = onPress;
}


/**
 * BTN attach long press function callback
 * 
 * @param onLongPress on a long press callback
**/
void BTN::attachLongPress(void (*onLongPress)(void)) 
{
  onLongPress = onLongPress;
}


/**
 * BTN check
 * 
 * must be called at interval ≈ 1ms
**/
void BTN::tick() {
  _tick_timer++;

  if(_push_detected == 0) {     // if no recent BTN push detected, read pin
    _push_detected = readPin();
  }
  
  if(_push_detected) {           // push recently detected
    
    if(_state == LISTEN) {       // restart _timer, goto _state 1
      _tick_timer = 0;
      _state = WAIT;
    }

    if(_state == WAIT) {         // stay in _state 1 till debounced (eg. 20 * 1ms _tick), goto _state 2
      if (_tick_timer > debounce_ticks) {
        _state = CHECK;
      }
    }

    if(_state == CHECK) {        // check if button is still pressed
      if ( !(readPin()) ) {
        onPress();
        _state = LONG;           // begin check if long press     
      }
      else {
        _push_detected = false;  // no valid button press detected
        _state = LISTEN;
      }
    }

    if (_state == LONG) {                    
      if ( !!(readPin()) ) {     // if during _state 3 button is released -> reset
        _push_detected = false;
        _state = LISTEN;
      }
      if (_tick_timer >= long_press_ticks) {      // check if long press time reached (eg. 1000 * 1ms _tick)
        onLongPress();
        _push_detected = false;   // reset
        _state = LISTEN;
      }
    }

    if (_state == DOUBLE) {
      _state = LISTEN;
    }
  }
}