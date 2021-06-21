/* NeoDigito ejemplo de código: neodigito_adc

    Cuenta de 0 a 9999 y luego hace una cuentra regresiva
    el color por defecto es rojo.

    Creado por David Figueroa
    Potenciado por Inventoteca y Xircuitos, Junio 11, 2021.
    basado en la libreria de Seven_Segment_Pixel, de Peter Hartmann.

    

    https://github.com/Inventoteca/NeoDigito

    This example code is in the public domain.
    Recuerda que debes tener instalada la librería de Adafruit_NeoPixel

*/

#include <NeoDigito.h>

// Pin donde estará conectado el display
#define PIN 12

// Neodigitos conectados
#define DIGITS 4

// Neopixels por segmento
#define PIXPERSEG 2


// Una vez especificado el número de displays,
// así como el número de neopixels por segmento.
// adicionalmente se agregan algunos argumentos de 
// la tira de neopixes usado

NeoDigito display1 = NeoDigito(DIGITS, PIXPERSEG, PIN, NEO_RGB + NEO_KHZ800);



void setup() 
{
  display1.begin(); // Esta función llama Adafruit_NeoPixel.begin() para configurar;

}

void loop() 
{
  int adc = analogRead(A0);

  if(adc > 512)
  {
    // Esta función puede controlar un solo led o toda la tira
    // si se especifica el número del led: display1.setPixelColor(0,0xff00ff);
    // y para toda la tira no se especifica el numero del display solo el color en 32 bits
    display1.setPixelColor(0x090000);  // Rojo
  }

  else
    display1.setPixelColor(0x900); // Verde

  display1.print(adc);
  display1.show();
  delay(100);

}
