/*
---------------------------------
Shift register module C++
74HC595
74HC165
---------------------------------
v1.0

Kasper Nyhus Kaae
2021
*/

#ifndef SHIFTREGS_H_
#define SHIFTREGS_H_

#include <cstdint>
#include <iostream>
#include <vector>


/* ------------------------------- */
/*             74HC595             */
/* ------------------------------- */
class shift595 {
  private:
    uint8_t number_of_chips;
    void (*latch)(void);
    void (*transmit)(uint8_t);
  public:
    shift595(void (*transmit)(uint8_t), void (*latch)(void), uint8_t number_of_chips=1);
    void shift595::shiftout(uint8_t &data);
    void shiftout(std::vector<uint8_t> &data);
    void reset();
};



/* ------------------------------- */
/*             74HC165             */
/* ------------------------------- */
// typedef struct {
//   uint8_t number_of_chips;
//   void (*set_latch)(uint8_t state);
// } shift74HC165_s;

// void shift74HC165_init(shift74HC165_s * const self, void (*set_latch)(uint8_t state), uint8_t number_of_chips);
// void shift74HC165_read(shift74HC165_s * const self, uint8_t *receive_data);


#endif /* SHIFTREGS_H_ */