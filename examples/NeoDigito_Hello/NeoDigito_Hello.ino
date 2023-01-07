/* NeoDigito example code: Hello

  Print "Hello" on display, color select

  Created by Inventoteca 

  https://github.com/Inventoteca/NeoDigito

  This example code is in the public domain.
  Remember that you must have installed Adafruit_NeoPixel library.
*/

#include <NeoDigito.h>

#define PIN 12        // Pin where the display will be attached
#define DIGITS 4      // Number of NeoDigitos connected
#define PIXPERSEG 3   // NeoPixels per segment

// Specified the number of displays and the number of neopixels per segment, some arguments of the neopixel strip used must be added. 
NeoDigito display1 = NeoDigito(DIGITS, PIXPERSEG, PIN, NEO_GRB + NEO_KHZ800); // For more info abaut the last argumets check Adafruit_Neopixel documentation.


void setup()
{
  display1.begin();             // This fuction calls Adafruit_NeoPixel.begin() to configure. 
  display1.setColor(cian); // Color specified by a 32bit hex, or 8bit numbers (red, green, blue), Also colors names, red, white, yellow, etc.    
  display1.print("HELLO");      // It prints the value.
  display1.show();              // Lights up the pixels.
  
    
}

void loop()
{
  
}
