#include "HardwareDefines.hpp"
#ifndef DATABUFFER_HPP
#define DATABUFFER_HPP

#define DATA_BUFFER_SIZE 256

struct TimeStamp
{
  byte hours;
  byte mins;
  byte secs;

  byte day;
  byte month;

};

struct WH1080Packet
{
  TimeStamp timestamp;
  byte rx_data [16];  
};

extern WH1080Packet rx_data_buffer[DATA_BUFFER_SIZE];
extern int          rx_data_buffer_idx;

#endif

