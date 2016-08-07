#include "HardwareDefines.hpp"
#include <Adafruit_GFX.h>
#include <Adafruit_ST7735.h>


#ifndef DISPLAY_HPP
#define DISPLAY_HPP

void disp_setupDisplay();
void disp_setBacklightLevel(int);
void disp_updateFromPacket(struct WH1080Packet *packet);


#endif
