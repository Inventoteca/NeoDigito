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
       //updateDigit(uint16_t position, uint16_t digit, uint8_t RED, uint8_t GREEN, uint8_t BLUE),
       updateDelimiter(uint16_t delimeter, uint8_t RED, uint8_t GREEN, uint8_t BLUE),
       updateDelimiter(uint16_t delimeter),
       updatePoint(uint16_t delimeter),
       updateTilde(uint16_t delimeter);

/*!
    @brief  Set specific digit # to a numeric value.
    @param  x    Character position.
    @param  num  Numeric (not ASCII) value.
    @param  rgb  Color argument in Wheel Format.
  */
  
  void write(uint16_t position, uint16_t digit, uint8_t RED, uint8_t GREEN, uint8_t BLUE);
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
  char *characterMap[96] = 
    // 1234567
  {
      "0000000",    //          32  
      "1000000",    // !        33
      "1010000",    // "        34
      "1011101",    // #        35
      "1101011",    // $        36
      "0011100",    // %        37
      "1111111",    // &        38
      "0010000",    // '        39  
      "0010001",    // (        40  
      "1000100",    // )        41  
      "1100000",    // *        42
      "0011001",    // +        43
      "0000000",    // ,        44
      "0001000",    // -        45
      "0000000",    // .        46
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
      "0111100",    // ?        63
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
      "0110011",    // J        74
      "1011100",    // K        75
      "1000110",    // L        76
      "1110101",    // M        77
      "1110101",    // N        78
      "1110111",    // 0        79
      "1111100",    // P        80
      "1110111",    // Q        81
      "1111100",    // R        82 
      "1101011",    // S        83  
      "1100100",    // T        84
      "1010111",    // U        85
      "1010111",    // V        86
      "1010111",    // W        87
      "1011101",    // X        88
      "1011011",    // Y        89
      "0111110",    // Z        90
      "1100110",    // [        91
      "1001001",    // \        92
      "0110011",    // ]        93
      "1110000",    // ^        94
      "0000010",    // _        95
      "1000000",    // `        96
      "0111111",    // a        97
      "1001111",    // b        98
      "0001110",    // c        99
      "0011111",    // d       100
      "1111110",    // e       101
      "1101100",    // f       102
      "1111011",    // g       103
      "1001101",    // h       104
      "0000100",    // i       105
      "0010011",    // j       106
      "1001100",    // k       107
      "0010001",    // l       108
      "0001101",    // m       109
      "0001101",    // n       110
      "0001111",    // o       111
      "1111100",    // p       112
      "1111001",    // q       113
      "0001100",    // r       114
      "1101011",    // s       115
	  "0011001",    // t       116
      "0000111",    // u       117
      "0000111",    // v       118
      "0000111",    // w       119
      "1011101",    // x       120
      "1011011",    // y       121
      "0111110",    // z       122
      "0011001",    // {       123
      "1000100",    // |       124
      "1001100",    // }       125
      "0011000",    // ~       126
	  "0000000"};   // [DEL]   127      	
  const uint16_t pixPerSeg, digPerDisp, numDelims, pixPerDelim;
  String bitmask;
};

#endif
