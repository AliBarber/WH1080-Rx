/***
 * Based on work by Kevin Sangeelee at http://www.susa.net/wordpress/2012/08/raspberry-pi-reading-wh1081-weather-sensors-using-an-rfm01-and-rfm12b/
 *                                  and http://www.susa.net/wordpress/2014/06/arduino-yun-reading-wh1080-using-aurel-rx-4mm5/
 *  This implementation aims to eliminate delay and wait loops using interrupts to time the pulses from the receiver
 */

#include "RF.hpp"
#include "Debug.hpp"

byte byte_buffer[BUFFER_SIZE];
byte buffer_idx = 0;
byte sig_seen = 0;

unsigned short shift_register = 0;
byte bit_count = 0;

unsigned long transition_t = micros();
unsigned long now, duration;
int val = 0;
int newVal;

void rf_ISR()
{
  cli();
  newVal += digitalRead(RF_IN) ? 1 : 0;
}

void rf_init()
{
  debug_sendLong("transition_t",transition_t);
  attachInterrupt(RF_IN,rf_ISR,CHANGE);
}

