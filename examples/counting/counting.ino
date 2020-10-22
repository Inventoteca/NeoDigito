/* NeoDigito library example code: counting

    Counts from 0 up the null character and back down using random colors on
    a whole display.

    Created by Inventoteca and Xircuitos, October 21, 2020.
    Released under GPLv3, based on Seven_Segment_Pixel, by Peter Hartmann.

    https://github.com/Inventoteca/NeoDigito

    This example code is in the public domain.

*/

#include <Adafruit_NeoPixel.h>
#include <NeoDigito.h>

// Which pin on the Arduino is connected the NeoPixel display connected to?
#define PIN 6

// How many digits are in the display?
#define DIGITS 6

// How may pixels per segement are there?
#define PIXPERSEG 2


// When we instatiate a display object we supply the number of digits in the
// custom built display, as well as the number of pixels per segment.
// Additionally we pass the ususal Adafruit_NeoPixel arguments for object
// instatiation.

NeoDigito display1 = NeoDigito(DIGITS, PIXPERSEG, PIN, NEO_GRB + NEO_KHZ800);

int delayval = 500; // delay for half a second

int increment = 1;

int count = 0;

void setup() {
  display1.begin(); // This function calls Adafruit_NeoPixel begin();
}

void loop() {
  for (int x = 1; x <= DIGITS; x++) {
    display1.print(x, count, random(0, 255), random(0, 255), random(0, 255));
  }

  count = count + increment;

  if (count == 0 || count == 16) {
    increment = -increment;
  }

  delay(delayval);
}
