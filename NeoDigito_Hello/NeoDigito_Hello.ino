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

// Once you have specified the number of displays and the number of neopixels per segment, 
// some arguments of the neopixel strip used must be added. NeoDigito() also admits the number of
// delimiters and the number of pixels per delimiter. 
// For more info abaut the last argumets check Adafruit Neopixel documentation.

NeoDigito display1 = NeoDigito(DIGITS, PIXPERSEG, PIN, NEO_GRB + NEO_KHZ800);


void setup()
{
  display1.begin();  // This fuction calls Adafruit_NeoPixel.begin() to configure. 

  // Color can be specified by a 32bit hexadecimal, three 8bit numbers (red, green, blue). 
  // Even you can use some colors names, red, white, yellow.
  display1.setPixelColor(cian);

  display1.print("HELLO");  // It prints the value.
  display1.show();          // Lights up the pixels.
  
    
}

void loop()
{
  
}
