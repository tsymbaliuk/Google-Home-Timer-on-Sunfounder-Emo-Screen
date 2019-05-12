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

#define DEBUG 0 // Should be 0 for real usage since same serial port is used for debug and communication

#define ARDUINOJSON_USE_LONG_LONG 1

#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoOTA.h>
#include <Ticker.h>
#include <map>
#include "NTPClient.h"

const char* ssid = "<SSID>";
const char* password = "<PASSWORD>";
const String GoogleHomeIps[] = {"192.168.0.201", "192.168.0.202"};
const int time_zone = (+3);

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP);
Ticker clockUpdater;

int nearest_fire_time = INT_MAX;
int nearest_first_seen_time = INT_MAX;

// progress from 24 (just started) to 1 (almost finished)
// -1 for unknown
int currentTimerProgress()
{
  if( nearest_first_seen_time == INT_MAX || nearest_fire_time == INT_MAX )
    return -1;

  if( nearest_fire_time < timeClient.getEpochTime() )
    return -1;

  return 1+std::min(23,int((nearest_fire_time-timeClient.getEpochTime())*24/(nearest_fire_time-nearest_first_seen_time)));
}

void updateClock()
{
  static int colonState = 0;
  colonState = (colonState + 1) % 20;
  char colon = ':';
  if ( -2 + colonState / 10 == -1 )
    colon = ';';
  else
    colon = ':';

  const int time_to_go_s = nearest_fire_time == INT_MAX ? INT_MAX : nearest_fire_time - timeClient.getEpochTime();;
  int left_value, right_value;
  if ( nearest_fire_time == INT_MAX )
  {
    left_value = (timeClient.getHours() + time_zone) % 24;
    right_value = timeClient.getMinutes();
  }
  else
  {
    if ( time_to_go_s > 0 )
    {
      left_value = time_to_go_s / 60;
      right_value = time_to_go_s % 60;
      int timer_progress = currentTimerProgress();
      if ( timer_progress > 0 )
      {
        colon = 'a'+timer_progress;
      }
    }
    else
    {
      left_value = (-time_to_go_s) / 60;
      right_value = (-time_to_go_s) % 60;
    }
  }

  if ( time_to_go_s > 0 )
    Serial.print(left_value / 10);
  else
    Serial.print('+');

  Serial.print( left_value % 10 );
  Serial.print(colon);
  Serial.print( right_value / 10 );
  Serial.print( right_value % 10 );
  Serial.print(' ');
}

void setup() {
  Serial.begin(115200);
  delay(1000);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    static int progress = 0;
    delay(300);
    Serial.print("l");
    Serial.print(progress+1);
    Serial.print(" ");
    progress = (progress+1)%4;
  }

  timeClient.begin();
  timeClient.setUpdateInterval(300 * 1000);

  clockUpdater.attach(0.05, updateClock);
}

std::map<int, int> timers;
void cleanupTimers()
{
  if( timers.empty() )
    return;

  if( timers.begin()->first < timeClient.getEpochTime() )
    timers.erase(timers.begin());
}

void loop() {
  timeClient.update();

  int least_fire_time = INT_MAX;
  for ( int google_home_i = 0; google_home_i < sizeof(GoogleHomeIps) / sizeof(GoogleHomeIps[0]); ++google_home_i )
  {
    delay(1000);
    if (WiFi.status() == WL_CONNECTED)
    {
      HTTPClient http;
      http.addHeader("Content-Type", "application/json");
      http.begin("http://" + GoogleHomeIps[google_home_i] + ":8008/setup/assistant/alarms");
      http.setTimeout(1000);
      const int httpCode = http.GET();

      if (httpCode > 0) {

        String payload = http.getString();
#if DEBUG
        Serial.println(payload);
#endif

        DynamicJsonBuffer jsonBuffer(10000);
        JsonObject& root = jsonBuffer.parseObject(payload);

        JsonArray& timers_array = root["timer"];

        for ( int i = 0; i < timers_array.size(); ++i)
        {
          JsonObject& timer = timers_array[i];
          const int64_t fire_time = timer["fire_time"];
          const int fire_time_int = fire_time/1000;
          std::map<int,int>::iterator it = timers.find(fire_time_int);
          if( timeClient.getEpochTime() < fire_time_int && it == timers.end() )
          {
#if DEBUG
            Serial.print("New timer added: ");
            Serial.print(timeClient.getEpochTime());
            Serial.print(" ");
            Serial.println(fire_time_int);
#endif
            timers[fire_time_int] = timeClient.getEpochTime();
          }

          const int time_to_go = fire_time_int - timeClient.getEpochTime();
          if ( fire_time_int < least_fire_time )
            least_fire_time = fire_time_int;
        }
      }

      http.end();
    }
  }
  nearest_fire_time = least_fire_time;

  cleanupTimers();
  const std::map<int,int>::iterator it = timers.find(nearest_fire_time);
  if( it == timers.end() )
    nearest_first_seen_time = INT_MAX;
  else
    nearest_first_seen_time = it->second;
}
