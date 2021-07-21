/* NeoDigito example code: countdown_clock

    Example code to show the delimeter feature. This sketch displays a 10 minutes
    countdown clock on a display with 4 digits and one colon which flashes when the
    seconds change.

    Created and empowered by Inventoteca & Xircuitos.
	Puebla, Pue. June 11, 2021.

    https://github.com/Inventoteca/NeoDigito

    This example code is in the public domain.

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

NeoDigito display1 =  NeoDigito(DIGITS, PIXPERSEG, PIN, NEO_RGB + NEO_KHZ800);

#define   tiempo    600
int count = tiempo; // 10 minutes in seconds

void setup() 
{
    display1.begin();
        // This function calls Adafruit_NeoPixel begin();

    display1.setPixelColor(0x090000);
        // This function sets a default color for the whole strip. It can be specified by
        // a 32bit hexadecimal number or three 8bit hexadecimal numbers that represents
        // red, green and blue separately.
}

void loop() {

  uint8_t minutes = count / 60;
  uint8_t seconds =  count - (minutes * 60) ; // Seconds ones place


  if(minutes < 10)
  {
   display1.write(' ',0);       // It prints a blank space
   display1.print(minutes,1);   // It prints the minutes. 
  } 
  else
    display1.print(minutes,0);

  if(seconds < 10)
  {
    display1.print(0,2);        // It prints a zero in the seconds first position
    display1.print(seconds,3);  // It prints the seconds
  }

  else
    display1.print(seconds,2);
  
  // Flash colon when seconds change
  if (!(seconds % 2)) {
    //  even
    display1.updateDelimiter(2, 0, 0, 0);
  } else {
    //  odd
    display1.updateDelimiter(2, 0, 25, 0);
  }

  display1.show();      // Lights up the pixels.

  delay(1000);
  count--;
  if (count == 0) {
    count = tiempo;
  }
}
