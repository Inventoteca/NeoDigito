/* NeoDigito ejemplo de cÃ³digo: neodigito_adc

    Se manipula el color del display con un potenci�metro, empezando por rojo 
    y atravsenando el verde y azul hasta terminar nuevamente en el rojo. Adem�s
    muestra el valor del color en hexadecimal.

    Creado por David Figueroa
    Potenciado por Inventoteca y Xircuitos, Junio 11, 2021.
    basado en la libreria de Seven_Segment_Pixel, de Peter Hartmann.

    

    https://github.com/Inventoteca/NeoDigito

    This example code is in the public domain.
    Recuerda que debes tener instalada la librerÃ­a de Adafruit_NeoPixel

*/

#include <NeoDigito.h>

// Pin donde estarÃ¡ conectado el display
#define PIN 12

// Neodigitos conectados
#define DIGITS 6

// Neopixels por segmento
#define PIXPERSEG 2

// Una vez especificado el nÃºmero de displays,
// asÃ­ como el nÃºmero de neopixels por segmento.
// adicionalmente se agregan algunos argumentos de 
// la tira de neopixes usado

NeoDigito display1 = NeoDigito(DIGITS, PIXPERSEG, PIN, NEO_GRB + NEO_KHZ800);

uint32_t rgb = 0xFFFFFF;
uint32_t R;
uint32_t B;
uint32_t G;
uint8_t wheel = 0;
int pot = A0;
int adc;
String text1, text2, text3;
int posZ;

void setup() 
{
  Serial.begin(9600);
  display1.begin(); // Esta funciÃ³n llama Adafruit_NeoPixel.begin() para configurar;
}

void loop() 
{
  adc = analogRead(pot);
  wheel = map(adc,0,1023,255,0);

  if(wheel < 85)
  {
    R = 255 - 3*wheel;
    G = 0;
    B = 3*wheel;
    posZ = 3;
  }
  else if(wheel < 170)
  {
    wheel -= 85;
    R = 0;
    G = 3*wheel;
    B = 255 - 3*wheel;
    posZ = 1;
  }
  else if(wheel < 255)
  {
    wheel -= 170;
    R = 3*wheel;
    G = 255 - 3*wheel;
    B = 0;
    posZ = 5;
  }

  rgb = R << 16 | G << 8 | B;

  text1 = String(R, HEX);
  text2 = String(G, HEX);
  text3 = String(B, HEX);
  
  display1.setPixelColor(rgb);
  display1.print(text1);
  display1.print(text2,2);
  display1.print(text3,4);
  display1.print(0,posZ);
  display1.show();
  delay(100);
}
