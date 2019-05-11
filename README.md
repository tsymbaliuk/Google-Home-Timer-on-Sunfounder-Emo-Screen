# Google Home Timer on Sunfounder Emo Screen
Shows timers from any number of Google Home devices on <a href=https://www.amazon.com/dp/B0796PX3ZN>Sunfounder Emo</a> screen (24x8 LED matrix in pretty case with SPI controller). Acts as a clock in steady state. Uses unofficial <a href=https://rithvikvibhu.github.io/GHLocalApi/>Google Home local API</a>. Hardware components are ESP8266 and Arduino.

<iframe width="560" height="315" src="https://www.youtube.com/embed/bby7mjBw0Bw" frameborder="0" allow="accelerometer; autoplay; encrypted-media; gyroscope; picture-in-picture" allowfullscreen></iframe>

<h2>Hardware</h2>

1. Any Arduino board that acts as a controller and also 3.3V-Serial to 5V-SPI converter. Arduino Nano or Arduino Pro Mini are perfect since they might be placed behind.

2. Any ESP8266, ESP01 is enough.

3. Optional. Brightness controller that changes LED brightness voltage from low value to high value and takes digital value as input.

<h2>Schematics</h2>

<h2>Limitations and ways to improve</h2>

* Implementation is possible with only one controller, for example, ESP-12. But in this case voltage should be around 4V that is high end of ESP8266. With 3.3V Sunfounder Emo work is not stable.

* PWM brightness change seems to be impossible for Sunfounder Emo board. That's why code allows to set it only to 2 discrete values.

* ESP8266 current consumption is completely unstable, so check for proper power supply and wires. Spikes during packets interchange each second might cause nasty LED blinking.

* In rear cases Google Home do not respond to ESP8266 with proper list of timers. In that case clock would be shown for 1-2 seconds until proper answer would be received and timer would be shown again.

* Instead of Sunfounder Emo, any LED matrix or time display like TM1637 can be used. In that case controller code should be changed.
