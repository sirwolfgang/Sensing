#include <Wire.h>
#include <Sensing.h>
#include <Packet.h>
/*
PreDefines|	PacketType	| DataType
TYPEBOOL	1			  Bool
TYPEINT		2			  Int
TYPEFLOAT	3			  Float
TYPELONG	4			  Long int
TYPEBYTE	5			  Byte
TYPETIME	6			  unsigned long
*/

// User Section: Defines ---------- ---------- ---------- ---------- 
#define PACKET_TYPE 2			// Use the above table as reference
#define DATA_TYPE	int

#define DATA_UNIT	"kPa"		// 5 char max

#define ADDRESS_TYPE	false	// True = Preset, False = pin based
#define ADDRESS			2		// Preset Value 
#define ADDRESS_PINS	8,9,10	// Digital Pins to Address off of 
// ---------- ---------- ---------- ---------- ---------- ---------- 

Packet<DATA_TYPE> g_packet;

unsigned long g_timeout;
int g_stage;

unsigned int pressure = 0;

// User Section: Sensor Setup	    ---------- ---------- ---------- 
void input()
{
	g_packet.SetReading(pressure);
	g_packet.SetStatus(true);
}
// ---------- ---------- ---------- ---------- ---------- ---------- 

void setup()
{
#if ADDRESS_TYPE
	SensingNodePreset(ADDRESS);
#else
	SensingNodeAddress(ADDRESS_PINS);
#endif
	g_packet.SetUnit(DATA_UNIT);

	// setup ADC
  ADMUX = B01100000;  // default to AVCC VRef, ADC Left Adjust, and ADC channel 0
  ADCSRB = B00000000; // Analog Input bank 1
  ADCSRA = B11001111; // ADC enable, ADC start, manual trigger mode, ADC interrupt enable, prescaler = 128

}

void loop()
{
	input();
}

ISR(ADC_vect)
{ // Analog->Digital Conversion Complete
  // Channel0: MAP, Channel1: AFRb1, Channel2: AFRb2
  static byte SeqIndex = 0;
  char ADCch = ADMUX & B00000111;  // extract the channel of the ADC result

  byte StdSequence[3] = {0,1,2};
  SeqIndex++;
  if (SeqIndex >= 3) SeqIndex = 0; // constrain SeqIndex
  ADMUX = (ADMUX & B11100000) + StdSequence[SeqIndex]; // set next ADC channel
  ADCSRA = B11001111;  // manually trigger the next ADC, ADC enable, ADC start, manual trigger mode, ADC interrupt enable, prescaler = 128

	// process the ADCch data (use the Left Adjusted ADC High Byte)
  if (ADCch == 0) {
    pressure = constrain(15 + ADCH, 0, 255);  // MPX4250 sensitivity 20mV/kPa.  15 kPa offset
	// MAPindex = constrain((ManifoldAirPressure - 80) >> 2, 0, BoostPressureIntervals_LookupTable-1);  // index: 0->25 = kPa: 80-180
  }

}

//////////////////////////////////////////////////////////////////////////
// Packet Sender
void SendPacket()
{
	// Tell hub the datatype
	if (g_stage == 0){
		Wire.send( PACKET_TYPE );
		g_timeout = millis() + 100;

		// IF TYPENUL, do not stage
		if (PACKET_TYPE != TYPENULL)
			g_stage = 1;
	}
	// Tell hub data
	else if (g_stage == 1) 
	{
		if (g_timeout > millis())
			Wire.send((uint8_t *)&g_packet, sizeof(g_packet));
		g_stage = 0;
	}
	// Tell Hub no data
	else if (g_stage == 3)
	{
		Wire.send( TYPENULL );
	}
}
// Initializer: Preset Address
void SensingNodePreset(unsigned int addr)
{
	g_stage = 0;
	Wire.begin((int)addr);
	Wire.onRequest( SendPacket );
}
// Initializer: Pin Based Address
void SensingNodeAddress(unsigned int pin0, unsigned int pin1, unsigned int pin2)
{
	g_stage = 0;
	// Activate Pins
	pinMode(pin0, INPUT);
	pinMode(pin1, INPUT);
	pinMode(pin2, INPUT);

	//activate internal pullup resistors
	digitalWrite(pin0, HIGH); 
	digitalWrite(pin1, HIGH);
	digitalWrite(pin2, HIGH);

	bool p0 = digitalRead(pin0), p1 = digitalRead(pin1), p2 = digitalRead(pin2);

	unsigned int plugAddr=0;

	if (!digitalRead(pin0))
		plugAddr += 1;

	if(!digitalRead(pin1))
		plugAddr += 2;

	if(!digitalRead(pin2))
		plugAddr += 4;

	Serial.print("[pinAddr]: ");
	Serial.println(plugAddr);

	Wire.begin((int)plugAddr + I2C_ADDRESS_BASE);
	Wire.onRequest( SendPacket );
}