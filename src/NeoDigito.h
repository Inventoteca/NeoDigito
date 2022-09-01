/*
  NeoDigito.h - Library for driving NeoDigito
  large custom made 7 segment neopixel displays.
  Created and empowered by Inventoteca and Xircuitos, October 21, 2020.
*/

#ifndef NeoDigito_H
#define NeoDigito_H

#define white 0
#define red 1
#define green 2
#define blue 3
#define orange 4
#define yellow 5
#define cian 6
#define pink 7
#define purple 8

#define Rainbow 10
#define Random 11
#define Xmas 12
#define Halloween 13
#define Thunder 14
#define Drops 15
#define Fire 16
#define Sparkle 17

#include <Adafruit_NeoPixel.h>
#include <../Adafruit_NeoPixel/Adafruit_NeoPixel.h>
#include <Arduino.h>

class NeoDigito 
{
public:
  NeoDigito(uint16_t digitsPerStrip, uint16_t pixelsPerSegment, uint16_t numDelimiters, uint16_t pixPerDelimiter, uint8_t p, uint8_t t);
  NeoDigito(uint16_t digitsPerStrip, uint16_t pixelsPerSegment, uint16_t numDelimiters, uint8_t p, uint8_t t);
  NeoDigito(uint16_t digitsPerStrip, uint16_t pixelsPerSegment, uint8_t p, uint8_t t);
  ~NeoDigito();

  void begin(),
       show(),
       setColor(uint32_t R, uint16_t G, uint8_t B),
       setColor(uint32_t c),
       setCursor(uint16_t pos),
       updatePixelColor(uint32_t FX, byte offset),
       updatePixelColor(uint32_t FX),
       updateDelimiter(uint16_t delimeter, uint8_t RED, uint8_t GREEN, uint8_t BLUE),
       updateDelimiter(uint16_t delimeter, uint32_t c),
       updateDelimiter(uint16_t delimeter),
       updatePoint(uint16_t delimeter, uint8_t RED, uint8_t GREEN, uint8_t BLUE),
       updatePoint(uint16_t delimeter, uint32_t c),
       updatePoint(uint16_t delimeter),
       updateTilde(uint16_t delimeter, uint8_t RED, uint8_t GREEN, uint8_t BLUE),
	   updateTilde(uint16_t delimeter, uint32_t c),
	   updateTilde(uint16_t delimeter);

  void clear();
  void write(uint16_t digit, uint16_t pos, uint8_t RED, uint8_t GREEN, uint8_t BLUE);
  void write(uint16_t digit, uint16_t pos, uint32_t rgb);
  void write(uint16_t digit, uint16_t pos);
  //void print(String word, int pos);
  void print(String word);
  void print(String word, uint32_t rgb);
  //void print(String word, int pos, uint8_t RED, uint8_t GREEN, uint8_t BLUE);
  void print(String word, uint8_t RED, uint8_t GREEN, uint8_t BLUE);
  //void print(int num, int pos);
  void print(int16_t num, uint32_t rgb);
  void print(int16_t num);
  //void print(double num, uint32_t rgb);
  //void print(double num);
  void print(int16_t num, uint8_t RED, uint8_t GREEN, uint8_t BLUE);
  //void print(int num, int pos, uint8_t RED, uint8_t GREEN, uint8_t BLUE);
  void wheel(byte wheelPos);
  void RedToWhite(byte wheelPos);

private:
  Adafruit_NeoPixel *strip;
  // 0,1,2,3,4,5,6,7,8,9,A,b,C,d,F,G,º,-,OFF,
  /*
    '8.

    0    2
      1     3
         4
      5     7
         6    8
  */
  // then array positions 11-17 are individual segments for funz.
  byte characterMap[97] = 
    // 1234567
  {
    0b00000000,    //          32  
    0b01000000,    // !        33
    0b01010000,    // "        34
    0b01011101,    // #        35
    0b01101011,    // $        36
    0b00011100,    // %        37
    0b01111111,    // &        38
    0b00000000,    // '        39  
    0b00010001,    // (        40  
    0b01000100,    // )        41  
    0b01100000,    // *        42
    0b00011001,    // +        43
    0b00000000,    // ,        44
    0b00001000,    // -        45
    0b00000000,    // .        46
    0b00011100,    // /        47
    0b01110111,    // 0        48
    0b00010001,    // 1        49
    0b00111110,    // 2        50
    0b00111011,    // 3        51
    0b01011001,    // 4        52
    0b01101011,    // 5        53
    0b01101111,    // 6        54  
    0b00110001,    // 7        55
    0b01111111,    // 8        56
    0b01111011,    // 9        57
    0b00000000,    // :        58
    0b00000000,    // ;        59
    0b00001110,    // <        60
    0b00001010,    // =        61
    0b00001011,    // >        62
    0b00111100,    // ?        63
    0b00111111,    // @        64
    0b01111101,    // A        65
    0b01111111,    // B        66
    0b01100110,    // C        67
    0b00011111,    // D        68
    0b01101110,    // E        69
    0b01101100,    // F        70
    0b01101111,    // G        71
    0b01011101,    // H        72
    0b01000100,    // I        73
    0b00110011,    // J        74
    0b01011100,    // K        75
    0b01000110,    // L        76
    0b01110101,    // M        77
    0b01110101,    // N        78
    0b01110111,    // 0        79
    0b01111100,    // P        80
    0b01110111,    // Q        81
    0b01111100,    // R        82 
    0b01101011,    // S        83  
    0b01100100,    // T        84
    0b01010111,    // U        85
    0b01010111,    // V        86
    0b01010111,    // W        87
    0b01011101,    // X        88
    0b01011011,    // Y        89
    0b00111110,    // Z        90
    0b01100110,    // [        91
    0b01001001,    // \        92
    0b00110011,    // ]        93
    0b01110000,    // ^        94
    0b00000010,    // _        95
    0b01000000,    // `        96
    0b00111111,    // a        97
    0b01001111,    // b        98
    0b00001110,    // c        99
    0b00011111,    // d       100
    0b01111110,    // e       101
    0b01101100,    // f       102
    0b01111011,    // g       103
    0b01001101,    // h       104
    0b00000100,    // i       105
    0b00010011,    // j       106
    0b01001100,    // k       107
    0b00010001,    // l       108
    0b00001101,    // m       109
    0b00001101,    // n       110
    0b00001111,    // o       111
    0b01111100,    // p       112
    0b01111001,    // q       113
    0b00001100,    // r       114
    0b01101011,    // s       115
    0b01001110,    // t       116
    0b00000111,    // u       117
    0b00000111,    // v       118
    0b00000111,    // w       119
    0b01011101,    // x       120
    0b01011011,    // y       121
    0b00111110,    // z       122
    0b00011001,    // {       123
    0b01000100,    // |       124
    0b01001100,    // }       125
    0b00011000,    // ~       126
    0b00000000,    // [DEL]   127
    0b01111000 };   // � 		167
/*
	  0b01100111,    // Cedilla 128
      0b00000111,    // �       129
      0b01111110,    // �       130
      0b00111111,    // �       131
      0b00111111,    // �       132
      0b00111111,    // �       133
      0b00111111,    // a*      134  
      0b00001110,    // cedilla 135  
      0b01111110,    // �       136
      0b01111110,    // �       137
      0b01111110,    // �       138
      0b00000100,    // �       139
      0b00000100,    // �       140
      0b00000100,    // �       141
      0b01111101,    // �       142
      0b01111101,    // A       143
      0b01101110,    // �       144
      0b00111111,    // ae      145
      0b01101101,    // AE      146
      0b00101111,    // �       147
      0b00101111,    // �       148
      0b00101111,    // �       149  
      0b00100111,    // �       150
      0b00100111,    // �       151
      0b01011011,    // �       152
      0b01110111,    // �       153
      0b01010111,    // �       154
      0b00101010,    // �       155  
      0b01101010,    // �       156
      0b00101010,    // �       157
      0b01011101,    // �       158
      0b01101100,    // f       159
      0b00111111,    // �       160
      0b00000100,    // �       161
      0b00001111,    // �       162
      0b00000111,    // �       163
      0b00001101,    // �       164
      0b01110101,    // �       165
      0b01111000,    // �       166
      0b01111000,    // �       167
      0b00011110,    // �       168
      0b01111100,    // �       169	
      0b00001001,    // �       170
      0b01001010,    // 1/2     171
      0b01001010,    // 1/4     172
      0b00000001,    // �       173
      0b00001110,    // <<      174
      0b00000111,    // >>      175
      0b00000000,    // ::      176
      0b00001000,    // :::     177
      0b01000100,    // :|:     178
      0b01000100,    // |       179
      0b00011001,    // -|      180
      0b01111101,    // �       181
      0b01111101,    // �       182 
      0b01111101,    // �       183  
      0b01100110,    // �       184
      0b00011011,    // =|      185
      0b01010101,    // ||      186
      0b00111001,    // ��      187
      0b00010011,    // _|      188
      0b01110110,    // �       189
      0b01011011,    // �       190	<-K
      "1100110",    // �|      191
      "1001001",    // |_      192
      "0110011",    // _|_     193
      "1110000",    // �-      194
      "0000010",    // |-      195
      "1000000",    // --      196
      "0111111",    // +       197
      "1001111",    // �       198
      "0001110",    // �       199
      "0011111",    // |_|_    200
      "1111110",    //        201
      "1101100",    //        202
      "1111011",    //        203
      "1001101",    //        204
      "0000100",    //        205
      "0010011",    //        206
      "1001100",    //        207
      "0010001",    //        208
      "0001101",    //        209
      "0001101",    //        210
      "0001111",    //        211
      "1111100",    //        212
      "1111001",    //        213
      "0001100",    //        214
      "1101011",    //        215
	  "0011001",    //        216
      "0000111",    //        217
      "0000111",    //        218
      "0000111",    //        219
      "1011101",    //        220
      "1011011",    //        221
      "0111110",    //        222
      "0011001",    //        223
      "1000100",    //        224
      "1001100",    //        225
      "0011000",    //        226
      "0000000",    //        227
      "1000000",    //        228
      "1010000",    //        229
      "1011101",    //        230
      "1101011",    //        231
      "0011100",    //        232
      "1111111",    //        233
      "0010000",    //        234  
      "0010001",    //        235  
      "1000100",    //        236  
      "1100000",    //        237
      "0011001",    //        238
      "0000000",    //        239
      "0001000",    //        240
      "0000000",    //        241
      "0011100",    //        242
      "1110111",    //        243
      "0010001",    //        244
      "0111110",    //        245
      "0111011",    //        246
      "1011001",    //        247
      "1101011",    //        248
      "1101111",    //        249  
      "0110001",    //        250
      "1111111",    //        251
      "1111011",    //        252
      "1011001",    //        253
      "1101011",    //        254
	  0b00000000};   //        255  
*/    	
  const uint16_t pixPerSeg, digPerDisp, numDelims, pixPerDelim;
  byte bitmask;
};

#endif
