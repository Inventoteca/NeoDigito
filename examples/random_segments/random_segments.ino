/* NeoDigito library example code: random_segments

Displays random segments in random colors on a whole display.

Created by Inventoteca and Xircuitos, October 21, 2020.
Released under GPLv3, based on Seven_Segment_Pixel, by Peter Hartmann.

https://github.com/Inventoteca/NeoDigito

This example code is in the public domain.

*/

#include <Adafruit_NeoPixel.h>
#include <NeoDigito.h>

// Which pin on the Arduino is connected the NeoPixel display connected to?
#define PIN 6

// How many NeoPixels are in the seven segment display total?
#define NUMPIXELS 126

// How many digits are in the display?
#define DIGITS 6

// How may pixels per segement are there?
#define PIXPERSEG 3

// How many delimeters are in the display?
#define NUMDELIMS 1

// How may pixels per delimeter are there?
#define PIXPERDELIM 1

// When we instatiate a display object we supply the number of digits in the
// custom built display as well as the number of pixels per segment. Additionally we pass the ususal
// Adafruit_NeoPixel arguments for object instatiation.

NeoDigito display1 =
    NeoDigito(DIGITS, PIXPERSEG, NUMDELIMS, PIXPERDELIM, NUMPIXELS,
                        PIN, NEO_GRB + NEO_KHZ800);

int delayval = 90; // delay for half a second

void setup() {
  display1.begin(); // This function calls Adafruit_NeoPixel begin();
}

void loop() {
  for (int x = 1; x <= DIGITS; x++) {
    display1.updateDigit(x, random(11, 18), random(0, 255), random(0, 255),
                         random(0, 255));
  }
  display1.show();

  delay(delayval);
}
