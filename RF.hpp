#include "HardwareDefines.hpp"
#include <avr/io.h>
#include <avr/interrupt.h>
#include <arduino.h>

#ifndef RF_HPP
#define RF_HPP

#define SHORT_PULSE  500
#define LONG_PULSE  1500
#define SHORT_MARGIN 300
#define LONG_MARGIN 300

#define BUFFER_SIZE  16

//bool rf_intFlag;
//int rf_newVal;

void rf_init();
void rf_checkPulse();
#endif
