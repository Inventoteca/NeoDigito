/* NeoDigito example code: Clock using ESP32 or ESP8266 wifi NTP Time from Server

    Example code to show the delimeter feature. This sketch displays time on a display with 4 digits
    and one colon which flashes when the seconds change.

    Created and empowered by Inventoteca & Xircuitos.
	Puebla, Pue. October 20, 2022.

    https://github.com/Inventoteca/NeoDigito

    This example code is in the public domain.

*/

#include <NeoDigito.h>
#if defined(ESP8266)
#include <ESP8266WiFi.h>  // For ESP8266
#else
#include <WiFi.h>           // For ESP32
#endif

#include "time.h"

#define PIN         2   // Pin where the display will be attached, ESP-01 Only GPIO 3(RX)
#define DIGITS      4   // Number of NeoDigitos connected
#define PIXPERSEG   3   // NeoPixels per segment, BIG version

// Specified the number of displays and the number of neopixels per segment, for more info about the argumets check documentation
NeoDigito display1 = NeoDigito(DIGITS, PIXPERSEG, PIN);

const char *ssid     = "YOUR_SSID";
const char *password = "YOUR_PASS";



const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = -6 * 60 * 60;         // Adjust for time zone for (UTC -6): -6 * 60 * 60
const int   daylightOffset_sec = 0;               // Set it to 3600 if your country observes Daylight saving time; otherwise, set it to 0.


#if defined(ESP8266)
bool getLocalTime(struct tm * info, uint32_t ms = 5000)
{
  uint32_t start = millis();
  time_t now;
  while ((millis() - start) <= ms) {
    time(&now);
    localtime_r(&now, info);
    if (info->tm_year > (2016 - 1900)) {
      return true;
    }
    delay(10);
  }
  return false;
}
#endif

void printLocalTime()
{
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    Serial.println("Failed to obtain time");
    display1.print("FAIL", Red);
    display1.show();
    return;
  }
  // For conver time infor into string for ESP8266
#if defined(ESP8266)
  char timeStringBuff[50];                          //BUffer for string conversion
  strftime(timeStringBuff, sizeof(timeStringBuff), "%A, %B %d %Y %H:%M:%S", &timeinfo);
  Serial.println(timeStringBuff); //ESP-01 Only Work on RX 
#else
  Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");   
#endif
  // Print Hour
  if (timeinfo.tm_hour < 10)                    // Less than 10 so place space or zero
    display1.print(" ");                        // You can print("0",CIAN)
  display1.print(timeinfo.tm_hour, Cian);

  // Print :
  if (timeinfo.tm_sec % 2 == 0)                 // Number of seconds is pair for blink delimiter
    display1.print(":", White);

  // Print Minutes
  if (timeinfo.tm_min < 10)
    display1.print("0", Pink);
  display1.print(timeinfo.tm_min, Pink);

  display1.show();
}


void setup()
{
  Serial.begin(115200);
  Serial.println("NeoClock");
  Serial.println("WiFi");

  display1.begin(); 			      // This fuction calls Adafruit_NeoPixel.begin() to configure.
  display1.clear();             // It erase the value.
  display1.print("wifi", Red);      // It prints the value.
  display1.show();              // Lights up the pixels.

  WiFi.begin(ssid, password);

  while ( WiFi.status() != WL_CONNECTED ) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("Connected");
  display1.updateColor(Green);    // Color specified by name RED, WHITE, YELLOW, etc or 32bit, or 8bit numbers (R, G, B)
  display1.show();
  delay(500);

  //init and get the time
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);
  printLocalTime();

  //disconnect WiFi as it's no longer needed
  WiFi.disconnect(true);
  WiFi.mode(WIFI_OFF);
}

void loop()
{
  printLocalTime();
  delay(1000);
  display1.clear();
}