#include "HardwareDefines.hpp"
#include "Display.hpp"
#include "RF.hpp"
#include "Debug.hpp"
#include "DataBuffer.hpp"

struct       WH1080Packet rx_data_buffer[DATA_BUFFER_SIZE];
int          rx_data_buffer_idx = 0;

void setup() {
  // put your setup code here, to run once:
  disp_setupDisplay();
  rf_init();
  #ifdef DEBUG
  debug_init();
  #endif
}

void loop() {
  rf_loop();
  if(rf_newDataFlag)
  {
          Serial.println("New data flag...");
          disp_updateFromPacket(&rx_data_buffer[rx_data_buffer_idx-1]);
          rf_newDataFlag = 0;
  }
}
