/* NeoDigito example code: volmeter

    Read ADC 0

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

float input_voltage = 0.0; 

void setup()
{
    for (int disp_num = 0; disp_num < DIGITS; disp_num++)
    {
      display1.updateColor(RANDOM); //Before for all display
      display1.setCursor(disp_num);
      display1.print(disp_num);      // It prints the value.
      display1.show();              // Lights up the pixels.
      delay(300);
    }

    delay(1000);
    display1.clear();
    display1.print("V:",Yellow);
}

void loop()
{
    int analog_value = analogRead(A0);
    input_voltage = (analog_value * 3.3) / 4095.0;  // ESP 32 ADC: 0-4095 and V = 3.3V
    //input_voltage = (analog_value * 3.3) / 4095.0;  // Arduino ADC: 0-1023 and V = 5.0V
    display1.setCursor(1);
    display1.print(String(input_voltage, 2),Blue);  // It prints the value.
    display1.show();
    delay(100);
}