# Google Home Timer on Sunfounder Emo Screen
Shows timers from any number of Google Home devices on <a href=https://www.amazon.com/dp/B0796PX3ZN>Sunfounder Emo</a> screen (24x8 LED matrix in pretty case with SPI controller). Acts as a clock in steady state. Uses unofficial <a href=https://rithvikvibhu.github.io/GHLocalApi/>Google Home local API</a>. Hardware components are ESP8266 and Arduino.

<img src=google.gif />
<a href=https://www.youtube.com/embed/bby7mjBw0Bw>YouTube video</a>

<h2>Software</h2>

<b>emo_nano</b> is software for Arduino Nano or similar. It acts as a controller of screen and contains pixel font.

<b>google_home_timer</b> is software for ESP8266. It sync time with NTP server (declared in NTPClient.h) and poll one or several Google Home devices through unofficial API.

Communication protocol is described in emo_nano.ino file.

<h2>Hardware</h2>

1. Any Arduino board that acts as a controller and also 3.3V-Serial to 5V-SPI converter. Arduino Nano or Arduino Pro Mini are perfect since they might be placed behind.

2. Any ESP8266, ESP01 is enough.

<i>Implementation is possible with only one controller, for example, ESP-12. But in this case voltage should be around 4V that is high end of ESP8266. With 3.3V Sunfounder Emo work is not stable.</i>

3. SunFounder 24x8 LED Dot Matrix Module - Emo.

<i>Instead of Sunfounder Emo, any LED matrix or time display like TM1637 can be used. In that case controller code should be changed.</i>

<i>ESP8266 current consumption is completely unstable, so check for proper power supply and wires. Spikes during packets interchange each second might cause nasty LED blinking.</i>

4. Optional. Brightness controller scheme. PWM brightness change seems to be impossible for Sunfounder Emo board. That's why code allows to set it only to 2 discrete values.

<h2>Schematics</h2>
<img src=schematics.png />

<h2>Limitations and known issues</h2>

* Daylight saving time (DST) is not supported yet.

* In rear cases Google Home do not respond to ESP8266 with proper list of timers. In that case clock would be shown for 1-2 seconds until proper answer would be received and timer would be shown again.

* Max timer time is 99 minutes 59 seconds, max timeout (time after timer fired but wasn't dismissed on Google Home device) is 9 minutes 59 seconds.

* Fails during NTP syncronization are not handled.
