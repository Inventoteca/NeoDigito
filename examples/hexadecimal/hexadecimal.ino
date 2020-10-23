/* NeoDigito library example code: hexadecimal

    Show hexadecimal characters using extra data
    in random colors.

    Created by David Figueroa
    Powered by Inventoteca and Xircuitos, October 21, 2020.
    Released under GPLv3, based on Seven_Segment_Pixel, by Peter Hartmann.

    https://github.com/Inventoteca/NeoDigito

    This example code is in the public domain.

*/

#include <Adafruit_NeoPixel.h>
#include <NeoDigito.h>

// Which pin on the Arduino is connected the NeoPixel display connected to?
#define PIN 6

// How many digits are in the display?
#define DIGITS 14

// How may pixels per segement are there?
#define PIXPERSEG 2


// We supply the number of digits in the display,
// as well as the number of pixels per segment.
// Additionally we pass the ususal Adafruit_NeoPixel arguments for object
// instatiation.

NeoDigito display1 = NeoDigito(DIGITS, PIXPERSEG, PIN, NEO_GRB + NEO_KHZ800);

int delayval = 500; // delay for half a second

int increment = 1;

int count = 0;

void setup()
{
  display1.begin(); // This function calls Adafruit_NeoPixel begin();

  // This function can control individual pixel color
  //display1.setPixelColor(0,0xff00ff);
  //or all the strip, 32-bit color value. Most significant byte is white (for RGBW pixels) or ignored (for RGB pixels)
  display1.setPixelColor(0xffff00);


}

void loop()
{
  for (int x = 0; x <= DIGITS; x++)
  {
    // x number of the display
    // count the number to show
    //display1.write(x, count);
    display1.write(x, count, random(0,0xffffff)); // Also you can set the 32-bit color value

  }

  count = count + increment;

  if (count == 0 || count == 15)
  {
    increment = -increment;
  }

  display1.show();
  delay(delayval);
}
