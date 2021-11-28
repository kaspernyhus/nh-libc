#include "shiftregs.h"


/* ------------------------------- */
/*             74HC595             */
/* ------------------------------- */

/**
 * 74HC595 constructor
 * 
 * @param transmit function to transmit data (eg. SPI_master_transmit)
 * @param latch function call back that sets latch pin
**/
shift595::shift595(void (*transmit)(uint8_t), void (*latch)(void), uint8_t number_of_chips)
  : number_of_chips(number_of_chips)
{
  transmit = transmit;
  latch = latch;
}


/**
 * Shifts data out
 * 
 * @param data vector of data elements of uin8_t
**/
void shift595::shiftout(std::vector<uint8_t> &data) {
  for (int i=data.size(); i>=0; i--) {
    transmit(data.at(i));
  }
  latch();
}


/**
 * Shifts data out
 * 
 * @param data data elements of uin8_t
**/
void shift595::shiftout(uint8_t &data) {
  transmit(data);
  latch();
}


/**
 * Resets to all LOW
 * 
**/
void shift595::reset() {
  for (int i=0; i<number_of_chips; i++) {
    transmit(0x00);
  }
  latch();
}


// /* ------------------------------- */
// /*             74HC165             */
// /* ------------------------------- */

// void shift74HC165_init(shift74HC165_s * const self, void (*set_latch)(uint8_t state), uint8_t number_of_chips) {
//   self->number_of_chips = number_of_chips;
//   self->set_latch = set_latch;
// }


// void shift74HC165_read(shift74HC165_s * const self, uint8_t *receive_data) {
//   self->set_latch(HIGH);
//   _delay_us(10);
//   for (int i=self->number_of_chips-1; i>=0; i--) {
//     receive_data[i] = SPI_masterReceive();
//   }
//   _delay_us(10);
//   self->set_latch(LOW);
  
// }