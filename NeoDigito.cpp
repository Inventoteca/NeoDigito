/*
NeoDigito:
  large custom made 7 segment neopixel displays.
  Created by Inventoteca and Xircuitos, October 21, 2020.
  Released under GPLv3, based on Seven_Segment_Pixel, by Peter Hartmann.
*/

#include "NeoDigito.h"
#include <../Adafruit_NeoPixel/Adafruit_NeoPixel.h>

// How many NeoPixels are in the seven segment display total?
uint8_t n;
uint16_t numDelimiters = 1;
uint16_t pixPerDelimiter = 1;

//<<constructor>>
NeoDigito::NeoDigito(uint16_t digitsPerDisplay,
                                         uint16_t pixelsPerSegment,
                                         uint8_t p, uint8_t t)
    : digPerDisp(digitsPerDisplay), pixPerSeg(pixelsPerSegment),
      numDelims(numDelimiters), pixPerDelim(pixPerDelimiter)
  {
    n =  (uint8_t(digitsPerDisplay * pixelsPerSegment * 7)) + (uint8_t( numDelimiters * pixPerDelimiter));
    strip = new Adafruit_NeoPixel(n, p, t);
  }
//<<destructor>>
NeoDigito::~NeoDigito() {}

void NeoDigito::begin() { strip->begin(); }

void NeoDigito::show() { strip->show(); }

void NeoDigito::setPixelColor(uint16_t n, uint32_t c){
    strip->setPixelColor(n, c);}

void NeoDigito::updateDigit(uint16_t position, uint16_t digit,
                                      uint8_t RED, uint8_t GREEN,
                                      uint8_t BLUE) {

  bitmask = characterMap[digit];

  int charPos = 0;
  // expand bitbask to number of pixels per segment in the proper position
  //for (int x = (position - 1) * 7; x <= (position - 1) * 7 + 6; x++)
  for (int x = 0; x <= 6; x++)
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

void NeoDigito::updateDelimiter(uint16_t delimeter, uint8_t RED,
                                          uint8_t GREEN, uint8_t BLUE) {

  int digitsOffset = digPerDisp * pixPerSeg * 7;

  for (int pix = digitsOffset + delimeter * pixPerDelim - pixPerDelim;
       pix <= digitsOffset + delimeter * pixPerDelim; pix++) {
    strip->setPixelColor(pix, strip->Color(RED, GREEN, BLUE));
  }
}
