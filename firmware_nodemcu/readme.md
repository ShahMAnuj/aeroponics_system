Make sure the "USB to UART VCP Drivers" are installed, otherwise ArduinoIDE won't detect "COM Port":

Silicon Labs: [CP210x USB to UART Bridge VCP Drivers](https://www.silabs.com/developers/usb-to-uart-bridge-vcp-drivers) 

You will need to download the files for the following (non-inbuilt) libraries:
* LiquidCrystal_PCF8574.h
* dht.h
* DS18B20.h
* LDR.h

To send data to ThingSpeak.com, you will also need these libraries:
* ESP8266WiFi.h
* ThingSpeak.h
