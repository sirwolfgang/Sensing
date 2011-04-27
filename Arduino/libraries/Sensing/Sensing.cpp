#include "Sensing.h"

SensingHub::SensingHub()
{
	Wire.begin();
}

void SensingHub::CheckAddress( unsigned int addr )
{
	Wire.requestFrom(addr, 1);    // request 1 bytes from slave device

	if ((int)Wire.available() == 1)
	{
		int type = Wire.receive();
		
		switch(type)
		{
		case TYPENULL:
			break;
		case TYPEBOOL:
			m_Type = TYPEBOOL;
			m_LastAddr = addr;
			m_newdata = true;
			handleBool();
			break;
		case TYPEINT:
			m_Type = TYPEINT;
			m_LastAddr = addr;
			m_newdata = true;
			handleInt();
			break;
		case TYPEFLOAT:
			m_Type = TYPEFLOAT;
			m_LastAddr = addr;
			m_newdata = true;
			handleFloat();
			break;
		case TYPELONG:
			m_Type = TYPELONG;
			m_LastAddr = addr;
			m_newdata = true;
			handleLong();
			break;
		case TYPEBYTE:
			m_Type = TYPEBYTE;
			m_LastAddr = addr;
			m_newdata = true;
			handleByte();
			break;
		case TYPETIME:
			m_Type = TYPETIME;
			m_LastAddr = addr;
			m_newdata = true;
			handleTime();
			break;
		default:
			Serial.print("Node ");
			Serial.print( addr );
			Serial.println(": ERROR");
			break;
		}
	}
}

bool SensingHub::GetLastBool()
{
	switch(m_Type)
	{
	case TYPEBOOL:
		return (bool)m_pbool.GetReading();
		break;
	case TYPEINT:
		return (bool)m_pint.GetReading();
		break;
	case TYPEFLOAT:
		return (bool)m_pfloat.GetReading();
		break;
	case TYPELONG:
		return (bool)m_plong.GetReading();
		break;
	case TYPEBYTE:
		return (bool)m_pbyte.GetReading();
		break;
	case TYPETIME:
		return (bool)m_ptime.GetReading();
		break;
	}
}

int SensingHub::GetLastInt()
{
	switch(m_Type)
	{
	case TYPEBOOL:
		return (int)m_pbool.GetReading();
		break;
	case TYPEINT:
		return (int)m_pint.GetReading();
		break;
	case TYPEFLOAT:
		return (int)m_pfloat.GetReading();
		break;
	case TYPELONG:
		return (int)m_plong.GetReading();
		break;
	case TYPEBYTE:
		return (int)m_pbyte.GetReading();
		break;
	case TYPETIME:
		return (int)m_ptime.GetReading();
		break;
	}
}

float SensingHub::GetLastFloat()
{
	switch(m_Type)
	{
	case TYPEBOOL:
		return (float)m_pbool.GetReading();
		break;
	case TYPEINT:
		return (float)m_pint.GetReading();
		break;
	case TYPEFLOAT:
		return (float)m_pfloat.GetReading();
		break;
	case TYPELONG:
		return (float)m_plong.GetReading();
		break;
	case TYPEBYTE:
		return (float)m_pbyte.GetReading();
		break;
	case TYPETIME:
		return (float)m_ptime.GetReading();
		break;
	}
}

long SensingHub::GetLastLong()
{
	switch(m_Type)
	{
	case TYPEBOOL:
		return (long)m_pbool.GetReading();
		break;
	case TYPEINT:
		return (long)m_pint.GetReading();
		break;
	case TYPEFLOAT:
		return (long)m_pfloat.GetReading();
		break;
	case TYPELONG:
		return (long)m_plong.GetReading();
		break;
	case TYPEBYTE:
		return (long)m_pbyte.GetReading();
		break;
	case TYPETIME:
		return (long)m_ptime.GetReading();
		break;
	}
}

byte SensingHub::GetLastByte()
{
	switch(m_Type)
	{
	case TYPEBOOL:
		return (byte)m_pbool.GetReading();
		break;
	case TYPEINT:
		return (byte)m_pint.GetReading();
		break;
	case TYPEFLOAT:
		return (byte)m_pfloat.GetReading();
		break;
	case TYPELONG:
		return (byte)m_plong.GetReading();
		break;
	case TYPEBYTE:
		return (byte)m_pbyte.GetReading();
		break;
	case TYPETIME:
		return (byte)m_ptime.GetReading();
		break;
	}
}

unsigned long SensingHub::GetLastTime()
{
	switch(m_Type)
	{
	case TYPEBOOL:
		return (unsigned long)m_pbool.GetReading();
		break;
	case TYPEINT:
		return (unsigned long)m_pint.GetReading();
		break;
	case TYPEFLOAT:
		return (unsigned long)m_pfloat.GetReading();
		break;
	case TYPELONG:
		return (unsigned long)m_plong.GetReading();
		break;
	case TYPEBYTE:
		return (unsigned long)m_pbyte.GetReading();
		break;
	case TYPETIME:
		return (unsigned long)m_ptime.GetReading();
		break;
	}
}

char* SensingHub::GetLastUnit()
{
	switch(m_Type)
	{
	case TYPEBOOL:
		return m_pbool.GetUnit();
		break;
	case TYPEINT:
		return m_pint.GetUnit();
		break;
	case TYPEFLOAT:
		return m_pfloat.GetUnit();
		break;
	case TYPELONG:
		return m_plong.GetUnit();
		break;
	case TYPEBYTE:
		return m_pbyte.GetUnit();
		break;
	case TYPETIME:
		return m_ptime.GetUnit();
		break;
	}
}

bool SensingHub::GetLastStatus()
{
	switch(m_Type)
	{
	case TYPEBOOL:
		return m_pbool.GetStatus();
		break;
	case TYPEINT:
		return m_pint.GetStatus();
		break;
	case TYPEFLOAT:
		return m_pfloat.GetStatus();
		break;
	case TYPELONG:
		return m_plong.GetStatus();
		break;
	case TYPEBYTE:
		return m_pbyte.GetStatus();
		break;
	case TYPETIME:
		return m_ptime.GetStatus();
		break;
	}
}

void SensingHub::SerialPrintAllNew()
{
	if (m_newdata)
	{
		SerialPrintAllLast();
	}
}

void SensingHub::SerialPrintAllLast()
{
	Serial.print( millis() );
	Serial.print( "," );
	Serial.print( m_LastAddr );
	Serial.print( "," );

	// Change based on datatype received
	switch(m_Type)
	{
	case TYPEBOOL:
		Serial.print( GetLastBool() );
		break;
	case TYPEINT:
		Serial.print( GetLastInt() );
		break;
	case TYPEFLOAT:
		Serial.print( GetLastFloat() );
		break;
	case TYPELONG:
		Serial.print( GetLastLong() );
		break;
	case TYPEBYTE:
		Serial.print( GetLastByte() );
		break;
	case TYPETIME:
		Serial.print( GetLastTime() );
		break;
	}

	Serial.print( "," );
	Serial.print( GetLastUnit() );
	Serial.print( "," );
	Serial.println( GetLastStatus() );
	m_newdata = false;
}

void SensingHub::handleBool()
{
	Wire.requestFrom((int)m_LastAddr, sizeof(Packet<bool>));
	if ( (int)sizeof(Packet<bool>) != (int)Wire.available() )
	{
		Serial.println("Packet Malformed");
		return;
	}

	byte buffer[sizeof(Packet<bool>)] = {};

	for (unsigned int i = 0; i < sizeof(Packet<bool>); ++i)
		buffer[i] = (byte)Wire.receive();

	memcpy(&m_pbool, buffer, sizeof(Packet<bool>));
}

void SensingHub::handleInt()
{
	Wire.requestFrom((int)m_LastAddr, sizeof(Packet<int>));
	if ( (int)sizeof(Packet<int>) != (int)Wire.available() )
	{
		Serial.println("Packet Malformed");
		return;
	}

	byte buffer[sizeof(Packet<int>)] = {};

	for (unsigned int i = 0; i < sizeof(Packet<int>); ++i)
		buffer[i] = (byte)Wire.receive();

	memcpy(&m_pint, buffer, sizeof(Packet<int>));
}

void SensingHub::handleFloat()
{
	Wire.requestFrom((int)m_LastAddr, sizeof(Packet<float>));
	if ( (int)sizeof(Packet<float>) != (int)Wire.available() )
	{
		Serial.println("Packet Malformed");
		return;
	}

	byte buffer[sizeof(Packet<float>)] = {};

	for (unsigned int i = 0; i < sizeof(Packet<float>); ++i)
		buffer[i] = (byte)Wire.receive();

	memcpy(&m_pfloat, buffer, sizeof(Packet<float>));
}

void SensingHub::handleLong()
{
	Wire.requestFrom((int)m_LastAddr, sizeof(Packet<long>));
	if ( (int)sizeof(Packet<long>) != (int)Wire.available() )
	{
		Serial.println("Packet Malformed");
		return;
	}

	byte buffer[sizeof(Packet<long>)] = {};

	for (unsigned int i = 0; i < sizeof(Packet<long>); ++i)
		buffer[i] = (byte)Wire.receive();

	memcpy(&m_plong, buffer, sizeof(Packet<long>));
}

void SensingHub::handleByte()
{
	Wire.requestFrom((int)m_LastAddr, sizeof(Packet<byte>));
	if ( (int)sizeof(Packet<byte>) != (int)Wire.available() )
	{
		Serial.println("Packet Malformed");
		return;
	}

	byte buffer[sizeof(Packet<byte>)] = {};

	for (unsigned int i = 0; i < sizeof(Packet<byte>); ++i)
		buffer[i] = (byte)Wire.receive();

	memcpy(&m_pbyte, buffer, sizeof(Packet<byte>));
}

void SensingHub::handleTime()
{
	Wire.requestFrom((int)m_LastAddr, sizeof(Packet<unsigned long>));
	if ( (int)sizeof(Packet<unsigned long>) != (int)Wire.available() )
	{
		Serial.println("Packet Malformed");
		return;
	}

	byte buffer[sizeof(Packet<unsigned long>)] = {};

	for (unsigned int i = 0; i < sizeof(Packet<unsigned long>); ++i)
		buffer[i] = (byte)Wire.receive();

	memcpy(&m_ptime, buffer, sizeof(Packet<unsigned long>));
}
