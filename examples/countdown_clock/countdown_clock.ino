/* NeoDigito example code: countdown_clock

    Example code to show the delimeter feature. This sketch displays a 3 minute
    countdown clock on a display with 3 digits and one colon which flashes when the
    seconds change.

    Created and empowered by Inventoteca & Xircuitos.
	Puebla, Pue. June 11, 2021.

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

// Once you have specified the number of displays
// and the number of neopixels per segment, some
// arguments of the neopixel strip used must
// be added.

NeoDigito display1 =  NeoDigito(DIGITS, PIXPERSEG, PIN, NEO_RGB + NEO_KHZ800);

#define   tiempo    600
int count = tiempo; // 3 minutes in seconds

void setup() 
{
    display1.begin();
        // This function calls Adafruit_NeoPixel begin();

    display1.setPixelColor(0x090000);
        // This function set a default color for the whole strip. It can be specified by
        // a 32bit hexadecimal number or three 8bit hexadecimal numbers that represents
        // red, green and blue separately.
}

void loop() {

  uint8_t minutes = count / 60;
  uint8_t seconds =  count - (minutes * 60) ; // Seconds ones place


  if(minutes < 10)
  {
   display1.write(' ',0); //null
   display1.print(minutes,1);
   
   
  } 
  else
  {
    display1.print(minutes,0);
  }
   

  if(seconds < 10)
  {
    display1.print(0,2); 
    display1.print(seconds,3);
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

  display1.show();

  delay(1000);
  count--;
  if (count == 0) {
    count = tiempo;
  }
}
