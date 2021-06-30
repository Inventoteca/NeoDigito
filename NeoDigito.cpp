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
void NeoDigito::show()
{
	strip->show();
}

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


//----------------------------------------------------------------------------------write(digit, pos, RED, GREEN, BLUE)
void NeoDigito::write(uint16_t digit, uint16_t pos, uint8_t RED, uint8_t GREEN, uint8_t BLUE)
{
	if (pos > DisplayNumber) // If the number of displays needed is greater than the number of displays available, it returns.
	    return;
    
	bitmask = characterMap[digit]; // It loads the characters available.
	
	int charPos = 0;
	int delimeter = pos * 2 + 1; // Omit the delimeters spaces.

	// Expand bitbask to number of pixels per segment in the proper position.
	for (int x = (pos) * 7; x <= (pos) * 7 + 6; x++)
	{
		for(int pix = 0; pix < pixPerSeg; pix++)
		{
			if (bitmask.charAt(charPos) == '1') // Lighting up this segment
			strip->setPixelColor(((x * pixPerSeg) + pix + delimeter),strip->Color(RED, GREEN, BLUE));
			
			else // Turning off this segment.
			strip->setPixelColor((x * pixPerSeg + pix + delimeter), 0);
		}
		charPos++;
	}
	strip->show();
  
	// -------- Only dots
    if(digit == ':' || digit == ';')
		updateDelimiter(pos);

    else if(digit == '.' || digit == ',')
		updatePoint(pos);
		
    else if(digit == "'")
		updateTilde(pos);
    
    // Single-space letters without delimiter
    else
    {
		updateDelimiter(pos,0,0,0);
		updateDelimiter(pos+1,0,0,0);
		//updateDelimiter(pos+2,0,0,0);
    }
	
    // ----- Letters with dots
    if(digit == '*' || digit == '�' || digit == 'i' || digit == 'T' || digit == 'P') // Accent mark (behind)
		updateTilde(pos);

    if(digit == 'J' || digit == 'g' || digit == '~') // Accent mark (forward)
		updateTilde(pos+1);

    if(digit == '!' || digit == '?')  // Dot (behind)
		updatePoint(pos);

    if(digit == 'Q' || digit == 'R' || digit == 'l' || digit == 't' || digit == 'u')  // Dot (forward)
		updatePoint(pos + 1);

    if(digit == '&' || digit == 'k' || digit == 'K' || digit == '{' || digit == '(')	// Double dot (forward)
		updateDelimiter(pos + 1);
    
    if(digit == ')' || digit == '}')	// Double dot (behind)
		updateDelimiter(pos);

    if(digit == '$' || digit == '%')  // Accent mark (behind), Dot (forwarD)
    {
		updatePoint(pos+1);
		updateTilde(pos);
    }
    
    if(digit == 'V' || digit == 'Y')	// Double accent mark
    {
		updateTilde(pos);
		updateTilde(pos+1);
	}
	
	if(digit == 'X')	// Double accent mark, double dot
	{
		updateDelimiter(pos);
		updateDelimiter(pos + 1);
	}
	
	/*
	// ----- letras y s�mbolos de dos espacios
	if(digit == '+')
	{
		write(pos,(digit-32));
		write(pos+1,(45-32));
	}
	
	if(digit == 'M' || digit == 'm')
	{
		updatePoint(pos);
		write(pos,(digit-32));
		write(pos+1,(digit-32));
		updatePoint(pos+2);
	}
	
	if(digit == 'W')
	{
		updateTilde(pos);
		write(pos,(digit-32));
		write(pos+1,(digit-32));
		updateTilde(pos+2);
	}
	
	if(digit == 'w')
	{
		write(pos,(digit-32));
		write(pos+1,(digit-32));
	}*/
}



//----------------------------------------------------------------------------------write(digit, pos, rgb)
// pos ----> Represents the digit position in the display
// digit --> Value to write
// rgb ----> Display color
void NeoDigito::write(uint8_t digit, uint8_t pos, uint32_t rgb)
{
	uint8_t R = rgb >> 16;
	uint8_t G = rgb >> 8;
	uint8_t B = rgb;
	write(digit, pos, R, G, B);
}


//---------------------------------------------------------------------------- write(digit,pos)
// pos ----> Represents the digit position in the display
// digit --> Value to write
void NeoDigito::write(uint8_t digit, uint8_t pos) 
{
	uint32_t rgb = Color;
    write(digit, pos, rgb);
}


//---------------------------------------------------------------------------- print(num)
// num --> Value to write
void NeoDigito::print(int num)
{
	//int digitos;
	String textNum = "";
	textNum = String(num);
	//digitos = textNum.length();
	
	for(int x = 0; x <= DisplayNumber; x++)
	{
		write((textNum[x])-32,x);
  	}
}


/*
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
    
    write((textNum[x])-32,x + offset);
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
  //}
  
}*/
