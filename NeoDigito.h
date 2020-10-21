/*
  NeoDigito.h - Library for driving obnoxiously
  large custom made 7 segment pixel displays.
  Created by Peter Hartmann, July 15, 2017.
  Released under GPLv3.
*/

#ifndef NeoDigito_H
#define NeoDigito_H

#include <../Adafruit_NeoPixel/Adafruit_NeoPixel.h>
#include <Arduino.h>

class NeoDigito {
public:
  NeoDigito(uint16_t digitsPerStrip, uint16_t pixelsPerSegment,
                      uint16_t numDelimiters, uint16_t pixPerDelimiter,
                      uint16_t n, uint8_t p, uint8_t t);
  ~NeoDigito();

  void begin(), show(), setPixelColor(uint16_t n, uint32_t c),
      updateDigit(uint16_t position, uint16_t digit, uint8_t RED, uint8_t GREEN,
                  uint8_t BLUE),
      updateDelimiter(uint16_t delimeter, uint8_t RED, uint8_t GREEN,
                      uint8_t BLUE);

private:
  Adafruit_NeoPixel *strip;
  // 0,1,2,3,4,5,6,7,8,9 and null a character,
  // then array positions 11-17 are individual segments for funz.
  char *characterMap[18] = {
      "1110111", "1000100", "0111110", "1101110", "1001101", "1101011",
      "1111011", "1000110", "1111111", "1101111", "0000000", "1000000",
      "0100000", "0010000", "0001000", "0000100", "0000010", "0000001"};
  const uint16_t pixPerSeg, digPerDisp, numDelims, pixPerDelim;
  String bitmask;
};

#endif
