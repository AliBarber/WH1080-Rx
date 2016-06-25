#include "Debug.hpp"

void debug_init()
{
  Serial.begin(115200);
}

void debug_sendLong(char* message, long data)
{
  Serial.printf("%s:%d",message, data);
}

