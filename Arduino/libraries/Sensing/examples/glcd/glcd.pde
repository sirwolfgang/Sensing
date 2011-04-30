#include <Wire.h>
#include <Sensing.h>
#include <Packet.h>
#include <ST7565.h>
#include "glcd.h"
#include "FloatToString.h"

#define ADDRESS_RANGE_BEGIN	1
#define ADDRESS_RANGE_END	99

SensingHub g_hub;

// the LCD backlight is connected up to a pin so you can turn it on & off
#define BACKLIGHT_LED 10

// pin 9 - Serial data out (SID)
// pin 8 - Serial clock out (SCLK)
// pin 7 - Data/Command select (RS or A0)
// pin 6 - LCD reset (RST)
// pin 5 - LCD chip select (CS)
ST7565 glcd(9, 8, 7, 6, 5);

#define LOGO16_GLCD_HEIGHT 16
#define LOGO16_GLCD_WIDTH  16

char m_screenbuffer[8][21];

unsigned long m_lastrefresh;

// User Section: Output		     --------- --------- --------- 
void output()
{
		if (g_hub.IsDataNew())
		{
			g_hub.SerialPrintAllLast();

 			String displayaddress = String( g_hub.GetLastAddr() );
			// Change based on datatype received
			String displayvalue;
				switch(g_hub.GetLastType())
				{
				case TYPEBOOL:
					displayvalue = String( g_hub.GetLastBool() );
					break;
				case TYPEINT:
					displayvalue = String( g_hub.GetLastInt() );
					break;
				case TYPEFLOAT:
					{
						char Floatchar[21] = {};
						floatToString( Floatchar, g_hub.GetLastFloat(), 2);
						displayvalue = String(Floatchar);
					}
					break;
				case TYPELONG:
					displayvalue = String( g_hub.GetLastLong() );
					break;
				case TYPEBYTE:
					displayvalue = String( g_hub.GetLastByte() );
					break;
				case TYPETIME:
					displayvalue = String( g_hub.GetLastTime() );
					break;
				}
			String displayunit = String( g_hub.GetLastUnit() );

			String displaystring = String( displayaddress + ": " + displayvalue + " " + displayunit );
 			//Serial.println(displaystring);

 			char tmp[21] = {};
 			displaystring.toCharArray( tmp ,21 );
 
 			for (unsigned int x = 0; x < 21; ++x)
 				m_screenbuffer[ g_hub.GetLastAddr()-8 ][x] = tmp[x];

 			if (m_lastrefresh < millis())
 			{
 				refresh();
 				m_lastrefresh = millis() + 750;
 			}
			g_hub.SetDataUsed();
		}
		
}

void refresh()
{
	glcd.clear();
 	for (unsigned int i = 0; i < 8; ++i)
 		 glcd.drawstring(0, i, m_screenbuffer[i]);
	
    glcd.display();
}
// --------- --------- --------- --------- --------- --------- 
//////////////////////////////////////////////////////////////////////////
void setup()
{
	Serial.begin(9600);  // start serial for output

	// turn on backlight
	pinMode(BACKLIGHT_LED, OUTPUT);
	digitalWrite(BACKLIGHT_LED, HIGH);

	// initialize and set the contrast to 0x18
	glcd.begin(0x18);

	glcd.clear();
	glcd.drawbitmap(0, 0, pnl_sensing_glcd_glcd_bmp, PNL_SENSING_GLCD_GLCD_WIDTH, PNL_SENSING_GLCD_GLCD_HEIGHT, BLACK);
	glcd.display(); // show splashscreen
	delay(2000);
	glcd.clear();

	for (unsigned int y = 0; y < 6; ++y)
		for (unsigned int x = 0; x < 24; ++x)
			m_screenbuffer[y][x] = ' ';

	char tmp[21] = "     Plug-N-Learn";
	for (unsigned int x = 0; x < 21; ++x)
 		m_screenbuffer[0][x] = tmp[x];

	m_lastrefresh = millis();
}

void loop()
{
	for (unsigned int i = ADDRESS_RANGE_BEGIN; i < ADDRESS_RANGE_END; ++i)
	{
		g_hub.CheckAddress(i);
		output();
	}
}
