/*
NeoDigito:
  Large custom made 7 segment neopixel displays.
  Created and empowered by Inventoteca and Xircuitos, October 21, 2020.
*/

#include "NeoDigito.h"
//#include <../Adafruit_NeoPixel/Adafruit_NeoPixel.h>

// How many NeoPixels are in the seven segment display total?
uint8_t n;
uint16_t DisplayNumber;
uint32_t Color = 0xffffff;   // white is default color
uint16_t displayCursor = 0;

//<<constructor>>
// |--- delimiter number and pixels per delimiter are different than 2 and 1 respectively 
NeoDigito::NeoDigito(uint16_t digitsPerDisplay, uint16_t pixelsPerSegment, uint16_t numDelimiters, uint16_t pixPerDelimiter, uint8_t p, uint8_t t)
	: digPerDisp(digitsPerDisplay), pixPerSeg(pixelsPerSegment),
	numDelims(numDelimiters), pixPerDelim(pixPerDelimiter)
{
	DisplayNumber = digitsPerDisplay;
	
	n =  (uint8_t(digitsPerDisplay * pixelsPerSegment * 7)) + digitsPerDisplay * (uint8_t( numDelimiters * pixPerDelimiter));
	strip = new Adafruit_NeoPixel(n, p, t);
}

// |--- delimiter number is different than 2 but the number of pixels per delimiter is 1 by default
NeoDigito::NeoDigito(uint16_t digitsPerDisplay, uint16_t pixelsPerSegment, uint16_t numDelimiters, uint8_t p, uint8_t t)
	: digPerDisp(digitsPerDisplay), pixPerSeg(pixelsPerSegment),
	numDelims(numDelimiters), pixPerDelim(1)
{
	DisplayNumber = digitsPerDisplay;
	
	n =  (uint8_t(digitsPerDisplay * pixelsPerSegment * 7)) + digitsPerDisplay * (uint8_t( numDelimiters * 1));
	strip = new Adafruit_NeoPixel(n, p, t);
}

// |--- delimiter number and pixels per delimiter are 2 and 1 respectively by default
NeoDigito::NeoDigito(uint16_t digitsPerDisplay, uint16_t pixelsPerSegment, uint8_t p, uint8_t t)
	: digPerDisp(digitsPerDisplay), pixPerSeg(pixelsPerSegment),
	numDelims(2), pixPerDelim(1)
{
	DisplayNumber = digitsPerDisplay;
	
	n =  (uint8_t(digitsPerDisplay * pixelsPerSegment * 7)) + digitsPerDisplay * (uint8_t( 2 * 1));
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

// -------------------------------------------------------- setPixelColor(R,G,B)
void NeoDigito::setPixelColor(uint32_t R, uint16_t G, uint8_t B)
{
	Color = R << 16 | G << 8 | B;
}

// -------------------------------------------------------- setPixelColor(c)
void NeoDigito::setPixelColor(uint32_t c)
{
    for(int i = 0; i < n; i++)
	{
		switch(c)
		{
			case 0:	//white
				Color = 0xAAAAAA;
				break;
			
			case 1:	//red
				Color = 0xFF0000;
				break;
			
			case 2:	//green
				Color = 0x00FF00;
				break;
			
			case 3:	//blue
				Color = 0x0000FF;
				break;
			
			case 4:	//orange
				Color = 0xFFA500;
				break;
			
			case 5: //yellow
				Color = 0xFFFF00;
				break;
			
			case 6://cian
				Color = 0x00FFFF;
				break;
			
			case 7://pink
				Color = 0xFF1493;
				break;
			
			case 8://purple
				Color = 0xAA00FF;
				break;
			
			default:
				Color = c;
				break;
		}
		
		if((strip->getPixelColor(i) != 0) && (Color != 0))
			strip->setPixelColor(i, Color);
	}
}

// -------------------------------------------------------- updatePixelColor(FX)
// This fuction admits the name of color FX and some solid colors, also admits
// a 32bit number to assign a particular color.
// Add offset to make FX start in a different color or to move along the pixels (for Random fx is not neccesary)
void NeoDigito::updatePixelColor(uint32_t FX, byte offset)
{
	byte wheelPos;

	for(int i = 0; i < n; i++)
	{
		switch(FX)
		{			
			case 0: //white
			{
				Color = 0xAAAAAA;
			}
				break;
				
			case 1:	//red
			{
				Color = 0xFF0000;
			}
				break;
			
			case 2:	//green
			{
				Color = 0x00FF00;
			}
				break;
			
			case 3:	//blue
			{
				Color = 0x0000FF;
			}
				break;
			
			case 4:	//orange
			{
				Color = 0xFFA500;
			}
				break;
			
			case 5: //yellow
			{
				Color = 0xFFFF00;
			}
				break;
			
			case 6: //cian
			{
				Color = 0x00FFFF;
			}
				break;
			
			case 7: //pink
			{
				Color = 0xFF1493;
			}
				break;
			
			case 8: //purple
			{
				Color = 0xAA00FF;
			}
				break;

			case 10:	//rainbow
			{
				wheelPos = map(i,0,n,0,255);
				wheel(wheelPos+offset);
			}
				break;
			
			case 11:	//random
			{
				if ((i+1) % (pixPerSeg * 7 + numDelims * pixPerDelim) == 0)
				{
					wheelPos = random(0, 255);
					wheel(wheelPos);
				}
			}
				break;
			
			case 12:	//xmas
			{
				RedToWhite(wheelPos+offset);	
			}		
				break;
			
			case 13:	//halloween
			{
				uint8_t pix_offset = i + map(offset,0,255,0,n);
				if(pix_offset > n)
					pix_offset -= n;
					
				if(pix_offset < n/4)
					wheelPos = map(pix_offset,0,n/4,60,2);
				
				else if(pix_offset < n/2){
					pix_offset -= n/4;
					wheelPos = map(pix_offset,0,n/4,254,240);
				}

				else if(pix_offset < 3*n/4){
					pix_offset -= n/2;
					wheelPos = map(pix_offset,0,n/4,240,254);
				}

				else if(pix_offset <= n){
					pix_offset -= 3*n/4;
					wheelPos = map(pix_offset,0,n/4,2,60);
				}

				wheel(wheelPos);
			}	
				break;

			//case 14:	//thunder
			//	break;
			
			default:
			{
				Color = FX;
			}
				break;
		}
		
		if((strip->getPixelColor(i) != 0) && (Color != 0))
			strip->setPixelColor(i, Color);
	}
}

// -------------------------------------------------------- updatePixelColor(FX)
// This fuction admits the name of color FX and some solid colors, also admits
// a 32bit number to assign a particular color.
void NeoDigito::updatePixelColor(uint32_t FX)
{
	updatePixelColor(FX,0);
}

//----------------------------------------------------------------------------------updateDelimiter
void NeoDigito::updateDelimiter(uint16_t delimeter, uint8_t RED, uint8_t GREEN, uint8_t BLUE)
{
	if(numDelims > 0 && pixPerDelim > 0)
	{
		int digitsOffset = (delimeter * pixPerDelim * numDelims) + (delimeter * pixPerSeg * 7);
		
		for (int pix = digitsOffset ; (pix > digitsOffset - (pixPerDelim * numDelims)) || (pix == 0); pix--) 
		{
			strip->setPixelColor(pix, strip->Color(RED, GREEN, BLUE));
		}
	}
	else
		return;
}

//----------------------------------------------------------------------------------updateDelimiter
void NeoDigito::updateDelimiter(uint16_t delimeter, uint32_t c)
{
	Color = c;
	if(numDelims > 0 && pixPerDelim > 0)
	{
		int digitsOffset = (delimeter * pixPerDelim * numDelims) + (delimeter * pixPerSeg * 7);
	
		for (int pix = digitsOffset ; (pix > digitsOffset - (pixPerDelim * numDelims)) || (pix == 0); pix--) 
		{
			strip->setPixelColor(pix, Color);
		}
	}
	else
		return;
}

//----------------------------------------------------------------------------------updateDelimiter
void NeoDigito::updateDelimiter(uint16_t delimeter)
{
	if(numDelims > 0 && pixPerDelim > 0)
	{
		int digitsOffset = (delimeter * pixPerDelim * numDelims) + (delimeter * pixPerSeg * 7);
	
		for (int pix = digitsOffset ; (pix > digitsOffset - (pixPerDelim * numDelims)) || (pix == 0); pix--) 
		{
			strip->setPixelColor(pix, Color);
		}
	}
	else
		return;
}

//----------------------------------------------------------------------------------updatePoint
void NeoDigito::updatePoint(uint16_t delimeter, uint8_t RED, uint8_t GREEN, uint8_t BLUE)
{
	if(numDelims > 0 && pixPerDelim > 0)
	{
		int digitsOffset = (delimeter * pixPerDelim * numDelims) + (delimeter * pixPerSeg * 7) - 1;
		
		strip->setPixelColor(digitsOffset, strip->Color(RED, GREEN, BLUE));
	}
	else
		return;
}

//----------------------------------------------------------------------------------updatePoint
void NeoDigito::updatePoint(uint16_t delimeter, uint32_t c)
{
	Color = c;
	if(numDelims > 0 && pixPerDelim > 0)
	{
		int digitsOffset = (delimeter * pixPerDelim * numDelims) + (delimeter * pixPerSeg * 7) - 1;
		
		strip->setPixelColor(digitsOffset, Color);
	}
	else
		return;
}

//----------------------------------------------------------------------------------updatePoint
void NeoDigito::updatePoint(uint16_t delimeter)
{
	if(numDelims > 0 && pixPerDelim > 0)
	{
		int digitsOffset = (delimeter * pixPerDelim * numDelims) + (delimeter * pixPerSeg * 7) - 1;
		
		strip->setPixelColor(digitsOffset, Color);
	}
	else
		return;
}

//----------------------------------------------------------------------------------updateTilde
void NeoDigito::updateTilde(uint16_t delimeter, uint8_t RED, uint8_t GREEN, uint8_t BLUE)
{
	if(numDelims > 0 && pixPerDelim > 0)
	{
		int digitsOffset = (delimeter * pixPerDelim * numDelims) + (delimeter * pixPerSeg * 7);
		
		strip->setPixelColor(digitsOffset, strip->Color(RED, GREEN, BLUE));
	}
	else
		return;
}

//----------------------------------------------------------------------------------updateTilde
void NeoDigito::updateTilde(uint16_t delimeter, uint32_t c)
{
	Color = c;
	if(numDelims > 0 && pixPerDelim > 0)
	{
		int digitsOffset = (delimeter * pixPerDelim * numDelims) + (delimeter * pixPerSeg * 7);
		
		strip->setPixelColor(digitsOffset, Color);
	}
	else
		return;
}

//----------------------------------------------------------------------------------updateTilde
void NeoDigito::updateTilde(uint16_t delimeter)
{
	if(numDelims > 0 && pixPerDelim > 0)
	{
		int digitsOffset = (delimeter * pixPerDelim * numDelims) + (delimeter * pixPerSeg * 7);
		
		strip->setPixelColor(digitsOffset, Color);
	}
	else
		return;
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
	int delimeter = pos * numDelims + pixPerDelim; // Omit the delimeters spaces.
	
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
		if (digit == ':' || digit == ';')
		{
			updateDelimiter(pos);
			updateDelimiter(pos + 1, 0, 0, 0);
		}
	    else if(digit == '.' || digit == ',')
		{
			updatePoint(pos);
			updateDelimiter(pos + 1, 0, 0, 0);
		}
		else if(digit == 39)
		{
			updateTilde(pos);
			updateDelimiter(pos + 1, 0, 0, 0);
		}
		// Numbers
		else if (digit >= 48 || digit <= 57)
		{
			updateDelimiter(pos + 1, 0, 0, 0);
			displayCursor++;
		}
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

    if(digit == 'Q' || digit == 'R' || digit == 'u')  // Dot (forward)
		updatePoint(pos + 1);

    if(digit == '&' || digit == 'k' || digit == 'K' || digit == '{' || digit == '(')	// Double dot (forward)
		updateDelimiter(pos + 1);
    
    if(digit == ')' || digit == '}')	// Double dot (behind)
		updateDelimiter(pos);

    if(digit == '$' || digit == '%') 	// Accent mark (behind), Dot (forwarD)
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
	// ----- double-space letters and symbols
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
	digitos = word.length();
	int x = 0;

	while(x < digitos)
	{
		write((word[x]), displayCursor);
		if(word[x+1] == '.' || word[x+1] == ',' || word[x+1] == ':' || word[x+1] == ';' || word[x+1] == 39){
			displayCursor++;
		}
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

//---------------------------------------------------------------------------- wheel(byte wheelPos)
// wheelPos --> Value from 0 to 255 that represents a color; the colours are a transition from red - green- blue back to red. 
void NeoDigito::wheel(byte wheelPos)
{	
	uint32_t R, G, B;
	
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
}

void NeoDigito::RedToWhite(byte wheelPos)
{
	uint32_t R = 255;
	uint16_t G;
	uint8_t B;
	
	if(wheelPos < 128)
	{
		G = 2*wheelPos;
		B = 2*wheelPos;
	}
	else if(wheelPos < 255)
	{	
		wheelPos -= 127;
		G = 255 - 2*wheelPos;
		B = 255 - 2*wheelPos;
	}

	Color = R << 16 | G << 8 | B;
}