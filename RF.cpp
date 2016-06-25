#include "RF.hpp"

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
  attachInterrupt(RF_IN,rf_ISR,CHANGE);
}

