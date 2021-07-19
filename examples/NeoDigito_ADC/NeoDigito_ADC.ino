/* NeoDigito example code: neodigito_adc
    
    It controls the display color with a single potenciometer. The colour transition
    is from red to green. In addition, it shows the adc value where the pot is
    attached.

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

uint32_t rgb = 0xFFFFFF;
// uint32_t R;
// uint32_t B;
// uint32_t G;
uint8_t color;
int pot = A0;
int adc;

void setup() 
{
  Serial.begin(9600);
  display1.begin();
    // This fuction calls Adafruit_NeoPixel.begin() to configure.
}

void loop() 
{
  adc = analogRead(pot);
  color = map(adc,0,1023,0,255);

  R = 255 - color;
  G = color;
  B = 0;

  // rgb = R << 16 | G << 8 | B;
  display1.setPixelColor(R,G,B);
  
  display1.clear();
  display1.show();

  display1.print(adc);
  display1.show();
  delay(300);
}
