/* NeoDigito example code: Hello

  Print "Hola" on display, color select and blink

  Created by Inventoteca 

  https://github.com/Inventoteca/NeoDigito

  This example code is in the public domain.
  Remember that you must have installed Adafruit_NeoPixel library.
*/

#include <NeoDigito.h>

#define PIN         2   // Pin where the display will be attached
#define DIGITS      4   // Number of NeoDigitos connected
#define PIXPERSEG   3   // NeoPixels per segment,3 for BIG version, 2 for MEDIO

// Specified the number of displays and the number of neopixels per segment, for more info about the argumets check documentation 
NeoDigito display1 = NeoDigito(DIGITS, PIXPERSEG, PIN); 


void setup()
{
  display1.begin();             // This fuction calls Adafruit_NeoPixel.begin() to configure. 
  display1.setColor(Random);    // Color specified by name Red, White, Yellow, etc or 32bit, or 8bit numbers (R, G, B).    
  display1.print("Hola");       // It prints the value.
}

void loop()
{
  display1.setBrightness(255);  // 255 Max
  delay(1000);
  display1.setBrightness(1);    // 1 min
  delay(1000);
}