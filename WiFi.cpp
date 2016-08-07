#include "WiFi.hpp"
#include "HardwareDefines.hpp"

enum connection_init_stages{
  ECHO_OFF,
  SETUP_AS_STATION,
  SETUP_DHCP,
  CONNECTING_TO_AP,
  WAITING_FOR_IP_ADDRESS,
  GETTING_IP_ADDRESS,
  GOT_IP_ADDRESS
};

enum connection_status{
  WIFI_DISCONNECT,
  WIFI_CONNECTED,
  WIFI_GOT_IP
};


volatile int flag;
volatile enum connection_init_stages  connection_init_stage;
volatile enum connection_status      wifi_connection_status;

IntervalTimer mytimer;

void _echoOff()
{
  connection_init_stage = ECHO_OFF;
  Serial1.println("ATE0");
}

void _setupAsStation()
{
    connection_init_stage = SETUP_AS_STATION;
    Serial1.println("AT+CWMODE=3");
}

void _setupDHCP()
{
  connection_init_stage = SETUP_DHCP;
  Serial1.println("AT+CWDHCP=1,1");
}

void _connectToAP()
{
  connection_init_stage = CONNECTING_TO_AP;
  String cmd = "AT+CWJAP=";
  cmd += "\"VM773740-2G\"";
  cmd += ",\"ntshsyfp\"";
  Serial1.println(cmd);
}

void _readIPAddress()
{
  connection_init_stage = GOT_IP_ADDRESS;
  Serial1.println("AT+CIPSTA?");
}

void _timerCallback()
{
  mytimer.end();
  Serial.println("T");

 
    if(connection_init_stage == ECHO_OFF)
    {
      Serial.println("Echo off");
      _setupAsStation();
      return;
    }
    if(connection_init_stage == SETUP_AS_STATION)
    {
      Serial.println("Setup as station");
      _setupDHCP();
      return;
    }
    if(connection_init_stage == SETUP_DHCP)
    {
      Serial.println("DHCP Setup");
      _connectToAP();
    }
    if(connection_init_stage == GETTING_IP_ADDRESS)
    {
      Serial.println("Finding ip address");
      _readIPAddress();
    }
}

void wifi_init()
{
  Serial1.begin(115200);
  _echoOff();
}

void serialEvent1()
{

  if(connection_init_stage == GETTING_IP_ADDRESS)
  {
    
  }
  
  if(connection_init_stage == CONNECTING_TO_AP)
  {
    if(Serial1.find("WIFI CONNECTED"))
    {
      wifi_connection_status = WIFI_CONNECTED;
      connection_init_stage = WAITING_FOR_IP_ADDRESS;
    }
    return; // Don't start the timer or jump to the next stage
  }
  if(connection_init_stage == WAITING_FOR_IP_ADDRESS)
  {
    if(Serial1.find("WIFI GOT IP"))
    {
      connection_init_stage = GETTING_IP_ADDRESS;
      //Read the ip address back now
    }
  }
  else
  {
      while(Serial1.available())
      {
        Serial.print((char)Serial1.read());
      }
  }
  //Wait a second or two before sending the next command, but don't block the whole processor
  mytimer.begin(_timerCallback,2000000);
}


