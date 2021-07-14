/* NeoDigito ejemplo de codigo: neodigito_adc

    Muestra el valor en hexadecimal del color con el que se configura el
    display. Los valores del Rojo, Verde y Azul, son manipulados con tres
  	potenci�metros.

    Creado por David Figueroa
    Potenciado por Inventoteca y Xircuitos, Junio 11, 2021.
    basado en la libreria de Seven_Segment_Pixel, de Peter Hartmann.

    https://github.com/Inventoteca/NeoDigito

    This example code is in the public domain.
    Recuerda que debes tener instalada la libreria de Adafruit_NeoPixel

*/

#include <NeoDigito.h>

// Pin donde estara conectado el display
#define PIN 12

// Neodigitos conectados
#define DIGITS 6

// Neopixels por segmento
#define PIXPERSEG 2


// Una vez especificado el numero de displays,
// asi como el numero de neopixels por segmento.
// adicionalmente se agregan algunos argumentos de 
// la tira de neopixes usado

NeoDigito display1 = NeoDigito(DIGITS, PIXPERSEG, PIN, NEO_GRB + NEO_KHZ800);

uint32_t rgb = 0xFFFFFF;
uint32_t R, G, B;
int adcR = 0, potR = A0;
int adcG = 0, potG = A1;
int adcB = 0, potB = A2;
String text1, text2, text3;
int posR, posG, posB;

void setup() 
{
  Serial.begin(9600);
  display1.begin(); // Esta funcion llama Adafruit_NeoPixel.begin() para configurar
}

void loop() 
{
  adcR = analogRead(potR);
  adcG = analogRead(potG);
  adcB = analogRead(potB);
  R = map(adcR,0,1023,0,255);
  G = map(adcG,0,1023,0,255);
  B = map(adcB,0,1023,0,255);

  rgb = R << 16 | G << 8 | B;
  display1.setPixelColor(rgb);

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
    posR = 1;
  }
  else
    posR = 0;
  
  if(G <= 9)
  {
    display1.print(0,2);
    posG = 3;
  }
  else
    posG = 2;
  
  if(B <= 9)
  {
    display1.print(0,4);
    posB = 5;
  }
  else
    posB = 4;

  display1.print(text1,posR);
  display1.print(text2,posG);
  display1.print(text3,posB);
  display1.show();

  delay(300);
}
