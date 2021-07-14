/* NeoDigito example code: neodigito_letras

    Example code to show the characters from the ASCII table. The code prints
	the number associated with the ASCII table's character in the  firsts
	positions, and the character itself in the subsecuents positions of the
	strip.  

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
String texto1 ="Hola";
String texto2 ="Ejem";
int pos = 2;

void setup() 
{
  display1.begin(); // This function calls Adafruit_NeoPixel begin();
  display1.setPixelColor(0x090000);

  display1.setPixelColor(0x090009);
  display1.print(texto1);
  display1.show();
  delay(1000);
  display1.setPixelColor(0x000909);
  display1.print(texto2);
  display1.show();
  delay(1000);
  display1.clear();
  display1.show();
  delay(1000);
}

void loop() 
{
	while(letra < 127)
	{
		if(letra < 100)
			pos = 2;
		
		if(letra >= 100)
			pos = 3;
		
		display1.setPixelColor(0x090000);
		display1.print(letra); // imprime en decimal
		display1.setPixelColor(0x0900);
		display1.write(letra,pos); // imprime la letra
		display1.show();
		letra++;
		delay(500);
	}
	
	letra = ' ';
  display1.clear();
}
