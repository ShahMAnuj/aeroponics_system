                                        _           
                                       (_)          
  __ _  ___ _ __ ___  _ __   ___  _ __  _  ___ ___  
 / _` |/ _ \ '__/ _ \| '_ \ / _ \| '_ \| |/ __/ __| 
| (_| |  __/ | | (_) | |_) | (_) | | | | | (__\__ \ 
 \__,_|\___|_|  \___/| .__/ \___/|_| |_|_|\___|___/ 
                     | |                            
                     |_|                            
                 _                                  
                | |                                 
   ___ _   _ ___| |_ ___ _ __ ___                   
  / __| | | / __| __/ _ \ '_ ` _ \                  
  \__ \ |_| \__ \ ||  __/ | | | | |                 
  |___/\__, |___/\__\___|_| |_| |_|                 
        __/ |                                       
       |___/                                        

Welcome to the ReadMe file for the Firmware/Software for the Aeroponics System Project!

The main code for our project is stored as the "Firmware_with_ThingSpeak" INO file. 
You can open and compile this code using the Arduino IDE, 
but incase you don't have Arduino IDE, we have also provided a TXT file, to view the code.


This firmware is made for the NodeMCU ESP8266 microcontroller and IoT (internet of things) platform.
NOTE: Before uploading this code to NodeMCU via USB, Make sure the "USB to UART VCP Drivers" are 
installed, otherwise ArduinoIDE won't detect "COM Port":
* Silicon Labs: CP210x USB to UART Bridge VCP Drivers

For the Firmware to work, you will need the following (non-inbuilt) libraries,
which you can download from online:
* LiquidCrystal_PCF8574.h
* dht.h
* DS18B20.h
* LDR.h

To send data to ThingSpeak.com, you will also need these libraries, available online:
* ESP8266WiFi.h
* ThingSpeak.h
