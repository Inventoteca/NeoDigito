/*
  NeoDigito.h - Library for driving NeoDigito
  large custom made 7 segment neopixel displays.
  Created by Inventoteca and Xircuitos, October 21, 2020.
  Released under GPLv3, based on Seven_Segment_Pixel, by Peter Hartmann.
*/

#ifndef NeoDigito_H
#define NeoDigito_H

#include <Adafruit_NeoPixel.h>
#include <../Adafruit_NeoPixel/Adafruit_NeoPixel.h>
#include <Arduino.h>

class NeoDigito 
{
public:
  NeoDigito(uint16_t digitsPerStrip, uint16_t pixelsPerSegment, uint8_t p, uint8_t t);
  ~NeoDigito();

  void begin(), 
       show(), 
       setPixelColor(uint16_t n, uint32_t c), 
       setPixelColor(uint32_t c),
       updateDigit(uint16_t position, uint16_t digit, uint8_t RED, uint8_t GREEN, uint8_t BLUE),
       updateDelimiter(uint16_t delimeter, uint8_t RED, uint8_t GREEN, uint8_t BLUE),
       write(uint16_t position, uint16_t digit, uint8_t RED, uint8_t GREEN, uint8_t BLUE);
/*!
    @brief  Set specific digit # to a numeric value.
    @param  x    Character position.
    @param  num  Numeric (not ASCII) value.
    @param  rgb  Color argument in Wheel Format.
  */
  
  void write(uint8_t x, uint8_t num, uint32_t rgb);
  void write(uint8_t x, uint8_t num);
  void print(int32_t num);

private:
  Adafruit_NeoPixel *strip;
  // 0,1,2,3,4,5,6,7,8,9,A,b,C,d,F,G,º,-,OFF,
  // then array positions 11-17 are individual segments for funz.
  char *characterMap[21] = {
      "1110111","1000100", "0111110", "1101110", "1001101", "1101011",
      "1111011", "1000110", "1111111", "1101111", "1011111", "1111001",
      "0110011", "1111100", "0111011", "0011011", "1111011", "1011001","0001111","0001000","0000000",};
  const uint16_t pixPerSeg, digPerDisp, numDelims, pixPerDelim;
  String bitmask;
};

#endif
