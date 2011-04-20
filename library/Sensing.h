/*
Sensing.h - Library for the Sensing Platform

Created as part of the familab (www.familab.org) entry
for the 2011 Greater Global Hackerspace Challenge sponsored by element14

Copyright (c) 2011 Greater Orlando Hackerspaces, Inc.

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

#ifndef SensingNet_h
#define SensingNet_h

#include "WProgram.h"		//required by arduino libraries
#include "..\Wire\Wire.h"	//i2c library

#define PACKET_LEN 25

#define FIELD1_LEN 10 //sensor reading
#define FIELD2_LEN 5  //unit
#define FIELD3_LEN 10 //status

/*
Current Protocol Definition

8 bit characters

Field1: char[10]: Sensor Reading - can be sent in any format,
but must be padded on the wire
Field2: char[ 5]: Unit - can be sent in any format,
but must be padded on the wire
Field3: char[10]: Status - can be sent in any format,
but must be padded on the wire

Yes, this is overly simplistic, and yet verbose. Our intent is to keep this
as simple as possible for new students / makers.
If they want higher performance, they can use the wire library
directly with a custom protocol.

Example transmission:

0001.23400m/s^2     Ready
byte: 0123456789012340123456789
<-field1-><f2-><-field3->

Example transmission:

123     F
byte: 0123456789012340123456789
<-field1-><f2-><-field3->
*/

class SensingNet
{
	class SensingNet
	{ 

		class Packet{

			// +1 to allow for Null Terminator
			char m_sensorReading[FIELD1_LEN +1];
			char m_sensorUnit[FIELD2_LEN +1];
			char m_sensorStatus[FIELD3_LEN +1];

		public:
			// Default Constructor
			Packet();

			//Destructor
			virtual ~Packet(){}

			// Constructor: Parse raw packet into packet
			Packet(const char* packet)
			{
				PacketParse(packet);
			}

			// Constructor: Parse raw data into packet
			Packet(const char* reading, const char* unit, const char* status);

			// Copy Constructor
			Packet(const Packet& that);

			// Operator= Overload
			Packet operator=( Packet that);

			// Parse raw packet into packet
			void PacketParse(const char* packet);

			// Return raw packet
			char* BuildPacket();

		};
		public:
			// TODO: Everything
	};

#endif