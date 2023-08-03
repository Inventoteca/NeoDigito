#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecure.h>
#include <NeoDigito.h>
#include "time.h"

#define PIN         2   // Pin where the display will be attached, ESP-01 Only GPIO 3(RX)
#define DIGITS      4   // Number of NeoDigitos connected
#define PIXPERSEG   2   // NeoPixels per segment, BIG version

NeoDigito display1 = NeoDigito(DIGITS, PIXPERSEG, PIN);

const char* ssid = "ssid-network";
const char* password = "password";
String city = "city";

String url = "https://wttr.in/" + city + "?format=%C+%f+%h+%T+%l&lang=es";
const char* ntpServer = "pool.ntp.org";
const long  gmtOffset_sec = -6 * 60 * 60;         // Adjust for time zone for (UTC -6): -6 * 60 * 60
const int   daylightOffset_sec = 0;               // Set it to 3600 if your country observes Daylight saving time; otherwise, set it to 0.


unsigned long previousMillisTime = 0;
unsigned long previousMillisWeather = 0;
unsigned long startDisplayTime = 0;
const long intervalTime = 500;
const long intervalWeather = 30000;
const long displayDuration = 2000;
const long displayDurationConditions = 500;
int weatherStage = 0;
bool displayingWeather = false;
String condition, temperature, humidity;


// ------------------------------- printLocalTime
void printLocalTime()
{
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    Serial.println("Failed to obtain time");
    display1.print("FAIL", Red);
    return;
  }
  // For conver time infor into string for ESP8266
  char timeStringBuff[50];                          //BUffer for string conversion
  strftime(timeStringBuff, sizeof(timeStringBuff), "%A, %B %d %Y %H:%M:%S", &timeinfo);
  Serial.println(timeStringBuff); //ESP-01 Only Work on RX
  display1.setCursor(0);

  // Variable para almacenar la hora como cadena
  String timeString = "";

  // Print Hour
  if (timeinfo.tm_hour < 10) {
    timeString += " "; // Puedes usar '0' en lugar de un espacio si prefieres
  }
  timeString += String(timeinfo.tm_hour);
  display1.print(timeString, Cian); 

  // Print Minutes
  timeString = "";
  if (timeinfo.tm_min < 10) {
    timeString += "0";
  }
  timeString += String(timeinfo.tm_min);
  display1.print(timeString, Pink); 

  // Print :
  if (timeinfo.tm_sec % 2 == 0) { // Número de segundos es par
    display1.updateDelimiter(2, White);
  }

}

void setup()
{
  Serial.begin(115200);
  Serial.println("NeoClock");
  Serial.println("WiFi");

  display1.begin();             // This fuction calls Adafruit_NeoPixel.begin() to configure.
  display1.setBrightness(64);
  //display1.clear();             // It erase the value.
  display1.print("wifi", Red);      // It prints the value.
  //display1.show();              // Lights up the pixels.

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
  //WiFi.disconnect(true);
  //WiFi.mode(WIFI_OFF);
}


void loop() {
  unsigned long currentMillis = millis();

  if (currentMillis - previousMillisTime >= intervalTime && !displayingWeather) {
    previousMillisTime = currentMillis;
    printLocalTime();
  }

  if (currentMillis - previousMillisWeather >= intervalWeather && !displayingWeather) {
    previousMillisWeather = currentMillis;
    displayingWeather = true;
    weatherStage = 0;

    if (WiFi.status() == WL_CONNECTED) {
      WiFiClientSecure client;
      HTTPClient http;

      // Ignore SSL certificate errors
      client.setInsecure();

      http.begin(client, url);
      int httpCode = http.GET();

      if (httpCode > 0) {
        String payload = http.getString();
        Serial.println(payload);

        int plusSign = payload.indexOf('+');
        int percentSign = payload.indexOf('%');
        int colonSign = payload.indexOf(':');
        int minusSign = payload.lastIndexOf('-');
        int lastSpace = payload.lastIndexOf(' ');

        String time = payload.substring(percentSign + 2, minusSign - 1);  // Time is between the percentage sign and the minus sign
        String timezone = payload.substring(minusSign, lastSpace);  // Timezone is between the minus sign and the last space
        String location = payload.substring(lastSpace + 1);  // Location is everything after the last space
        condition = "   " + location + " " +  payload.substring(0, plusSign - 1);
        temperature = payload.substring(plusSign + 1, percentSign - 3);
        humidity = payload.substring(percentSign - 2, percentSign + 1);

        startDisplayTime = currentMillis;
      }

      http.end();
    }
  }

  if (displayingWeather) {
    if (weatherStage <= 2 && currentMillis - startDisplayTime >= displayDuration) {
      startDisplayTime = currentMillis;
      display1.clear();
      weatherStage++;
      if (weatherStage == 1) {
        display1.print(temperature, Purple);
      } else if (weatherStage == 2) {
        display1.print(humidity, Cian);
      }
    } else if (weatherStage > 2 && currentMillis - startDisplayTime >= displayDurationConditions) {
      startDisplayTime = currentMillis;
      display1.clear();
      weatherStage++;
      int startChar = weatherStage - 3;
      if (startChar < condition.length()) {
        String conditionSnippet = condition.substring(startChar, startChar + 4);
        display1.print(conditionSnippet, Yellow);
      } else {
        displayingWeather = false;
      }
    }
  }
}