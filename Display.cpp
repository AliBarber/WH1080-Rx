#include "Display.hpp"
#include "DataBuffer.hpp"

Adafruit_ST7735 disp_tft = Adafruit_ST7735(DISP_CS, DISP_DC, DISP_MOSI, DISP_SCLK, DISP_RST);

void disp_updateFromPacket(struct WH1080Packet* packet)
{
    int temp_raw = 0;
    byte nibble_d = packet->rx_data[1] & 0xF;
    temp_raw = nibble_d << 8;
    temp_raw = temp_raw | packet->rx_data[2];
    float temp_value = temp_raw - 0x190;
    temp_value = temp_value / 10;
    Serial.print("Temperature from buffer: ");
    Serial.println(temp_value);
    disp_tft.fillScreen(ST7735_BLACK);
    disp_tft.setCursor(0,0);
    disp_tft.setTextSize(1);
    disp_tft.print("Outside:\n\n");
    disp_tft.setTextSize(3);
    disp_tft.print(temp_value);
}

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
  disp_tft.print("Waiting for data...");
}
void disp_setBacklightLevel(int level)
{
  analogWrite(DISP_BL,level);
}


