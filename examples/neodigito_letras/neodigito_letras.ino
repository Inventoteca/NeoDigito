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

char letra =' '; // Letra inicial

void setup() 
{
  display1.begin(); // This function calls Adafruit_NeoPixel begin();
  display1.setPixelColor(0x090000);
}

void loop() 
{
  display1.setPixelColor(0x090000);
  display1.print(letra); // imprime en decimal
  display1.setPixelColor(0x0900);
  display1.print(letra,2); // imprime la letra
  display1.show();
  letra++;

  if(letra >= 91)
  {
    letra = ' ';
  }
  
  delay(500);
}