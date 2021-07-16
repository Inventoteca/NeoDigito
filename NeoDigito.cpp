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
uint16_t displayCursor = 0;

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

// -------------------------------------------------------- setPixelColor(c)
void NeoDigito::setPixelColor(uint32_t c)
{
    Color = c;
}

// -------------------------------------------------------- updatePixelColor(c)
void NeoDigito::updatePixelColor(String FX)
{

    if(FX == "Rainbow")
	{
		byte wheelPos;
		uint32_t R, G, B;

		for(int i = 0; i < n; i++)
		{
			wheelPos = map(i,0,n,0,255);

			if(wheelPos < 85)
			{
				R = 255 - 3*wheelPos;
				G = 0;
				B = 3*wheelPos;
			}
			else if(wheelPos < 170)
			{
				wheelPos -= 85;
				R = 0;
				G = 3*wheelPos;
				B = 255 - 3*wheelPos;
			}
			else if(wheelPos < 255)
			{
				wheelPos -= 170;
				R = 3*wheelPos;
				G = 255 - 3*wheelPos;
				B = 0;
			}

			Color = R << 16 | G << 8 | B;

			if((strip->getPixelColor(i) != 0) && (Color != 0))
			{
				strip->setPixelColor(i, Color);
			}	
		}
	}
	//if(FX == "Random")
	//if(FX == "Xmas")
	//if(FX == "Halloween")
	//if(FX == "Birthday")
	//if(FX == "Pulse")    for(int i = 0; i < n; i++)
	else
	{
		return;
	}
}

// -------------------------------------------------------- updatePixelColor(c)
void NeoDigito::updatePixelColor(uint32_t c)
{
	Color = c;
	for(int i = 0; i < n; i++)
	{
		if((strip->getPixelColor(i) != 0) && (c != 0))
		{
			strip->setPixelColor(i, c);
		}	
	} 
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

void NeoDigito::clear()
{
	strip->clear();
	displayCursor = 0;
}


//----------------------------------------------------------------------------------write(digit, pos, RED, GREEN, BLUE)
void NeoDigito::write(uint16_t digit, uint16_t pos, uint8_t RED, uint8_t GREEN, uint8_t BLUE)
{
	if(digit == '°')
		digit = 128;
	
	else if(digit < 32 || digit > 127)
		return;
		
	bitmask = characterMap[digit - 32]; // It loads the characters available.
	
	int charPos = 0;
	int delimeter = pos * 2 + 1; // Omit the delimeters spaces.
	
	if (pos > DisplayNumber) // If the number of displays needed is greater than the number of displays available, it returns.
	    return;
	    
	if(digit == 13)
  	{
  		clear();
	}
	
	else if(digit <= 127)
	{
		int i = 6;
		// Expand bitbask to number of pixels per segment in the proper position.
		for (int x = (pos) * 7; x <= (pos) * 7 + 6; x++)
		{
			uint8_t ref = 0x01;
			uint8_t res = 0x00;
		
			res = (bitmask >> i) & ref;
			
			for(int pix = 0; pix < pixPerSeg; pix++)
			{
				if (res == 0x01) // Lighting up this segment
					strip->setPixelColor(((x * pixPerSeg) + pix + delimeter),strip->Color(RED, GREEN, BLUE));
				
				if (res == 0x00) // Turning off this segment.
					strip->setPixelColor((x * pixPerSeg + pix + delimeter), 0);
				
			}	
			i--;
		}  
	  
		// -------- Only dots
	    if(digit == ':' || digit == ';')
			updateDelimiter(pos);
	
	    else if(digit == '.' || digit == ',')
			updatePoint(pos);
			
	    else if(digit == 39)
			updateTilde(pos);
	    
	    // Single-space letters without delimiter
	    else
	    {
			updateDelimiter(pos,0,0,0);
			updateDelimiter(pos + 1,0,0,0);
			displayCursor++;
	    }
	}
  	
    // ----- Letters with dots
    if(digit == '*' || digit == '�' || digit == 'i' || digit == 'T' || digit == 'P') // Accent mark (behind)
		updateTilde(pos);

    if(digit == 'J' || digit == '~') // Accent mark (forward)
		updateTilde(pos + 1);

    if(digit == '!' || digit == '?')  // Dot (behind)
		updatePoint(pos);

    if(digit == 'Q' || digit == 'R' || digit == 't' || digit == 'u')  // Dot (forward)
		updatePoint(pos + 1);

    if(digit == '&' || digit == 'k' || digit == 'K' || digit == '{' || digit == '(')	// Double dot (forward)
		updateDelimiter(pos + 1);
    
    if(digit == ')' || digit == '}')	// Double dot (behind)
		updateDelimiter(pos);

    if(digit == '$' || digit == '%')  // Accent mark (behind), Dot (forwarD)
    {
		updatePoint(pos + 1);
		updateTilde(pos);
    }
    
    if(digit == 'V' || digit == 'Y')	// Double accent mark
    {
		updateTilde(pos);
		updateTilde(pos + 1);
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
void NeoDigito::write(uint16_t digit, uint16_t pos, uint32_t rgb)
{
	uint8_t R = rgb >> 16;
	uint8_t G = rgb >> 8;
	uint8_t B = rgb;
	write(digit, pos, R, G, B);
}


//---------------------------------------------------------------------------- write(digit,pos)
// pos ----> Represents the digit position in the display
// digit --> Value to write
void NeoDigito::write(uint16_t digit, uint16_t pos) 
{
	uint32_t rgb = Color;
    write(digit, pos, rgb);
}

//---------------------------------------------------------------------------- print(String word, int pos)
// word --> Word to write
// pos ---> Represents the digit position in the display
void NeoDigito::print(String word, int pos)
{	
	displayCursor = pos;
	int digitos;
	//int x=displayCursor;
	digitos = word.length();
	int x = 0;

	//for(int x = 0; x < digitos; x++)
	while(x < digitos)
	{
		write((word[x]), displayCursor);
		x++;
	}
}

//---------------------------------------------------------------------------- print(String word)
// word --> Word to write
void NeoDigito::print(String word)
{	
	print(word,0);
}

//---------------------------------------------------------------------------- print(int num, int pos)
// pos --> Represents the digit position in the display
// num --> Value to write
void NeoDigito::print(int num, int pos)
{
	displayCursor = pos;
	String textNum = "";
	textNum = String(num);
	
	print(textNum,displayCursor);
}

//---------------------------------------------------------------------------- print(int num)
// num --> Value to write
void NeoDigito::print(int num)
{
	print(num,0);
}

//---------------------------------------------------------------------------- print(float num, int pos)
// pos --> Represents the digit position in the display
// num --> Value to write
void NeoDigito::print(float num, int pos)
{
	displayCursor = pos;
	String textNum = "";
	//textNum = String(num); //Contar la cantidad de decimales que tiene el 'float' para saber cuantos imprimira
	textNum.concat(num);

	print(textNum,displayCursor);
}

//---------------------------------------------------------------------------- print(float num)
// num --> Value to write
void NeoDigito::print(float num)
{
	print(num,0);
}

/*
void NeoDigito::wheel(byte wheelPos)
{	
	byte R, G, B;
	
	if(wheelPos < 85)
	{
		R = 255 - 3*wheelPos;
		G = 0;
		B = 3*wheelPos;
	}
	else if(wheelPos < 170)
	{
		wheelPos -= 85;
		R = 0;
		G = 3*wheelPos;
		B = 255 - 3*wheelPos;
	}
	else if(wheelPos < 255)
	{
		wheelPos -= 170;
		R = 3*wheelPos;
		G = 255 - 3*wheelPos;
		B = 0;
	}
	
	Color = R << 16 | G << 8 | B;
	
	setPixelColor(Color);
}

void NeoDigito::colorFX(int number)
{
	switch(number)
	{
		case 0:
			for(byte wheelPos = 255; wheelPos >= 0; wheelPos--)
			{
				wheel(wheelPos);
				delay(100);
			}
			break;
		default:
			break;
	}
}
*/