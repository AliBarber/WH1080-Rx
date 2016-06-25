#include "Display.hpp"

Adafruit_ST7735 disp_tft = Adafruit_ST7735(DISP_CS, DISP_DC, DISP_MOSI, DISP_SCLK, DISP_RST);

void disp_setupDisplay()
{
//  //Setup the backlight output
  pinMode(DISP_BL,OUTPUT);
  disp_setBacklightLevel(128);

    
  disp_tft.initR(INITR_BLACKTAB);
  disp_tft.fillScreen(ST7735_BLACK);
  disp_tft.setCursor(0,0);
  disp_tft.setTextColor(ST7735_WHITE);
  disp_tft.setTextWrap(true);
  disp_tft.print("Hello World");
}
void disp_setBacklightLevel(int level)
{
  analogWrite(DISP_BL,level);
}

