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
  void print(int num, int x); // número y posición
  void print(int num);
  void print(char num, int x);  //letra y posición
  

private:
  Adafruit_NeoPixel *strip;
  // 0,1,2,3,4,5,6,7,8,9,A,b,C,d,F,G,º,-,OFF,
  /*
    Aqui hay que poner la imagen del orden
    '8.

    0    2
      1     3
         4
      5     7
         6    8
  */
  // then array positions 11-17 are individual segments for funz.
  char *characterMap[47] = 
    // 1234567
  {
      "0000000",    //          32  
      "1000100",    // !        33
      "1010000",    // "        34
      "1011101",    // #        35
      "1101011",    // $        36
      "0011100",    // %        37
      "1111111",    // &        38
      "0010000",    // '        39  
      "1100110",    // (        40  
      "0110011",    // )        41  
      "1010000",    // *        42
      "0011001",    // +        43
      "0000100",    // ,        44
      "0001000",    // -        45
      "0000001",    // .        46
      "0011100",    // /        47
      "1110111",    // 0        48
      "0010001",    // 1        49
      "0111110",    // 2        50
      "0111011",    // 3        51
      "1011001",    // 4        52
      "1101011",    // 5        53
      "1101111",    // 6        54  
      "0110001",    // 7        55
      "1111111",    // 8        56
      "1111011",    // 9        57
      "0001010",    // :        58
      "0001010",    // ;        59
      "0001110",    // <        60
      "0001010",    // =        61
      "0001011",    // >        62
      "0110100",    // ?        63
      "0111111",    // @        64
      "1111101",    // A        65
      "1111111",    // B        66
      "1100110",    // C        67
      "0011111",    // D        68
      "1101110",    // E        69
      "1101100",    // F        70
      "1101111",    // G        71
      "1011101",    // H        72
      "1000100",    // I        73
      "0010011",    // J        74
      "1011100",    // K        75
      "1000110",    // L        76
      "1110101",    // M        77
      "1110101",};  // N        78          
  const uint16_t pixPerSeg, digPerDisp, numDelims, pixPerDelim;
  String bitmask;
};

#endif
