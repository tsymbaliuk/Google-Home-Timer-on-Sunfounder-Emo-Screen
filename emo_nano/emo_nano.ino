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

// Commands come through serial port.
// Each command should end with space symbol. Unknown commands are ignored.
// List of commands
// 1. Brightness control. Each command here is just 1 symbol long:
// l - low brightness. Set screen brightness pin to LOW state.
// h - high brightness. Set screen brightness pin to HIGH state (default value).
// 0 - turn the screen off. Turns off each pixel on screen. Use command above to turn it on.
// 2. Library emos (saved images). Each command here is 2 symbols long:
// b1, b2 - blink emos
// l1, l2, l3, l4 - look emos
// s1, s2, s3 - sleepy emos
// p1, p2, p3 - pacman emos
// 3. Time commands. Each command is exactly 5 symbols long:
// <first 2 symbols><delimiter><last 2 symbols>
// <first 2 symbols> - any number from 00 to 99. First symbol might be '+'
// <delimiter> - ':' or ';' for dot shifted left or right on 8th line
//             - 'a' to 'y' for line from 0 to 24 pixels long accordingly
// <last 2 symbols> - any number from 00 to 99
// examples: "+1m23", "12:35", "01;15"

#include <SunFounder_Emo.h>
#include <emo_maps.h>
#include "Font.h"

static const int CS_PIN = 2;
static const int BRIGHTNESS_PIN = 3;

void setup() {
  pinMode(BRIGHTNESS_PIN, OUTPUT);
  digitalWrite(BRIGHTNESS_PIN, HIGH);
  Serial.begin(115200);
}

bool screen_on = true;
char screen_buf[24];
const byte *emos[] =      {blink1, blink2, look1, look2, look3, look4, sleepy1, sleepy2, sleepy3, pac_man1, pac_man2, pac_man3 };
const char *emo_names[] = {"b1",   "b2",   "l1",  "l2",  "l3",  "l4",  "s1",    "s2",    "s3",    "p1",     "p2",     "p3"     };
const char *screen_state = screen_buf;

void showScreen()
{
  static Emo emo(CS_PIN);
  if( !screen_on )
  {
    emo.show_emo(OFF);
  }
  else
  {
    emo.show_emo( screen_state );
  }
}

void loop() {
  if (Serial.available())
  {
    byte buf[32];
    int len = Serial.readBytesUntil( ' ', buf, sizeof(buf) );

    if ( len == 1 )
    {
      if ( buf[0] == 'l' )
      {
        screen_on = true;
        showScreen();
        digitalWrite(BRIGHTNESS_PIN, LOW);
      } 
      else if ( buf[0] == 'h' )
      {
        screen_on = true;
        showScreen();
        digitalWrite(BRIGHTNESS_PIN, HIGH);
      }
      else if ( buf[0] == '0' )
      {
        screen_on = false;
        showScreen();
      }
    }
    else if ( len == 2 )
    {
      for ( int i = 0; i < sizeof(emo_names) / sizeof(emo_names[0]); ++i )
      {
        if ( buf[0] == emo_names[i][0] && buf[1] == emo_names[i][1] )
        {
          screen_state = emos[i];
          showScreen();
          break;
        }
      }
    }
    else if ( len == 5 )
    {
      const int d1 = buf[0] == '+' ? PLUS_SYMBOL : buf[0] - '0';
      const int d2 = buf[1] - '0';
      const int d3 = buf[3] - '0';
      const int d4 = buf[4] - '0';

      int progress = 0;
      if ( buf[2] == ';' )
        progress = COLON_RIGHT;
      else if ( buf[2] == ':' )
        progress = COLON_LEFT;
      else
        progress = buf[2] - 'a';

      fill_digits( screen_buf, d1, d2, d3, d4, progress );
      screen_state = screen_buf;
      showScreen();
    }
  }
}
