/* NeoDigito example code: neodigito_adc

    It controls the display color with a single potenciometer on A0. The colour transition
    is from RED to GREEN. In addition, it shows the adc value where the pot is
    attached.

    Created and empowered by Inventoteca & Xircuitos.
  Puebla, Pue. June 11, 2021.

    https://github.com/Inventoteca/NeoDigito

    This example code is in the public domain.
    Remember that you must have installed Adafruit_NeoPixel library.
*/

#include <NeoDigito.h>

#define PIN         2   // Pin where the display will be attached
#define DIGITS      4   // Number of NeoDigitos connected
#define PIXPERSEG   3   // NeoPixels per segment, BIG version

// Specified the number of displays and the number of neopixels per segment, for more info about the argumets check documentation
NeoDigito display1 = NeoDigito(DIGITS, PIXPERSEG, PIN);

int color;
unsigned int adc;

void setup()
{
  Serial.begin(115200);
  display1.begin();             // Begin NeoDigito Display
  display1.print("ADC0");       // It prints the value.
  display1.updateColor(RAINBOW);
  display1.show();              // Lights up the pixels.
  delay(1000);
}

void loop()
{
  adc = analogRead(A0);         // Read ADC potenciometer on A0
  Serial.println(adc);
  color = map(adc, 0, 4095, 0, 255); // ADC for ESP32 is: (0 - 4095)

  short R = 255 - color;        // Decrement RED color
  short G = color;              // Increment GREEN color
  short B = 0;                  // OFF blue color

  if (adc < 10)
    display1.print(" ");        // It prints a space for rigth aling.
  if (adc < 100)
    display1.print(" ");        // It prints a space for rigth aling.
  if (adc < 1000)
    display1.print(" ");        // It prints a space for rigth aling.

  display1.setColor(R, G, B);   // Sets the display color.
  display1.print(adc);          // It prints the adc value.
  display1.show();              // Lights up the pixels.
  delay(100);
}
