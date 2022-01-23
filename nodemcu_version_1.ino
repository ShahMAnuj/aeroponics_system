// Include Libraries

  //Libraries for LCD screen
  #include "Arduino.h"
  #include "Wire.h"
  #include "LiquidCrystal_PCF8574.h"

  //Libraries for DHT11
  #include "dht.h"

  //Libraries for DH18B20
  #include "DS18B20.h" 

  //Libraries for LDR
  #include "LDR.h"

//PIN DEFINITIONS
#define DHT_PIN_DATA 0 
#define DS18B20WP_PIN_DQ  2
#define LDR_PIN_SIG  A0

//GLOBAL VARIABLES and DEFINES
int ldrAverageLight;

#define LCD_ADDRESS 0x27
// Define LCD characteristics
#define LCD_ROWS 4
#define LCD_COLUMNS 20
#define SCROLL_DELAY 150
#define BACKLIGHT 0

// object initialization
LiquidCrystal_PCF8574 lcd20x4;
dht DHT;
DS18B20 ds18b20wp(DS18B20WP_PIN_DQ);
LDR ldr(LDR_PIN_SIG);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200); //sets serial port for communication
  
  // initialize the lcd
  lcd20x4.begin(LCD_COLUMNS, LCD_ROWS, LCD_ADDRESS, BACKLIGHT);

  ldrAverageLight = ldr.readAverage();
}

void loop() {
  // put your main code here, to run repeatedly:

  DHT.read11(DHT_PIN_DATA);
   lcd20x4.selectLine(1);                    // Set cursor at the begining of line 1
   lcd20x4.print("Humidity = ");
   lcd20x4.print(DHT.humidity);
   lcd20x4.print("%  ");

  float ds18b20wpTempC = ds18b20wp.readTempC();
   lcd20x4.selectLine(2);                    // Set cursor at the begining of line 2
   lcd20x4.print("Temperature = "); 
   lcd20x4.print(ds18b20wpTempC); 
   lcd20x4.print("C  ");

  int ldrSample = ldr.read();
   lcd20x4.selectLine(3);                    // Set cursor at the begining of line 3
   lcd20x4.print("Brightness = ");  
   lcd20x4.print(ldrSample);
 

  delay(1000);//Wait 1 seconds before accessing sensor again.
}
