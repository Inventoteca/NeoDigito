/* NeoDigito ejemplo de codigo: neodigito_adc

    Muestra el valor en hexadecimal del color con el que se configura el
    display. Los valores del Rojo, Verde y Azul, son manipulados con tres
  potenciómetros.

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
#define DIGITS 4

// Neopixels por segmento
#define PIXPERSEG 2


// Una vez especificado el numero de displays,
// asi como el numero de neopixels por segmento.
// adicionalmente se agregan algunos argumentos de 
// la tira de neopixes usado

NeoDigito display1 = NeoDigito(DIGITS, PIXPERSEG, PIN, NEO_RGB + NEO_KHZ800);

uint32_t rgb = 0xFFFFFF;
uint32_t R, G, B;
int adcR = 0, potR = A0;
int adcG = 0, potG = A1;
int adcB = 0, potB = A2;
String text;

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

  /*
  Serial.print("Rojo: ");
  Serial.print(R, HEX);
  Serial.print("\t Verde: ");
  Serial.print(G, HEX);
  Serial.print("\t Azul: ");
  Serial.print(B, HEX);
  */

  rgb = R << 16 | G << 8 | B;
  display1.setPixelColor(rgb);

  text = String(rgb,HEX);
  Serial.print("Color: ");
  Serial.println(text);
  
  display1.print(text);
  display1.show();
  delay(300);

}
