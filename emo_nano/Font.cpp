/**
   The MIT License (MIT)
   Copyright (c) 2019 by Ivan Tsymbaliuk

   Permission is hereby granted, free of charge, to any person obtaining a copy
   of this software and associated documentation files (the "Software"), to deal
   in the Software without restriction, including without limitation the rights
   to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
   copies of the Software, and to permit persons to whom the Software is
   furnished to do so, subject to the following conditions:
   The above copyright notice and this permission notice shall be included in all
   copies or substantial portions of the Software.
   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
   SOFTWARE.
*/

#include "Font.h"

int d0_0 = 0b01110;
int d0_1 = 0b11011;
int d0_2 = 0b11011;
int d0_3 = 0b11011;
int d0_4 = 0b11011;
int d0_5 = 0b11011;
int d0_6 = 0b01110;
int d0_7 = 0b00000;

int d1_0 = 0b00110;
int d1_1 = 0b01110;
int d1_2 = 0b00110;
int d1_3 = 0b00110;
int d1_4 = 0b00110;
int d1_5 = 0b00110;
int d1_6 = 0b00110;
int d1_7 = 0b00000;

int d2_0 = 0b01110;
int d2_1 = 0b11011;
int d2_2 = 0b00011;
int d2_3 = 0b00110;
int d2_4 = 0b01100;
int d2_5 = 0b11000;
int d2_6 = 0b11111;
int d2_7 = 0b00000;

int d3_0 = 0b01110;
int d3_1 = 0b11011;
int d3_2 = 0b00011;
int d3_3 = 0b00110;
int d3_4 = 0b00011;
int d3_5 = 0b11011;
int d3_6 = 0b01110;
int d3_7 = 0b00000;

int d4_0 = 0b00011;
int d4_1 = 0b00111;
int d4_2 = 0b01011;
int d4_3 = 0b10011;
int d4_4 = 0b11111;
int d4_5 = 0b00011;
int d4_6 = 0b00011;
int d4_7 = 0b00000;

int d5_0 = 0b11111;
int d5_1 = 0b11000;
int d5_2 = 0b11110;
int d5_3 = 0b11011;
int d5_4 = 0b00011;
int d5_5 = 0b11011;
int d5_6 = 0b01110;
int d5_7 = 0b00000;

int d6_0 = 0b01110;
int d6_1 = 0b11011;
int d6_2 = 0b11000;
int d6_3 = 0b11110;
int d6_4 = 0b11011;
int d6_5 = 0b11011;
int d6_6 = 0b01110;
int d6_7 = 0b00000;

int d7_0 = 0b11111;
int d7_1 = 0b11011;
int d7_2 = 0b00011;
int d7_3 = 0b00110;
int d7_4 = 0b01100;
int d7_5 = 0b01100;
int d7_6 = 0b01100;
int d7_7 = 0b00000;

int d8_0 = 0b01110;
int d8_1 = 0b11011;
int d8_2 = 0b11011;
int d8_3 = 0b01110;
int d8_4 = 0b11011;
int d8_5 = 0b11011;
int d8_6 = 0b01110;
int d8_7 = 0b00000;

int d9_0 = 0b01110;
int d9_1 = 0b11011;
int d9_2 = 0b11011;
int d9_3 = 0b11111;
int d9_4 = 0b00011;
int d9_5 = 0b11011;
int d9_6 = 0b01110;
int d9_7 = 0b00000;

int pl_0 = 0b00000;
int pl_1 = 0b00000;
int pl_2 = 0b00110;
int pl_3 = 0b01111;
int pl_4 = 0b01111;
int pl_5 = 0b00110;
int pl_6 = 0b00000;
int pl_7 = 0b00000;

int c1_0 = 0b00;
int c1_1 = 0b00;
int c1_2 = 0b00;
int c1_3 = 0b00;
int c1_4 = 0b00;
int c1_5 = 0b00;
int c1_6 = 0b00;
int c1_7 = 0b01;

int c2_0 = 0b00;
int c2_1 = 0b00;
int c2_2 = 0b00;
int c2_3 = 0b00;
int c2_4 = 0b00;
int c2_5 = 0b00;
int c2_6 = 0b00;
int c2_7 = 0b10;

int c1[8] = {c1_0, c1_1, c1_2, c1_3, c1_4, c1_5, c1_6, c1_7};
int c2[8] = {c2_0, c2_1, c2_2, c2_3, c2_4, c2_5, c2_6, c2_7};

int d[11][8] = {{d0_0, d0_1, d0_2, d0_3, d0_4, d0_5, d0_6, d0_7},
  {d1_0, d1_1, d1_2, d1_3, d1_4, d1_5, d1_6, d1_7},
  {d2_0, d2_1, d2_2, d2_3, d2_4, d2_5, d2_6, d2_7},
  {d3_0, d3_1, d3_2, d3_3, d3_4, d3_5, d3_6, d3_7},
  {d4_0, d4_1, d4_2, d4_3, d4_4, d4_5, d4_6, d4_7},
  {d5_0, d5_1, d5_2, d5_3, d5_4, d5_5, d5_6, d5_7},
  {d6_0, d6_1, d6_2, d6_3, d6_4, d6_5, d6_6, d6_7},
  {d7_0, d7_1, d7_2, d7_3, d7_4, d7_5, d7_6, d7_7},
  {d8_0, d8_1, d8_2, d8_3, d8_4, d8_5, d8_6, d8_7},
  {d9_0, d9_1, d9_2, d9_3, d9_4, d9_5, d9_6, d9_7},
  {pl_0, pl_1, pl_2, pl_3, pl_4, pl_5, pl_6, pl_7}
};

void fill_digits( char *buffer, int digit1, int digit2, int digit3, int digit4, int progress_or_colon )
{
  for ( int i = 0; i < 24; ++i ) buffer[i] = 0;
  for ( int i = 0; i < 7; ++i)
  {
    buffer[3 * i + 0] = (d[digit1][i] << 3) + (d[digit2][i] >> 3);
    buffer[3 * i + 1] = (d[digit2][i] << 5) + (d[digit3][i] >> 2);
    buffer[3 * i + 2] = (d[digit3][i] << 6) + (d[digit4][i]);
  }

  if ( progress_or_colon == COLON_LEFT )
    buffer[22] += c1[7] << 3;
  else if ( progress_or_colon == COLON_RIGHT )
    buffer[22] += c2[7] << 3;
  else if ( progress_or_colon >= 0 && progress_or_colon <= 24 )
  {
    buffer[21] = buffer[22] = buffer[23] = 255;
    buffer[23] <<= (24 - progress_or_colon);
    if ( 16 - progress_or_colon > 0 )
      buffer[22] <<= (16 - progress_or_colon);
    if ( 8 - progress_or_colon > 0 )
      buffer[21] <<= (8 - progress_or_colon);
  }
}
