// INCLUDE LIBRARIES
#include "Arduino.h"
#include "Wire.h" // For I2C
#include "LCD.h" // For LCD
#include "DS18B20.h" //TEMPERATURE
#include "OneWire.h"
#include "DallasTemperature.h"
#include "LDR.h" //BRIGHTNESS
#include "ESP8266.h" //WIFI
#include "dht.h" //HUMIDITY
#include "LiquidCrystal_PCF8574.h"

//PIN DEFINITIONS
#define dht_apin 2 
#define LDR_PIN_SIG  A0
#define respin A6 //sensor pin used
#define ONE_WIRE_BUS 3 

//GLOBAL VARIABLES and DEFINES
int ldrAverageLight;
int resval = 0; 

#define LCD_ADDRESS 0x27
// Define LCD characteristics
#define LCD_ROWS 4
#define LCD_COLUMNS 20
#define SCROLL_DELAY 150
#define BACKLIGHT 255
#define THRESHOLD_ldr   100

// OBJECT INITIALIZATION
dht DHT; 
LDR ldr(LDR_PIN_SIG);
OneWire oneWire(ONE_WIRE_BUS); 
 // Setup a oneWire instance to communicate with any OneWire devices 
// Pass our oneWire reference to Dallas Temperature.
DallasTemperature sensors(&oneWire);
LiquidCrystal_PCF8574 lcd20x4;


void setup() {
  // put your setup code here, to run once:
  
  // Use the Serial Monitor to view printed messages
  Serial.begin(9600); //sets serial port for communication
  while (!Serial) ; // wait for serial port to connect. Needed for native USB
  Serial.println("start");

  // initialize the lcd
    lcd20x4.begin(LCD_COLUMNS, LCD_ROWS, LCD_ADDRESS, BACKLIGHT); 

  ldrAverageLight = ldr.readAverage();
  // Start up the library
  sensors.begin();  
}



void loop() {
  // put your main code here, to run repeatedly:

   // lcd20x4.clear();                          // Clear LCD screen.
   
   DHT.read11(dht_apin);
   lcd20x4.selectLine(1);                    // Set cursor at the begining of line 1
   lcd20x4.print("Humidity = ");
   lcd20x4.print(DHT.humidity);
   lcd20x4.print("%  ");

   sensors.requestTemperatures(); // Send the command to get temperatures
   lcd20x4.selectLine(2);                    // Set cursor at the begining of line 2
   lcd20x4.print("Temperature = ");
   lcd20x4.print(sensors.getTempCByIndex(0));
   lcd20x4.print("C  ");

   // Get current light reading
   int ldrSample = ldr.read();
   lcd20x4.selectLine(3);                    // Set cursor at the begining of line 3
   lcd20x4.print(F("Light Sample = ")); lcd20x4.print(ldrSample);

   resval = analogRead(respin); //Read data from analog pin and store it to resval variable
   //lcd20x4.selectLine(4);                    // Set cursor at the begining of line 4 
   Serial.print("Water lvl = "); 
   if (resval<=75){ 
     Serial.print("Empty "); 
   } 
   else if (resval>75 && resval<=150){
     Serial.print("Low "); 
   } 
   else if (resval>150 && resval<=225){
     Serial.print("Medium "); 
   } 
   else if (resval>225){ 
     Serial.print("High"); 
   } 
    
   delay(1000);//Wait 1 seconds before accessing sensor again.
}
