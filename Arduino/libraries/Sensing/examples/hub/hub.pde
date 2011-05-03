#include <Wire.h>
#include <Sensing.h>
#include <Packet.h>

#define ADDRESS_RANGE_BEGIN	1
#define ADDRESS_RANGE_END	99

SensingHub g_hub;
bool m_heart;

// User Section: Output		     --------- --------- --------- 
void output()
{
	g_hub.SerialPrintAllNew();
}
// --------- --------- --------- --------- --------- --------- 
//////////////////////////////////////////////////////////////////////////
void setup()
{
	Serial.begin(9600);  // start serial for output
	pinMode(13, OUTPUT);
}

void loop()
{
	for (unsigned int i = ADDRESS_RANGE_BEGIN; i < ADDRESS_RANGE_END; ++i)
	{
		g_hub.CheckAddress(i);
		output();
	}

	if (m_heart)
		digitalWrite(13, HIGH);
	else
		digitalWrite(13, LOW);
	m_heart = !m_heart;
}