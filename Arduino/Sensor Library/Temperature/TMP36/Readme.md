TMP36
===========
 - Type: Temperature sensor
 - Output: C - Celsus
 - Model: TMP36
 - Use: Measure Tempature (-40°C to +150°C)

Resources
---------

### Techincal Documents
- <a href="http://www.ladyada.net/media/sensors/TMP35_36_37.pdf">Manufacter's Sheet</a>

### Tutorials
- <a href="http://www.ladyada.net/learn/sensors/tmp36.html">ladyada.net</a>

Notes
-----
There are two ways to wire this one up. Looking at the flat side your pins, starting on the left.
Pin 1 - 5.0v or 3.3v
Pin 2 - Data to A0
Pin 3 - Ground

5 volts will work, but offers more noise and less acuracy. If you wire the 3.3v you must also set a line from 3.3v to your aref. Make sure your using the right code, also note there is an extra define in the defines section for 3.3v.


