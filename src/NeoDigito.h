/*
  NeoDigito.h - Library for driving NeoDigito
  large custom made 7 segment neopixel displays.
  Created and empowered by Inventoteca and Xircuitos, October 21, 2020.
*/

#ifndef NeoDigito_H
#define NeoDigito_H

#define White       1
#define Red         2
#define Green       3
#define Blue        4
#define Orange      5
#define Yellow      6
#define Cian        7
#define Pink        8
#define Purple      9

#define Rainbow     10
#define Random      11
#define Xmas        12
#define Halloween   13
#define Thunder     14
#define Drops       15
#define Fire        16
#define Sparkle     17

#include <Adafruit_NeoPixel.h>
#include <../Adafruit_NeoPixel/Adafruit_NeoPixel.h>
#include <Arduino.h>

class NeoDigito 
{
public:
  NeoDigito(uint16_t digitsPerStrip, uint16_t pixelsPerSegment, uint16_t numDelimiters, uint16_t pixPerDelimiter, uint8_t p, uint8_t t);
  NeoDigito(uint16_t digitsPerStrip, uint16_t pixelsPerSegment, uint16_t numDelimiters, uint8_t p, uint8_t t);
  NeoDigito(uint16_t digitsPerStrip, uint16_t pixelsPerSegment, uint8_t p, uint8_t t);
  NeoDigito(uint16_t digitsPerStrip, uint16_t pixelsPerSegment, uint8_t p);
  ~NeoDigito();

  void begin(),
       show(),
       setColor(uint32_t R, uint16_t G, uint8_t B),
       setColor(uint32_t c),
       setCursor(uint16_t pos),
       updateColor(uint32_t FX, uint32_t offset, uint32_t end),
       updateColor(uint32_t FX),
       updateDelimiter(uint16_t delimeter, uint8_t R, uint8_t G, uint8_t B),
       updateDelimiter(uint16_t delimeter, uint32_t c),
       updateDelimiter(uint16_t delimeter),
       updatePoint(uint16_t delimeter, uint8_t R, uint8_t G, uint8_t B),
       updatePoint(uint16_t delimeter, uint32_t c),
       updatePoint(uint16_t delimeter),
       updateTilde(uint16_t delimeter, uint8_t R, uint8_t G, uint8_t B),
	     updateTilde(uint16_t delimeter, uint32_t c),
	     updateTilde(uint16_t delimeter),
       updateDigitType(uint16_t digitsPerStrip, uint16_t pixelsPerSegment, uint16_t numDelimiters, uint16_t pixPerDelimiter),
       updateDigitType(uint16_t digitsPerStrip, uint16_t pixelsPerSegment),
       updatePixType(neoPixelType t),
       setPin(int16_t p),
       setBrightness(uint8_t br);

  void clear();
  void write(uint16_t digit, uint16_t pos, uint8_t R, uint8_t G, uint8_t B);
  void write(uint16_t digit, uint16_t pos, uint32_t rgb);
  void write(uint16_t digit, uint16_t pos);
  void print(String word);
  void print(String word, uint32_t rgb);
  void print(String word, uint8_t R, uint8_t G, uint8_t B);
  void print(int32_t num, uint8_t R, uint8_t G, uint8_t B);
  void print(int32_t num, uint32_t rgb);
  void print(int32_t num);
  //void print(double num, uint32_t rgb);
  //void print(double num);
  void wheel(byte wheelPos);
  void RedToWhite(byte wheelPos);

private:
  Adafruit_NeoPixel *strip;
  // Segment Order
  // '8.
  /*

    0    2
      1     3
         4
      5     7
         6    8


  */
  // Pixel 0 and 8 change o function.
  byte characterMap[225] = 
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
    0b00010011,    // J        74
    0b01011101,    // K        75
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
    0b01011101,    // k       107
    0b01000100,    // l       108
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
    0b01111000,    // [DEL]   127
    0b00101010,    //         128  	
	  0b01100111,    // Cedilla 129
    0b00000111,    // �       130
    0b01111110,    // �       131
    0b00111111,    // �       132
    0b00111111,    // �       133
    0b00111111,    // �       134
    0b00111111,    // a*      135  
    0b00001110,    // cedilla 136  
    0b01111110,    // �       137
    0b01111110,    // �       138
    0b01111110,    // �       139
    0b00000100,    // �       140
    0b00000100,    // �       141
    0b00000100,    // �       142
    0b01111101,    // �       143
    0b01111101,    // A       144
    0b00101101,    // Ñ       145
    0b00111111,    // ae      146
    0b01101101,    // AE      147
    0b00101111,    // �       148
    0b00101111,    // �       149
    0b00101111,    // �       150  
    0b00100111,    // �       151
    0b00100111,    // �       152
    0b01011011,    // �       153
    0b01110111,    // �       154
    0b01010111,    // �       155
    0b00101010,    // �       156  
    0b01101010,    // �       157
    0b00101010,    // �       158
    0b01011101,    // �       159
    0b01101100,    // f       160
    0b00111111,    // �       161
    0b00000100,    // �       162
    0b00001111,    // �       163
    0b00000111,    // �       164
    0b00001101,    // �       165
    0b01110101,    // �       166
    0b01111000,    // �       167
    0b01111000,    // �       168
    0b01111110,    // é       169
    0b01111100,    // �       170	
    0b00001001,    // �       171
    0b01001010,    // 1/2     172
    0b01001010,    // 1/4     173
    0b00000001,    // �       174
    0b00001110,    // <<      175
    0b00000111,    // >>      176
    0b00101101,    // ñ      177
    0b00001000,    // :::     178
    0b01000100,    // :|:     179
    0b01000100,    // |       180
    0b00011001,    // -|      181
    0b01111101,    // �       182
    0b01111101,    // �       183 
    0b01111101,    // �       184  
    0b01100110,    // �       185
    0b01111000,    // =|      186
    0b01111111,    // ||      187
    0b00111001,    // ��      188
    0b00010011,    // _|      189
    0b01110110,    // �       190
    0b00011110,    // ¿       191	
    0b01100110,  // 192
    0b01001001,  // 193
    0b00110011,  // 194
    0b01110000,  // 195
    0b00000010,  // 196
    0b01000000,  // 197
    0b00111111,  // 198
    0b01001111,  // 199
    0b00001110,  // 200
    0b00011111,  // 201
    0b01111110,  // 202
    0b01101100,  // 203
    0b01111011,  // 204
    0b01001101,  // 205
    0b00000100,  // 206
    0b00010011,  // 207
    0b01001100,  // 208
    0b00010001,  // 209
    0b00001101,  // 210
    0b00001101,  // 211
    0b00001111,  // 212
    0b01111100,  // 213
    0b01111001,  // 214
    0b00001100,  // 215
    0b01101011,  // 216
    0b00011001,  // 217
    0b00000111,  // 218
    0b00000111,  // 219
    0b00000111,  // 220
    0b01011101,  // 221
    0b01011011,  // 222
    0b00111110,  // 223
    0b00011001,  // 224
    0b01000100,  // 225
    0b01001100,  // 226
    0b00011000,  // 227
    0b00000000,  // 228
    0b01000000,  // 229
    0b01010000,  // 230
    0b01011101,  // 231
    0b01101011,  // 232
    0b00011100,  // 233
    0b01111111,  // 234
    0b00010000,  // 235
    0b00010001,  // 236
    0b01000100,  // 237
    0b01100000,  // 238
    0b00011001,  // 239
    0b00000000,  // 240
    0b00001000,  // 241
    0b00000000,  // 242
    0b00011100,  // 243
    0b01110111,  // 244
    0b00010001,  // 245
    0b00111110,  // 246
    0b00111011,  // 247
    0b01011001,  // 248
    0b01101011,  // 249
    0b01101111,  // 250
    0b00110001,  // 251
    0b01111111,  // 252
    0b01111011,  // 253
    0b01011001,  // 254
    0b01101011,  // 255
    0b00000000   // 256
};               //     
   	
  uint16_t pixPerSeg, digPerDisp, numDelims, pixPerDelim;
  byte bitmask;
};

#endif
