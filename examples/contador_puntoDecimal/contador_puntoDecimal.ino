/* NeoDigito example code: decimalCounter

    Counts from 0 to 9.99, then it counts down. The default color is purple

    Created and empowered by Inventoteca & Xircuitos.
	Puebla, Pue. June 11, 2021.

    https://github.com/Inventoteca/NeoDigito

    This example code is in the public domain.
    Remember that you must have installed Adafruit_NeoPixel library.
*/

#include <NeoDigito.h>

// Pin where the display will be attached
#define PIN 12

// Number of NeoDigitos connected
#define DIGITS 4

// NeoPixel per segment
#define PIXPERSEG 2

// Once you have specified the number of displays
// and the number of neopixels per segment, some
// arguments of the neopixel strip used must be
// added. NeoDigito() also admits the number of
// delimiters and the number of pixels per delimiter.

NeoDigito display1 = NeoDigito(DIGITS, PIXPERSEG, PIN, NEO_GRB + NEO_KHZ800);
int delayval = 20;      // counter delay
float increment = 0.01; // increment
float count = 0.00;     // counter

void setup()
{
    display1.begin();
        // This fuction calls Adafruit_NeoPixel.begin() to configure.

    display1.setPixelColor(0x090009);
        // This function sets a default color for the whole strip. It can be specified by
        // a 32bit hexadecimal number or three 8bit hexadecimal numbers that represents
        // red, green and blue separately.
}

void loop()
{
    display1.print(count);  // It prints the value.
    display1.show();        // Lights up the pixels.
    delay(delayval);
  
    count = count + increment;
  
    if (count < 0.01 || count > 9.99)
    {
        increment = -increment;
        display1.clear();   // It erase the value.
        display1.show();    // Lights off the pixels.
    }
}