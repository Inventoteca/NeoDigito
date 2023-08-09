/*
    This example uses NeoDigitos, 7 segments displays based on Adafruit NeoPixel
    Use a ESP32 or ESP8266 and connect to internet to get Time and Weather
*/


#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecure.h>
#include <NeoDigito.h>
#include "time.h"

#define PIN         2   // Pin where the display will be attached, ESP-01 Only GPIO 3(RX)
#define DIGITS      4   // Number of NeoDigitos connected
#define PIXPERSEG   2   // NeoPixels per segment,3 for BIG version, 2 for MEDIO

NeoDigito neodisplay = NeoDigito(DIGITS, PIXPERSEG, PIN);

const char* ssid = "Inventoteca_2G";    // Your WiFi Network
const char* password = "science_7425";    // Password
String city = "Puebla";                 // Place name of your city for wheater

String url = "https://wttr.in/" + city + "?format=%C+%f+%h+%T+%l&lang=es";  // wheater service, change language
const char* ntpServer = "pool.ntp.org";           // NTC server for time
const long  gmtOffset_sec = -6 * 60 * 60;         // Adjust for time zone for (UTC -6): -6 * 60 * 60
const int   daylightOffset_sec = 0;               // Set it to 3600 if your country observes Daylight saving time; otherwise, set it to 0.


unsigned long previousMillisTime = 0;
unsigned long previousMillisWeather = 0;
unsigned long startDisplayTime = 0;
const long intervalTime = 500;
const long intervalWeather = 90000;
const long displayDuration = 2000;
const long displayDurationConditions = 500;
int weatherStage = 0;
bool displayingWeather = false;
String condition, temperature, humidity;

// Variables globales para almacenar la última hora y minutos conocidos
int lastKnownHour = -1;
int lastKnownMinute = -1;
bool lastKnownDelimiter = false; // Para almacenar el estado del delimitador
String dayAndDate;


// Función para convertir el número del día de la semana al nombre en español
String dayInSpanish(int dayOfWeek) {
  const char* days[] = {"Domingo", "Lunes", "Martes", "Miércoles", "Jueves", "Viernes", "Sábado"};
  return days[dayOfWeek];
}

String monthInSpanish(int month) {
  const char* months[] = {"Enero", "Febrero", "Marzo", "Abril", "Mayo", "Junio", "Julio", "Agosto", "Septiembre", "Octubre", "Noviembre", "Diciembre"};
  return months[month];
}

// ------------------------------- printLocalTime
void printLocalTime()
{
  struct tm timeinfo;
  if (!getLocalTime(&timeinfo)) {
    Serial.println("Failed to obtain time");
    neodisplay.print("FAIL", Red);
    return;
  }
  // Verificar si los segundos son pares
  bool isSecondEven = (timeinfo.tm_sec % 2 == 0);

  // Actualizar delimitador solo si ha cambiado
  if (isSecondEven != lastKnownDelimiter) {
    lastKnownDelimiter = isSecondEven;
    if (isSecondEven) {
      neodisplay.updateDelimiter(2, White);
    }
    else
      neodisplay.updateDelimiter(2, 0);
  }
  // Actualizar hora solo si ha cambiado
  if (timeinfo.tm_hour != lastKnownHour) {
    lastKnownHour = timeinfo.tm_hour;
    neodisplay.setCursor(0);
    String timeString = "";
    if (lastKnownHour < 10) {
      timeString += " ";
    }
    timeString += String(lastKnownHour);
    neodisplay.print(timeString, Cian);
  }

  // Actualizar minutos solo si han cambiado
  if (timeinfo.tm_min != lastKnownMinute) {
    lastKnownMinute = timeinfo.tm_min;
    String timeString = "";
    if (lastKnownMinute < 10) {
      timeString += "0";
    }
    timeString += String(lastKnownMinute);
    neodisplay.setCursor(2);
    neodisplay.print(timeString, Pink);
  }

  // Crear una cadena para el día y la fecha
  String day = dayInSpanish(timeinfo.tm_wday);
  String month = monthInSpanish(timeinfo.tm_mon);
  dayAndDate = "   " + day + " " + String(timeinfo.tm_mday) + " " + month + " "  + String(timeinfo.tm_year + 1900);

}


// ----------------------------------- setup
void setup()
{
  Serial.begin(115200);
  Serial.println("NeoClock");
  Serial.println("WiFi");

  neodisplay.begin();               // This fuction calls Adafruit_NeoPixel.begin() to configure.
  neodisplay.setBrightness(64);     // 25% of brightness, min 1 and max 255
  neodisplay.print("wifi", Red);    // It prints the value, on Red color.

  WiFi.begin(ssid, password);

  while ( WiFi.status() != WL_CONNECTED ) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
  Serial.println("Connected");
  neodisplay.updateColor(Green);    // Color specified by name Red, White, YELLOW, etc or 32bit, or 8bit numbers (R, G, B)
  delay(500);

  //init and get the time
  configTime(gmtOffset_sec, daylightOffset_sec, ntpServer);  // Once config is not WiFi connection needed
  printLocalTime();

}


// ----------------------------------- loop
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
      neodisplay.clear();
      weatherStage++;
      if (weatherStage == 1) {
        neodisplay.print(temperature, Purple);
      } else if (weatherStage == 2) {
        neodisplay.print(humidity, Cian);
      }
    } else if (weatherStage > 2 && currentMillis - startDisplayTime >= displayDurationConditions) {
      startDisplayTime = currentMillis;
      neodisplay.clear();
      weatherStage++;
      int startChar = weatherStage - 3;
      if (startChar < condition.length()) {
        String conditionSnippet = condition.substring(startChar, startChar + 4);
        neodisplay.print(conditionSnippet, Yellow);
      }
      // Luego mostrar el día y la fecha
      else if (startChar - condition.length() < dayAndDate.length()) {
        int dateChar = startChar - condition.length();
        String dateSnippet = dayAndDate.substring(dateChar, dateChar + 4);
        neodisplay.print(dateSnippet);
        neodisplay.updateColor(Rainbow);
      }
      else {
        displayingWeather = false;
        lastKnownHour = -1;
        lastKnownMinute = -1;
        lastKnownDelimiter = false;
      }
    }
  }
}