CdS photoresistor
===========
 - Type: CdS cells, photoresistors, light dependent resistor
 - Output: Lx - Lux
 - Model:
 - Use: Detect Light

Resources
---------

### Techincal Documents
- <a href="http://www.ladyada.net/media/sensors/PDV-P8001.pdf">Manufacter's Sheet 1</a>
- <a href="http://www.ladyada.net/media/sensors/DTS_A9950_A7060_B9060.pdf">Manufacter's Sheet 2</a>

- <a href="http://www.ladyada.net/media/sensors/APP_PhotocellIntroduction.pdf">Photocell Introduction</a>
- <a href="http://www.ladyada.net/media/sensors/gde_photocellselecting.pdf">Selecting a Photocell</a>

### Tutorials
- <a href="http://www.ladyada.net/learn/sensors/cds.html">ladyada.net</a>

Notes
-----
Photoresistors are very inacturate as even two from the same batch will vary greatly. This being said, I still tryed to take Ladyada's Lux tables and use them to help calucate lux. You will need to comment/uncomment based on your pulldown resitor:
```c++
	// 10k pulldown, For Darker environments
	if (volt > 4.0){ lux = 21.824*volt*volt*volt*volt - 161.06*volt*volt*volt + 332.63*volt*volt - 167.44*volt + 13.676; }
	else { lux = 2.6213*volt*volt*volt - 7.1646*volt*volt + 5.688*volt - 0.3998; }

	// 1k pulldown, For Lighter environments
//	if (volt > 3.8){ lux = 266.29*volt*volt*volt*volt - 1673.6*volt*volt*volt + 2903.7*volt*volt - 1242.5*volt + 97.857; }
//	else { lux = 30.702*volt*volt*volt - 60.088*volt*volt + 49.035*volt - 3.3333; }
```

