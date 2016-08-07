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
unsigned long duration;

volatile long pulseNow;
int val = 0;

bool rf_intFlag;
int rf_newVal;
int rf_intCount = 0;

void rf_checkPulse()
{
 if(transition_t <= pulseNow)
  {
    duration = pulseNow - transition_t;
  }
  else
  {
    duration = (~transition_t) + pulseNow;
  }
  if(rf_newVal != val)
  {
    transition_t = pulseNow;
    val = rf_newVal;

    /*
     *  If the pulse width (hi or low) is outside the
     *  range of the Fine Offset signal, then ignore them.
     */
    debug_sendLong("Duration",duration);
    if(duration < (SHORT_PULSE - SHORT_MARGIN) 
        || duration > (LONG_PULSE + LONG_MARGIN)) {
      // Meaningless pulse
      return;
    }
    debug_sendLong("Pulse",rf_newVal);
    /*
     *  If we reach here, then we have seen a potentially
     *  valid pulse. Shift the bit into the register.
     */
    if(rf_newVal == 1) 
    {
      // rising edge of a pulse (0 -> 1)
    } 
    else 
    {
      // falling edge of a pulse (1 -> 0)
      if( duration >= (SHORT_PULSE - SHORT_MARGIN) && duration <= (SHORT_PULSE + SHORT_MARGIN) ) 
      {
        // short pulse is binary '1'
        shift_register = (shift_register << 1) | 0x01;
        bit_count++;

 
      } 
      else if(duration >= (LONG_PULSE - LONG_MARGIN) && duration <= (LONG_PULSE + LONG_MARGIN)) 
      {
        // long pulse is binary '0'
        shift_register = (shift_register << 1);
        bit_count++;

      }
    }
    
    if((shift_register & 0xff) == 0xfa && buffer_idx == 0) 
    {
      // Found signature - discard pre-amble and leave 0x0a.
      shift_register = 0x0a;
      bit_count = 4;
      sig_seen = 1;  // Flag that the signature has been seen.


    } 
    else if(bit_count == 8 && sig_seen) 
    {
      // Got a byte, so store it if we have room.
     if(buffer_idx < BUFFER_SIZE) byte_buffer[buffer_idx++] = (byte)(shift_register & 0xff);
     else Serial.println("Buffer overflown...");
     
      shift_register = 0;
      bit_count = 0;
    }
  }
  else
  {
    if(duration > 5000)
    {
      if(buffer_idx > 0)
      {
        Serial.print("Found:  ");
        Serial.println(buffer_idx);
        for(int i = 0; i < buffer_idx; i++) {
//            for (byte mask = 0x80; mask; mask >>= 1) {
//              Serial.print(mask & byte_buffer[i] ? '1' : '0');
//            }
//            Serial.print(' ');
            Serial.println(byte_buffer[i]);
   
          }
        if(buffer_idx >= 2)
        {
          int temp_raw = 0;
          byte nibble_d = byte_buffer[1] & 0xF;
          temp_raw = nibble_d << 8;
          temp_raw = temp_raw | byte_buffer[2];
          float temp_value = temp_raw - 0x190;
          temp_value = temp_value / 10;
          Serial.print("Temperature: ");
          Serial.println(temp_value);
        }
        buffer_idx = 0;
      }
      shift_register = 0;
      bit_count = 0;
      sig_seen = 0;
      
    }
  }
}

void rf_ISR()
{
  cli();
  rf_newVal += digitalRead(RF_IN) ? 1 : 0;
  delayMicroseconds(5); // Uuugh
  rf_intCount++;
  if(rf_intCount == 10)
  {
     rf_intCount = 0;
     rf_newVal = (rf_newVal + 5) / 10;
     pulseNow = micros();
     rf_checkPulse();
  }
  sei();
}

void rf_init()
{
  debug_sendLong("transition_t",transition_t);
  rf_intFlag = false;
  rf_newVal = 0;
  pinMode(RF_IN,INPUT);
  attachInterrupt(digitalPinToInterrupt(RF_IN),rf_ISR,CHANGE);
}

