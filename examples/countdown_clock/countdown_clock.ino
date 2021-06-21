/* NeoDigito example code: countdown_clock

    Example code to show the delimeter feature. This sketch displays a 3 minute
    countdown clock on a display with 3 digits and one colon which flashes when the
    seconds change.

    Created by Inventoteca and Xircuitos, October 21, 2020.
    Released under GPLv3, based on Seven_Segment_Pixel, by Peter Hartmann.

    https://github.com/Inventoteca/NeoDigito

    This example code is in the public domain.

*/


#include <NeoDigito.h>

// Which pin on the Arduino is connected the NeoPixel display connected to?
#define PIN 12

// How many digits are in the display?
#define DIGITS 4

// How may pixels per segement are there?
#define PIXPERSEG 2

// When we instatiate a display object we supply the number of digits in the
// custom built display, as well as the number of pixels per segment.
// Additionally we pass the ususal Adafruit_NeoPixel arguments for object
// instatiation.

NeoDigito display1 =  NeoDigito(DIGITS, PIXPERSEG, PIN, NEO_RGB + NEO_KHZ800);

#define   tiempo    600
int count = tiempo; // 3 minutes in seconds

void setup() 
{
  display1.begin(); // This function calls Adafruit_NeoPixel begin();
  display1.setPixelColor(0x090000);
}

void loop() {

  int minutes = count / 60;
  int seconds =  count - (minutes * 60) ; // Seconds ones place

  display1.print(minutes,0);
  display1.print(seconds,2);
  
  // Flash colon when seconds change
  if (!(seconds % 2)) {
    //  even
    display1.updateDelimiter(2, 0, 0, 0);
  } else {
    //  odd
    display1.updateDelimiter(2, 0, 25, 0);
  }

  display1.show();

  delay(1000);
  count--;
  if (count == 0) {
    count = tiempo;
  }
}