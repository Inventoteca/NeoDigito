/* NeoDigito example code: neodigito_3pots

    Shows the hexadecimal value that represents the colour with which the
    the display is configured. Three potenciometers are attached to control
    the saturation of red, green and blue.

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
#define DIGITS 6

// NeoPixel per segment
#define PIXPERSEG 2

// Once you have specified the number of displays
// and the number of neopixels per segment, some
// arguments of the neopixel strip used must be
// added.

NeoDigito display1 = NeoDigito(DIGITS, PIXPERSEG, PIN, NEO_GRB + NEO_KHZ800);

// uint32_t rgb = 0xFFFFFF;
uint32_t R, G, B;
int adcR = 0, potR = A0;
int adcG = 0, potG = A1;
int adcB = 0, potB = A2;
String text1, text2, text3;
int posR, posG, posB;

void setup() 
{
  Serial.begin(9600);
  display1.begin();
    // This fuction calls Adafruit_NeoPixel.begin() to configure.
}

void loop() 
{
  adcR = analogRead(potR);
  adcG = analogRead(potG);
  adcB = analogRead(potB);
  R = map(adcR,0,1023,0,255);
  G = map(adcG,0,1023,0,255);
  B = map(adcB,0,1023,0,255);

  // rgb = R << 16 | G << 8 | B;
  display1.setPixelColor(R,G,B);

  text1 = String(R,HEX);
  text2 = String(G,HEX);
  text3 = String(B,HEX);
  
  Serial.print("Color:\t");
  Serial.print(text1);
  Serial.print("\t");
  Serial.print(text2);
  Serial.print("\t");
  Serial.println(text3);

  if(R <= 9)
  {
    display1.print(0);
    display1.show();
    posR = 1;
  }
  else
    posR = 0;
  
  if(G <= 9)
  {
    display1.print(0,2);
    display1.show();
    posG = 3;
  }
  else
    posG = 2;
  
  if(B <= 9)
  {
    display1.print(0,4);
    display1.show();
    posB = 5;
  }
  else
    posB = 4;

  display1.print(text1,posR);   // Prints the hexadecimal value of Red
  display1.print(text2,posG);   // Prints the hexadecimal value of Green
  display1.print(text3,posB);   // Prints the hexadecimal value of Blue
  display1.show();

  delay(300);
}
