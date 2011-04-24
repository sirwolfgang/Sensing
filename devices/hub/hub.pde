#include <Wire.h>
#include <Sensing.h>
#include <Packet.h>

#define ADDRESS_RANGE_BEGIN	1
#define ADDRESS_RANGE_END	99

SensingHub g_hub;

// User Section: Output
void output()
{
	g_hub.SerialPrintAllNew();
}

//////////////////////////////////////////////////////////////////////////
void setup()
{
	Serial.begin(9600);  // start serial for output
}

void loop()
{
	for (unsigned int i = ADDRESS_RANGE_BEGIN; i < ADDRESS_RANGE_END; ++i)
	{
		g_hub.CheckAddress(i);
		output();
	}
}