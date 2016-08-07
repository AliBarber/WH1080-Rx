#include "HardwareDefines.hpp"
#include "Display.hpp"
#include "RF.hpp"
#include "Debug.hpp"

extern bool rf_intFlag;
extern int  rf_newVal; 

void setup() {
  // put your setup code here, to run once:
  disp_setupDisplay();
  rf_init();
  #ifdef DEBUG
  debug_init();
  #endif
}

void loop() {
  // put your main code here, to run repeatedly:
//  if(rf_intFlag)
//  {
//      rf_checkPulse();
//      rf_intFlag = false;
//  }
}
