/*
	Sensing.cpp - Library for the Sensing Platform
	Created as part of the familab (www.familab.org) entry
	for the 2011 Greater Global Hackerspace Challenge sponsored by element14

	Copyright (c) 2011 [TODO: OFFICIAL NAME]

	Permission is hereby granted, free of charge, to any person obtaining a copy
	of this software and associated documentation files (the "Software"), to deal
	in the Software without restriction, including without limitation the rights
	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
	copies of the Software, and to permit persons to whom the Software is
	furnished to do so, subject to the following conditions:

	The above copyright notice and this permission notice shall be included in
	all copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
	THE SOFTWARE.



*/

/*
	TODO:
	 - Addressing - 3pin?
	 - Use struct or class for packet variables / functions - extensible...

	 - Future: VARIABLE PROTOCOL: Nodes can have more than one sensor reading;
	 								Each sensor can define the length of its reading
*/




#include "Sensing.h"


class SensingNetWrapper
{
	//this class is needed to handle the callback from the wire library to a member function.
	//wrapper implementation from http://www.comp.ua.ac.be/publications/files/Adapter-Para04.pdf

	public:
		static void onQuery() { return fObj->onQuery(); }
		static void setObj (SensingNet& obj) {fObj = &obj; }

	private:
		static SensingNet* fObj;

};

SensingNet* SensingNetWrapper::fObj=NULL;

void SensingNet::begin()
{
	//to be called by hub
	hardWire.begin();
}

void SensingNet::begin(int addr)
{
	//to be called by nodes
	hardWire.begin(addr);

	//wrapper implementation (see declaration above)
	SensingNetWrapper::setObj(*this);
	hardWire.onRequest(&SensingNetWrapper::onQuery);
}

void SensingNet::begin(int pin0, int pin1, int pin2)
{

  pinMode(pin0, INPUT);
  pinMode(pin1, INPUT);
  pinMode(pin2, INPUT);

  digitalWrite(pin0, HIGH); //activate internal pullup resistors
  digitalWrite(pin1, HIGH);
  digitalWrite(pin2, HIGH);

  boolean p0 = digitalRead(pin0);
  boolean p1 = digitalRead(pin1);
  boolean p2 = digitalRead(pin2);

  int plugAddr=0;

  if (!digitalRead(pin0))
  {
    plugAddr+=1;
  }
  if(!digitalRead(pin1))
  {
    plugAddr+=2;
  }
  if(!digitalRead(pin2))
  {
    plugAddr+=4;
  }
  Serial.print("[pinAddr]:");
  Serial.println(plugAddr);

  begin(plugAddr + I2C_ADDRESS_BASE); //call the standard begin function with address

}


boolean SensingNet::updateNodeData(int id)
{
	int bytesRecv = 0;

	hardWire.requestFrom(id, PACKET_LEN);    // request bytes from node

	while(hardWire.available())    // slave may send less than requested
	{
	  char c = hardWire.receive(); // receive a byte as character

	  xmitPacket[bytesRecv] = c;
	  bytesRecv++;
	}

	if (bytesRecv > 0)
	{


		/*
		Serial.println("[updateNoteData]");
		Serial.print("[");
		Serial.print(id);
		Serial.print("]");
		Serial.print("[xmitPacket]:");
		Serial.println(xmitPacket);
		*/

		sensorReading = "";
		sensorUnit="";
		sensorStatus="";

		String xmitString(xmitPacket);
		sensorReading = xmitString.substring(0,FIELD1_LEN -1);
		//Serial.print("[und-sr]:");
		//Serial.println(sensorReading);
		sensorUnit = xmitString.substring(FIELD1_LEN,FIELD1_LEN + FIELD2_LEN - 1);
		//Serial.print("[und-su]:");
		//Serial.println(sensorUnit);
		sensorStatus = xmitString.substring(FIELD1_LEN + FIELD2_LEN,FIELD1_LEN + FIELD2_LEN + FIELD3_LEN - 1);
		//Serial.print("[und-ss]:");
		//Serial.println(sensorStatus);

		return 0; //recv data

	 }

	 return 1; //no data


}



void SensingNet::setSensorReading(float val, int precision)
{

	//found float to stringcode here:
	//http://code.google.com/p/arduino/issues/detail?id=372

	String resultString = "";
	  // Handle negative numbers
	  if (val < 0.0)
	  {
	     resultString += "-";
	     val = -val;
	  }

	  // Round correctly so that print(1.999, 2) prints as "2.00"
	  double rounding = 0.5;
	  for (uint8_t i=0; i<precision; ++i)
	    rounding /= 10.0;

	  val += rounding;

	  // Extract the integer part of the number and print it
	  unsigned long int_part = (unsigned long)val;
	  double remainder = val - (double)int_part;
	  resultString += int_part;

	  // Print the decimal point, but only if there are digits beyond
	  if (precision > 0)
	    resultString += ".";

	  // Extract digits from the remainder one at a time
	  while (precision-- > 0)
	  {
	    remainder *= 10.0;
	    int toPrint = int(remainder);
	    resultString += toPrint;
	    remainder -= toPrint;
	  }

	sensorReading = "";
	sensorReading.concat(padString(resultString, FIELD1_LEN, ' '));

	Serial.print("[ssr]:");
	Serial.println(sensorReading);

    //resultString.toCharArray(sensorReading, FIELD1_LEN);

}

void SensingNet::setSensorReading(long val)
{
	sensorReading = "";
	sensorReading.concat(padString(String(val), FIELD1_LEN, ' '));

	Serial.print("[ssr]:");
	Serial.println(sensorReading);
}

void SensingNet::setSensorReading(int val)
{
	sensorReading = "";
	sensorReading.concat(padString(String(val), FIELD1_LEN, ' '));

	Serial.print("[ssr]:");
	Serial.println(sensorReading);
}


void SensingNet::setSensorUnit(String unit)
{
	sensorUnit = "";
	sensorUnit.concat(padString(unit, FIELD2_LEN, ' '));
	Serial.print("[ssu]:");
	Serial.println(sensorUnit);

}

void SensingNet::setSensorStatus(String status)
{
	sensorStatus = "";
	sensorStatus.concat(padString(status, FIELD3_LEN, ' '));
	Serial.print("[sss]:");
	Serial.println(sensorStatus);

}

void SensingNet::onQuery() //callback function for slaves to respond when called by the master
{

	Serial.println("[onQuery]");

	//build xmitPacket

	String xmitString="";
	xmitString.concat(sensorReading);
	xmitString.concat(sensorUnit);
	xmitString.concat(sensorStatus);
	Serial.print("[xmitString]");
	Serial.println(xmitString);

	char xmitChar[PACKET_LEN+1];
	xmitString.toCharArray(xmitChar, PACKET_LEN);

	Serial.print("[xmitChar]");
	Serial.println(xmitChar);

	hardWire.send(xmitChar); //doesnt xmit the null terminator byte...

}


String SensingNet::padString(String in, int len, char pad)
{
	//todo: add left / right pad?

	String result="";

	int padAmount = len - in.length();

	//Serial.print("[pad]:");
	//Serial.println(padAmount);

	if (padAmount <1) return in;

	else
	{
		result.concat(in);
		for (int i=0; i<padAmount; i++)
		{
			result.concat(pad);
		}
	}

	return result;
}


SensingNet::Packet::Packet()
{
	for (unsigned int i = 0; i < FIELD1_LEN+1; ++i)
		m_sensorReading[i] = '\0';

	for (unsigned int i = 0; i < FIELD2_LEN+1; ++i)
		m_sensorUnit[i] = '\0';

	for (unsigned int i = 0; i < FIELD3_LEN+1; ++i)
		m_sensorStatus[i] = '\0';
}

SensingNet::Packet::Packet( const char* reading, const char* unit, const char* status )
{
	for (unsigned int i = 0; i < FIELD1_LEN; ++i)
		m_sensorReading[i] = reading[i];
	m_sensorReading[FIELD1_LEN +1] = '\0';

	for (unsigned int i = 0; i < FIELD2_LEN; ++i)
		m_sensorUnit[i] = unit[i];
	m_sensorUnit[FIELD2_LEN +1] = '\0';

	for (unsigned int i = 0; i < FIELD3_LEN; ++i)
		m_sensorStatus[i] = status[i];
	m_sensorStatus[FIELD3_LEN +1] = '\0';
}

SensingNet::Packet::Packet( const Packet& that )
{
	for (unsigned int i = 0; i < FIELD1_LEN +1; ++i)
		m_sensorReading[i] = that.m_sensorReading[i];

	for (unsigned int i = 0; i < FIELD2_LEN +1; ++i)
		m_sensorUnit[i] = that.m_sensorUnit[i];

	for (unsigned int i = 0; i < FIELD3_LEN +1; ++i)
		m_sensorStatus[i] = that.m_sensorStatus[i];
}

/*
SensingNet::Packet::operator=( Packet that )
{
	for (unsigned int i = 0; i < FIELD1_LEN +1; ++i)
		m_sensorReading[i] = that.m_sensorReading[i];

	for (unsigned int i = 0; i < FIELD2_LEN +1; ++i)
		m_sensorUnit[i] = that.m_sensorUnit[i];

	for (unsigned int i = 0; i < FIELD3_LEN +1; ++i)
		m_sensorStatus[i] = that.m_sensorStatus[i];
}
*/

void SensingNet::Packet::ParsePacket( const char* packet )
{
	for (unsigned int i = 0; i < FIELD1_LEN; ++i)
		m_sensorReading[i] = packet[i];
	m_sensorReading[FIELD1_LEN +1] = '\0';

	for (unsigned int i = 0; i < FIELD2_LEN; ++i)
		m_sensorUnit[i] = packet[i + FIELD1_LEN];
	m_sensorUnit[FIELD2_LEN +1] = '\0';

	for (unsigned int i = 0; i < FIELD3_LEN; ++i)
		m_sensorUnit[i] = packet[i + FIELD1_LEN + FIELD2_LEN];
	m_sensorStatus[FIELD3_LEN +1] = '\0';
}

char* SensingNet::Packet::GetPacket()
{
	char destination[PACKET_LEN];

	for (unsigned int i = 0; i < FIELD1_LEN; ++i)
		destination[i] = m_sensorReading[i];

	for (unsigned int i = 0; i < FIELD2_LEN; ++i)
		destination[i + FIELD1_LEN] = m_sensorUnit[i];

	for (unsigned int i = 0; i < FIELD3_LEN; ++i)
		destination[i + FIELD1_LEN + FIELD2_LEN] = m_sensorStatus[i];

	return destination;
}

void SensingNet::Packet::SetReading( const char* data )
{
	for (unsigned int i = 0; i < FIELD1_LEN; ++i)
		m_sensorReading[i] = data[i];
	m_sensorStatus[FIELD1_LEN +1] = '\0';
}

void SensingNet::Packet::SetUnit( const char* unit )
{
	for (unsigned int i = 0; i < FIELD2_LEN; ++i)
		m_sensorUnit[i] = unit[i];
	m_sensorStatus[FIELD2_LEN +1] = '\0';
}

void SensingNet::Packet::SetStatus( const char* status )
{
	for (unsigned int i = 0; i < FIELD3_LEN; ++i)
		m_sensorStatus[i] = status[i];
	m_sensorStatus[FIELD3_LEN +1] = '\0';
}