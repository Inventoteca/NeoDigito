/*
NeoDigito:
  
  Display de 7 Segmentos basado en neopixels
  
  
  Large custom made 7 segment neopixel displays.
  Created by Inventoteca and Xircuitos, October 21, 2020.
  Released under GPLv3, based on Seven_Segment_Pixel, by Peter Hartmann.
*/

#include "NeoDigito.h"
#include <../Adafruit_NeoPixel/Adafruit_NeoPixel.h>

// How many NeoPixels are in the seven segment display total?
uint8_t n;
uint16_t numDelimiters = 2;
uint16_t pixPerDelimiter = 1;
uint16_t DisplayNumber;
uint32_t Color = 0xffffff;   // white is default color

//<<constructor>>
NeoDigito::NeoDigito(uint16_t digitsPerDisplay, uint16_t pixelsPerSegment, uint8_t p, uint8_t t)
    : digPerDisp(digitsPerDisplay), pixPerSeg(pixelsPerSegment),
      numDelims(numDelimiters), pixPerDelim(pixPerDelimiter)
  {
    DisplayNumber = digitsPerDisplay;

    n =  (uint8_t(digitsPerDisplay * pixelsPerSegment * 7)) + digitsPerDisplay * (uint8_t( numDelimiters * pixPerDelimiter));
    strip = new Adafruit_NeoPixel(n, p, t);
  }
//<<destructor>>
NeoDigito::~NeoDigito() {}

//--------------------------------------------------------- begin
void NeoDigito::begin()
{
  strip->begin();
}

//--------------------------------------------------------- show
void NeoDigito::show() { strip->show(); }

// -------------------------------------------------------- setPixelColor(n,c)
void NeoDigito::setPixelColor(uint16_t n, uint32_t c)
{
    strip->setPixelColor(n, c);
    Color = c;
}

// -------------------------------------------------------- setPixelColor(c)
void NeoDigito::setPixelColor(uint32_t c)
{
    Color = c;
    //strip->setPixelColor(n, c);
}

//--------------------------------------------------------- updateDigit
/*
void NeoDigito::updateDigit(uint16_t position, uint16_t digit, uint8_t RED, uint8_t GREEN, uint8_t BLUE)
{

  bitmask = characterMap[digit];

  int charPos = 0;
  // expand bitbask to number of pixels per segment in the proper position
  for (int x = (position) * 7; x <= (position - 1) * 7 + 6; x++)
  //for (int x = 0; x <= 6; x++)
  {

    if (bitmask.charAt(charPos) == '1')
    {
      // Lighting up this segment
      for (int pix = 1; pix <= pixPerSeg; pix++)
      {
        strip->setPixelColor((x * pixPerSeg + pix),strip->Color(RED, GREEN, BLUE));
      }

    }
    else
    {
      // Turning off this up this segment.
      for (int pix = 1; pix <= pixPerSeg; pix++)
      {
        strip->setPixelColor((x * pixPerSeg + pix), 0);
      }
    }
    charPos++;
  }
}
*/

//----------------------------------------------------------------------------------updateDelimiter
void NeoDigito::updateDelimiter(uint16_t delimeter, uint8_t RED, uint8_t GREEN, uint8_t BLUE)
{

  int digitsOffset = (delimeter * pixPerDelim * numDelimiters) + (delimeter * pixPerSeg * 7);

  for (int pix = digitsOffset ; (pix > digitsOffset - (pixPerDelim * numDelimiters)) || (pix == 0); pix--) 
  {
    strip->setPixelColor(pix, strip->Color(RED, GREEN, BLUE));
  }
}


//----------------------------------------------------------------------------------updateDelimiter
void NeoDigito::updateDelimiter(uint16_t delimeter)
{

  int digitsOffset = (delimeter * pixPerDelim * numDelimiters) + (delimeter * pixPerSeg * 7);

  for (int pix = digitsOffset ; (pix > digitsOffset - (pixPerDelim * numDelimiters)) || (pix == 0); pix--) 
  {
    strip->setPixelColor(pix, Color);
  }
}


//----------------------------------------------------------------------------------updatePoint
void NeoDigito::updatePoint(uint16_t delimeter)
{

  int digitsOffset = (delimeter * pixPerDelim * numDelimiters) + (delimeter * pixPerSeg * 7) - 1;

  //for (int pix = digitsOffset ; (pix > digitsOffset - (pixPerDelim)); pix--) 
  //{
    strip->setPixelColor(digitsOffset, Color);
  //}
}

//----------------------------------------------------------------------------------updateTilde
void NeoDigito::updateTilde(uint16_t delimeter)
{

  int digitsOffset = (delimeter * pixPerDelim * numDelimiters) + (delimeter * pixPerSeg * 7);

  //for (int pix = digitsOffset ; (pix > digitsOffset - (pixPerDelim)); pix--) 
  //{
    strip->setPixelColor(digitsOffset, Color);
  //}
}


//----------------------------------------------------------------------------------write
void NeoDigito::write(uint16_t position, uint16_t digit, uint8_t RED, uint8_t GREEN, uint8_t BLUE)
{

  bitmask = characterMap[digit];

  int charPos = 0;
  int delimeter;


  //Omit the delimiters
  delimeter = position * 2 + 1;

  // expand bitbask to number of pixels per segment in the proper position
  for (int x = (position) * 7; x <= (position) * 7 + 6; x++)
  {

    if (bitmask.charAt(charPos) == '1')
    {
      // Lighting up this segment
      for (int pix = 0; pix < pixPerSeg; pix++)
      {
        strip->setPixelColor(((x * pixPerSeg) + pix + delimeter),strip->Color(RED, GREEN, BLUE));
      }

    }
    else
    {
      // Turning off this up this segment.
      for (int pix = 0; pix < pixPerSeg; pix++)
      {
        strip->setPixelColor((x * pixPerSeg + pix + delimeter), 0);
      }
    }
    charPos++;
  }
  strip->show();
}

//----------------------------------------------------------------------------------write (x,num,rgb)
void NeoDigito::write(uint8_t x, uint8_t num, uint32_t rgb)
{
  if (x > DisplayNumber) // Si el número de display es mayor al número de displays disponible, rompe
    return;

  bitmask = characterMap[num]; // Se cargan los caracteres disponibles
  Color = rgb;

  int charPos = 0;
  int delimeter;


  //Omit the delimiters
  delimeter = x * 2 + 1;

  // expand bitbask to number of pixels per segment in the proper position
  for (int i = (x) * 7; i <= (x) * 7 + 6; i++)
  {

    if (bitmask.charAt(charPos) == '1')
    {
      // Lighting up this segment
      for (int pix = 0; pix < pixPerSeg; pix++)
      {
        strip->setPixelColor(((i * pixPerSeg) + pix + delimeter),rgb);
      }

    }
    else
    {
      // Turning off this up this segment.
      for (int pix = 0; pix < pixPerSeg; pix++)
      {
        strip->setPixelColor((i * pixPerSeg + pix + delimeter), 0);
      }
    }
    charPos++;
  }
  //strip->show();
}

//---------------------------------------------------------------------------- write(x,num)
// x ----> Representa el display
// num --> Valor a escribir
void NeoDigito::write(uint8_t x, uint8_t num) 
{
  if (x > DisplayNumber)  // Si el display seleccionado no existe, se regresa
    return;

  bitmask = characterMap[num]; // Cargo los caracteres disponibles 0,1,2,3,4,5,6,7,8,9,A,b,C,d,F,G,º,OFF,

  int charPos = 0;  // aqui selecciono el caracter a escirbir
  int delimeter;    // aqui ajuslo lo delimitadores, uno al inicio y otro al final
  int offset = x*7;


  //Omit the delimiters
  delimeter = (x * 2) + 1;
  //delimeter = (x * 2);

  // expand bitbask to number of pixels per segment in the proper position
  // para escribir a la tira de leds uno por uno
  // primero se revisa a partir de que led iniciar segun la posición del display x
  // se desplaza por cada 7 segmentos
  // iniciando por el led 0 del primer segmento 
  // terminando en el segmento 6
  for(int i = 0; i <= 6; i++)
  {
    offset = (i + (x*7)) * pixPerSeg;

    if (bitmask.charAt(charPos) == '1') // Busco en los caracteres si el segmento se enciende o no
    {
      // Lighting up this segment
      for (int pix = 0; pix < pixPerSeg; pix++) // aquí reviso según la cantidad de neopixels por segmento
      {
        //strip->setPixelColor(((offset * pixPerSeg) + pix + delimeter),Color);
        strip->setPixelColor(((offset) + pix + delimeter),Color);
      }

    }
    else
    {
      // Turning off this up this segment.
      for (int pix = 0; pix < pixPerSeg; pix++)
      {
        //strip->setPixelColor(((offset * pixPerSeg) + pix + delimeter), 0);
        strip->setPixelColor(((offset) + pix + delimeter), 0);
      }
    }
    charPos++;
  }
}


//---------------------------------------------------------------------------- print(int num)
// x ----> Representa el display
// num --> Valor a escribir
void NeoDigito::print(int num)
{
 bitmask = characterMap[num]; // Cargo los caracteres disponibles 0,1,2,3,4,5,6,7,8,9,A,b,C,d,F,G,º,OFF,

  int x = 0;        // display
  int digitos;
  String textNum = "";
  int charPos = 0;  // aqui selecciono el caracter a escirbir
  int delimeter;    // aqui ajuslo lo delimitadores, uno al inicio y otro al final
  int offset = x*7;

  textNum = String(num);
  digitos = textNum.length();

  // cantidad de displays usados para representar el número
   // if (digitos > DisplayNumber)  // Si el display seleccionado no existe, se regresa
   //return;
  
  // Barro según la cantidad de displays disponibles
  for(x = 0; x <= DisplayNumber; x++)
  {
    
    write(x,(textNum[x])-32);
  }
  
}

//---------------------------------------------------------------------------- print(int num, int x)
// x ----> Representa el display o posición a partir de la cual imprimir
// num --> Valor a escribir
void NeoDigito::print(int num, int x)
{
 bitmask = characterMap[num]; // Cargo los caracteres disponibles 0,1,2,3,4,5,6,7,8,9,A,b,C,d,F,G,º,OFF,

  //int x = 0;        // display
  int digitos;
  String textNum = "";
  int charPos = 0;  // aqui selecciono el caracter a escirbir
  int delimeter;    // aqui ajuslo lo delimitadores, uno al inicio y otro al final
  int offset = x;

  textNum = String(num);
  //digitos = textNum.length();

  // cantidad de displays usados para representar el número
   // if (digitos > DisplayNumber)  // Si el display seleccionado no existe, se regresa
   //return;
  
  // Barro según la cantidad de displays disponibles
  for(x = 0; x <= DisplayNumber; x++)
  {
    
    write(x + offset,(textNum[x])-32);
  }
  
}

//---------------------------------------------------------------------------- print( char num,x)
// x ----> Representa el display o posición a partir de la cual imprimir
// num --> Letra a escribir

void NeoDigito::print(char num, int x)
{
 
 bitmask = characterMap[num]; // Cargo los caracteres disponibles 0,1,2,3,4,5,6,7,8,9,A,b,C,d,F,G,º,OFF,

  //int x = 0;        // display
  int digitos;
  String textNum = "";
  int charPos = 0;  // aqui selecciono el caracter a escirbir
  int delimeter;    // aqui ajuslo lo delimitadores, uno al inicio y otro al final
  int offset = x;

  //textNum = String(num);
  //digitos = textNum.length();

  // cantidad de displays usados para representar el número
   // if (digitos > DisplayNumber)  // Si el display seleccionado no existe, se regresa
   //return;
  
  // Barro según la cantidad de displays disponibles
  //for(x = 0; x <= DisplayNumber; x++)
  //{

    // -------- solo puntos
    if(num == ':' || num == ';')
    {
      //write(x,(num-32));
      updateDelimiter(x);
    }
    else if(num == '.' || num == ',')
    {
      updatePoint(x);
    }
    else if(num == "'")
    {
      updateTilde(x);
    }

    // solo letras sin delimitador
    else
    {
      write(x,(num-32));
      updateDelimiter(x,0,0,0);
      updateDelimiter(x+1,0,0,0);
    }

    // ----- letras con puntos
    if(num == '*' || num == '�' || num == 'i' || num == 'T' || num == 'P') // tilde atras
    {
      write(x,(num-32));
      updateTilde(x);
    }

    if(num == '+' || num == 'J' || num == 'g' || num == '~') // tilde adelante
    {
      write(x,(num-32));
      updateTilde(x+1);
    }

    if(num == '!' || num == '?')  // punto atras
    {
      write(x,(num-32));
      updatePoint(x);
    }

    if(num == 'Q' || num == 'R' || num == 'l' || num == 't' || num == 'u')  // punto adelante
    {
      write(x,(num-32));
      updatePoint(x +1);
    }

    if(num == '&' || num == 'k' || num == 'K' || num == '{' || num == '(')	// dos puntos adelante
    {
      write(x,(num-32));
      updateDelimiter(x + 1);
    }
    
    if(num == ')' || num == '}')	// dos puntos atr�s
    {
    	write(x,(num-32));
    	updateDelimiter(x);
	}

    if(num == '$' || num == '%')  // Tilde atras, punto adelante
    {
      write(x,(num-32));
      updatePoint(x+1);
      updateTilde(x);
    }
    
    if(num == 'V' || num == 'Y')	// Dos puntos arriba
    {
    	write(x,(num-32));
    	updateTilde(x);
		updateTilde(x+1);
	}
	
	if(num == 'X')	// Cuatro puntos
	{
		write(x,(num-32));
		updateDelimiter(x);
		updateDelimiter(x+1);
	}
  //}
  
}
