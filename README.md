# WH1080-Rx

__WH1080-Rx__ Is  a custom build of a 433MHz Receiver for the populer Maplin Weather station (http://www.maplin.co.uk/p/black-usb-wireless-touchscreen-weather-centre-n96gy "N96GY"), supporting WiFi and uploading data to a web-service or email directly. It's designed to replace or work in conjunction with the original receiver/USB module, receiving packets directly from the outdoor transmitter.
The main components are:
1. Teensy 3.2 CPU
2. 1.8in TFT Display
3. 433MHz Receiver Module
4. ESP2866 Module

Lots to do:
- Draw Schematic
- Implement everything

Trying to write the code as asynchronously as possible (interrupt based) - although it's in quite a C style. Want to fork and bring nice neat C++ness? Please do!
Also currently using teensyduino to get it up and running, might be a good idea to switch over to straight out Teensy Code/paradigms at some point.
