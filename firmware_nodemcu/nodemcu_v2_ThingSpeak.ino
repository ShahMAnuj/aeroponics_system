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

  //Libraries for DHT11
  #include "dht.h"

  //Library for ESP8266
  #include "ESP8266WiFi.h"

  //Library for ThingSpeak
  #include "ThingSpeak.h"

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

//Internet and ThingSpeak Configuration
char ssid[] = "Jio_1";        // your network SSID (name) 
char pass[] = "eivesiepohpiugee";    // your network password
int keyIndex = 0;            // your network key Index number (needed only for WEP)
WiFiClient  client;
unsigned long myChannelNumber = 1;
const char * myWriteAPIKey = "CQUPCMFTA1PJCHBC";

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200); //sets serial port for communication

  // initialize the lcd
  lcd20x4.begin(LCD_COLUMNS, LCD_ROWS, LCD_ADDRESS, BACKLIGHT);

  ldrAverageLight = ldr.readAverage();
  
  WiFi.mode(WIFI_STA);   
  ThingSpeak.begin(client);  // Initialize ThingSpeak
}

void loop() {
  // put your main code here, to run repeatedly:

  // connect or reconnect to WiFi
  if(WiFi.status() != WL_CONNECTED){
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    while(WiFi.status() != WL_CONNECTED){
      WiFi.begin(ssid, pass);  // Connect to WPA/WPA2 network. Change this line if using open or WEP network
      Serial.print(".");
      delay(5000);     
    } 
    Serial.println("\nConnected.");
  }

  // collect sensor data
  DHT.read11(DHT_PIN_DATA);
  float humidity = DHT.humidity;
  float temperature = ds18b20wp.readTempC();
  int brightness = ldr.read();

  // display sensor data to LCD
   lcd20x4.selectLine(1);                    // Set cursor at the begining of line 1
   lcd20x4.print("Humidity = ");
   lcd20x4.print(humidity);
   lcd20x4.print("%  ");

   lcd20x4.selectLine(2);                    // Set cursor at the begining of line 2
   lcd20x4.print("Temperature = "); 
   lcd20x4.print(temperature); 
   lcd20x4.print("C  ");

   lcd20x4.selectLine(3);                    // Set cursor at the begining of line 3
   lcd20x4.print("Brightness = ");  
   lcd20x4.print(brightness);

  // set the fields with the values
  ThingSpeak.setField(1, humidity);
  ThingSpeak.setField(2, temperature);
  ThingSpeak.setField(3, brightness);


  // write to ThingSpeak.
  int x = ThingSpeak.writeFields(myChannelNumber, myWriteAPIKey);
  
  delay(10*1000); //Wait 10 seconds before accessing sensor again.
}
