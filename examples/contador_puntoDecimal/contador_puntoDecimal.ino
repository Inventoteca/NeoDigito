/* NeoDigito ejemplo de código: contador

    Cuenta de 0 a 9.99 y luego hace una cuentra regresiva
    el color por defecto es violeta.

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

NeoDigito display1 = NeoDigito(DIGITS, PIXPERSEG, PIN, NEO_GRB + NEO_KHZ800);
int delayval = 20; // retardo para el conteo
float increment = 0.01;  // valor a incrementar
float count = 0.00;      // Variable para almacenar el conteo

void setup()
{
  display1.begin(); // Esta función llama Adafruit_NeoPixel.begin() para configurar;

  // Esta función puede controlar un solo led o toda la tira
  // si se especifica el número del led: display1.setPixelColor(0,0xff00ff);
  // y para toda la tira no se especifica el numero del display solo el color en 32 bits
  display1.setPixelColor(0x090009);
}

void loop()
{
  // se escribe el digito y el valor a escribir
  display1.print(count);
  
  
  count = count + increment;
  
  if (count < 0 || count > 9.99)
  {
    increment = -increment;
  }
  
  display1.show();
  delay(delayval);
}
