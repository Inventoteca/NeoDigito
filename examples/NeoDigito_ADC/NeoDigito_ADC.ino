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
uint8_t color;
int pot = A0;
int adc;

void setup() 
{
  Serial.begin(9600);
  display1.begin(); // Esta funciÃ³n llama Adafruit_NeoPixel.begin() para configurar;
}

void loop() 
{
  adc = analogRead(pot);
  color = map(adc,0,1023,0,255);

  B = 0;
  R = 255 - color;
  G = color;

  rgb = R << 16 | G << 8 | B;

  display1.setPixelColor(rgb);
  
  display1.clear();
  display1.show();

  display1.print(adc);
  display1.show();
  delay(300);
}
