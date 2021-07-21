/* NeoDigito example code: neodigito_letras

    Example code to show the characters from the ASCII table. The code prints
	the number associated with the ASCII table's character in the  firsts
	positions, and the character itself in the subsecuents positions of the
	strip.  

    Created and empowered by Inventoteca and Xircuitos.
    Puebla, Pue. October 21, 2020.

    https://github.com/Inventoteca/NeoDigito

    This example code is in the public domain.
	Remember that you must have installed Adafruit_NeoPixel library.
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

char letra =' '; // Initial character
String texto1 ="Hola";
int pos = 2;

void setup() 
{
  display1.begin();
	// This function calls Adafruit_NeoPixel begin();

  display1.setPixelColor(0x090009);
  display1.print(texto1);	// Prints a full word
  display1.show();			// Lights up the pixels
  delay(1000);
  display1.clear();			// Clear the display
  display1.show();			// Lights off the pixels
}

void loop() 
{
	while(letra < 127)
	{
		if(letra < 100)
			pos = 2;
		
		if(letra >= 100)
			pos = 3;
		
		display1.setPixelColor(0x090000);	// Sets the color for the first text
		display1.print(letra);				// Prints the ASCII number
		display1.setPixelColor(0x0900);		// Sets the color for the next text
		display1.write(letra,pos);			// Prints de character.
		display1.show();					// Lights up the pixels.
		letra++;
		delay(500);
	}
	
	letra = ' ';
	display1.clear();	// Erase the text.
	display1.show();	// Lights off the pixels.
}