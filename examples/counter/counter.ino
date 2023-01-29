/* NeoDigito example code: counter

	Counts from 0 to 9999. CIAN is the default color.

	Created and empowered by Inventoteca & Xircuitos.
	Puebla, Pue. June 11, 2021.

    https://github.com/Inventoteca/NeoDigito

    This example code is in the public domain.
    Remember that you must have installed Adafruit_NeoPixel library.
*/

#include <NeoDigito.h>

#define PIN         2   // Pin where the display will be attached
#define DIGITS      4   // Number of NeoDigitos connected
#define PIXPERSEG   3   // NeoPixels per segment, BIG version

// Specified the number of displays and the number of neopixels per segment, for more info about the argumets check documentation 
NeoDigito display1 = NeoDigito(DIGITS, PIXPERSEG, PIN); 

int count = 0;     				// counter

void setup()
{
	display1.begin(); 			  // This fuction calls Adafruit_NeoPixel.begin() to configure.     
  	display1.print("ABCD");       // It prints the value.
  	display1.updateColor(Rainbow);// Color specified by name RED, WHITE, YELLOW, etc or 32bit, or 8bit numbers (R, G, B).
	display1.show();              // Lights up the pixels.
	delay(1000);
	display1.clear();			  // It erase the text in the whole display.
	display1.show();
	display1.setColor(Random);
}

void loop()
{
	if (count < 10)
   		display1.print(" ");    // It prints the value.
  	if (count < 100)
    	display1.print(" ");    // It prints the value.
  	if (count < 1000)
    	display1.print(" ");    // It prints the value.

	display1.print(count);		// It prints the value.
	display1.show();			// Lights up the pixels.
	delay(1);

	if (count >= 9999)			// Reset
	{
		delay(1000);
		display1.updateColor(Random);
		display1.show();		// Lights off the pixels.
		delay(1000);
		display1.clear();		// It erase the text in the whole display.
		display1.show();		// Lights off the pixels.
		count = 0;
	}
	count++;
}
