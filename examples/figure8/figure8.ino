/* NeoDigito library example code: figure8

    Outlines a figure 8 using individual segments of a seven segment display
    in random colors.

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
// custom built display,as well as the number of pixels per segment.
// Additionally we pass the ususal Adafruit_NeoPixel arguments for object
// instatiation.

NeoDigito display1 =  NeoDigito(DIGITS, PIXPERSEG, PIN, NEO_GRB + NEO_KHZ800);

int delayval = 300;

int count = 0;

void setup() {
  display1.begin(); // This function calls Adafruit_NeoPixel begin();
}

int figure8[] = {17, 16, 11, 12, 17, 15, 14, 13};

void loop() {
  for (int x = 1; x <= DIGITS; x++) {
    display1.updateDigit(x, figure8[count], random(0, 255), random(0, 255),
                         random(0, 255));
  }
  count++;
  display1.show();
  if (count == 8) {
    count = 0;
  }
  display1.show();

  delay(delayval);
}
