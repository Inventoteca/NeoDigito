/* NeoDigito example code: counter

	Counts from 0 to 9999. Red is the default color.

	Created and empowered by Inventoteca & Xircuitos.
	Puebla, Pue. June 11, 2021.

    https://github.com/Inventoteca/NeoDigito

    This example code is in the public domain.
    Remember that you must have installed Adafruit_NeoPixel library.
*/

#include <NeoDigito.h>

// Pin where the display will be attached
#define PIN 12

// NeoDigitos number connected
#define DIGITS 4

// NeoPixel per segment
#define PIXPERSEG 2

// Once you have specified the number of displays
// and the number of neopixels per segment, some
// arguments of the neopixel strip used must be
// added.

NeoDigito display1 = NeoDigito(DIGITS, PIXPERSEG, PIN, NEO_GRB + NEO_KHZ800);

int delayval = 2;	// count delay

int increment = 1; 	// increment

int count = 0;     	// counter

void setup()
{
	display1.begin();
		// This fuction calls Adafruit_NeoPixel.begin() to configure.
	 
	display1.setPixelColor(0x090000);
		// This function set a default color for the whole strip. It can be specified by
		// a 32bit hexadecimal number or three 8bit hexadecimal numbers that represents
		// red, green and blue separately.
}

void loop()
{
	display1.print(count);	// It prints the value
	display1.show();		// Lights up the pixels.
	delay(delayval);
	count = count + increment;

	if (count >= 9999)
	{
	display1.clear();
	display1.show();
	count = 0;
	}
}
