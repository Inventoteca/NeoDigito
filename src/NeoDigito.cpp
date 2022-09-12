/*
NeoDigito:
  Large custom made 7 segment neopixel displays.
  Created and empowered by Inventoteca and Xircuitos, October 21, 2020.
*/

#include "NeoDigito.h"
//#include <../Adafruit_NeoPixel/Adafruit_NeoPixel.h>

// How many NeoPixels are in the seven segment display total?
uint32_t n;
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
	
	n =  (uint32_t(digitsPerDisplay * pixelsPerSegment * 7)) + digitsPerDisplay * (uint8_t( numDelimiters * pixPerDelimiter));
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
	displayCursor = 0;
}

// -------------------------------------------------------- setCursor(pos)
void NeoDigito::setCursor(uint16_t pos)
{
	displayCursor = pos;
}

// -------------------------------------------------------- setPixelColor(R,G,B)
void NeoDigito::setColor(uint32_t R, uint16_t G, uint8_t B)
{
	Color = R << 16 | G << 8 | B;
}

// -------------------------------------------------------- setPixelColor(c)
void NeoDigito::setColor(uint32_t c)
{
    //for(int i = 0; i < n; i++)
	//{
		switch(c)
		{
			case 0:	//white
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
			
			case 6://cian
			{
				Color = 0x00FFFF;
			}
				break;
			
			case 7://pink
			{
				Color = 0xFF1493;
			}
				break;
			
			case 8://purple
			{
				Color = 0xAA00FF;
			}
				break;
			
			default:
			{
				Color = c;
			}
				break;
		}
		
		//if((strip->getPixelColor(i) != 0) && (Color != 0))
		//	strip->setPixelColor(i, Color);
	//}
}

// -------------------------------------------------------- updatePixelColor(FX)
// This fuction admits the name of color FX and some solid colors, also admits
// a 32bit number to assign a particular color.
// Add offset to make FX start in a different color or to move along the pixels (for Random fx is not neccesary)
void NeoDigito::updateColor(uint32_t FX, uint32_t offset, uint32_t end)
{
	byte wheelPos;
	//offset = offset * 16;
	//end = end *16;

	for(int32_t i = offset*16; i < (end+1)*16; i++)
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
				wheelPos = map(i,offset*16,end*16,0,255);
				wheel(wheelPos);
			}
				break;
			
			case 11:	//random
			{
				if ((i) % (pixPerSeg * 7 + numDelims * pixPerDelim) == 0)
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
		
		uint8_t R = Color >> 16;
		uint8_t G = Color >> 8;
		uint8_t B = Color;
		if((strip->getPixelColor(i) != 0) && (Color != 0))
		{
			strip->setPixelColor(i,Color);
			//strip->setPixelColor(i, (strip -> gamma8(R)),(strip -> gamma8(G)),(strip -> gamma8(B)));
			//strip->setPixelColor(i, (strip -> gamma32(R)),(strip -> gamma32(G)),(strip -> gamma32(B)));
		}
	}
}

// -------------------------------------------------------- updatePixelColor(FX)
// This fuction admits the name of color FX and some solid colors, also admits
// a 32bit number to assign a particular color.
void NeoDigito::updateColor(uint32_t FX)
{
	updateColor(FX,0,DisplayNumber);
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
	//if(digit == '°')
	//	digit = 126;
	
	if(digit < 32 || digit > 127)
		digit = 127;
		//return;
		
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
    
	if(digit == '*' || digit == '¿' || digit == 'i') // Accent mark (behind)
		updateTilde(pos);

    //if(digit == 'J' || digit == '~') // Accent mark (forward)
	//	updateTilde(pos + 1);

    if(digit == '!' || digit == '?')  // Dot (behind)
		updatePoint(pos);

    //if(digit == 'Q' || digit == 'R' || digit == 'u')  // Dot (forward)
	//	updatePoint(pos + 1);

    if(digit == '&')	// Double dot (forward)
		updateDelimiter(pos + 1);
    
    //if(digit == ')' || digit == '}')	// Double dot (behind)
	//	updateDelimiter(pos);

    if(digit == '$' || digit == '%') 	// Accent mark (behind), Dot (forwarD)
    {
		updatePoint(pos + 1);
		updateTilde(pos);
    }
    
    //if(digit == 'V' || digit == 'Y')	// Double accent mark
    //{
	//	updateTilde(pos);
	//	updateTilde(pos + 1);
	//}
	
	//if(digit == 'X')	// Double accent mark, double dot
	//{
	//	updateDelimiter(pos);
	//	updateDelimiter(pos + 1);
	//}
	
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


//---------------------------------------------------------------------------- print(String word, r,g,b)
// word --> Word to write
// pos ---> Represents the digit position in the display
// r,g,b
void NeoDigito::print(String word, uint8_t RED, uint8_t GREEN, uint8_t BLUE)
{	
	//displayCursor = pos;
	int digitos;
	digitos = word.length();
	int x = 0;

	while(x < digitos)
	{
		write((word[x]), displayCursor,RED,GREEN,BLUE);
		//if(word[x+1] == '.' || word[x+1] == ',' || word[x+1] == ':' || word[x+1] == ';' || word[x+1] == 39){
		//	displayCursor++;
		//}
		x++;
	}
}



//---------------------------------------------------------------------------- print(String word, int pos)
// word --> Word to write
// rgb ---> Represents the color
void NeoDigito::print(String word, uint32_t rgb)
{	
	//displayCursor = pos;

	setColor(rgb);
	uint8_t R = Color >> 16;
	uint8_t G = Color >> 8;
	uint8_t B = Color;

	print(word,R,G,B);
}

//---------------------------------------------------------------------------- print(String word)
// word --> Word to write
void NeoDigito::print(String word)
{	
	print(word,Color);
}

//---------------------------------------------------------------------------- print(int num, byte red, byte green, byte blue)
// num --> Value to write
// r,g,b
void NeoDigito::print(int32_t num, uint8_t RED, uint8_t GREEN, uint8_t BLUE)
{
	String textNum = "";
	textNum = String(num);
	
	print(textNum,RED,GREEN,BLUE);
}

//---------------------------------------------------------------------------- print(int num, int pos)
// pos --> Represents the digit position in the display
// num --> Value to write
void NeoDigito::print(int32_t num, uint32_t rgb)
{
	//displayCursor = pos;
	String textNum = "";
	textNum = String(num);
	
	print(textNum,rgb);
}

//---------------------------------------------------------------------------- print(int num)
// num --> Value to write
void NeoDigito::print(int32_t num)
{
	//print(num,0);
	print(num,Color);
}

//---------------------------------------------------------------------------- print(float num, int pos)
// pos --> Represents the digit position in the display
// num --> Value to write
/*void NeoDigito::print(double num, uint32_t rgb)
{
	//setColor();
	String textNum = "";
	//textNum = String(num); //Contar la cantidad de decimales que tiene el 'float' para saber cuantos imprimira
	textNum.concat(num);

	print(textNum,rgb);
}*/

//---------------------------------------------------------------------------- print(float num)
// num --> Value to write
/*void NeoDigito::print(double num)
{
	//print(num,0);
	print(num,Color);
}*/

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