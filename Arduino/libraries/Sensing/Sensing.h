#pragma once
#include <Wire.h>
#include "Packet.h"
#include "WProgram.h"

#define I2C_ADDRESS_BASE 10

class SensingHub 
{
	// Handling Packets
	Packet<bool> m_pbool;
	Packet<int>	 m_pint;
	Packet<float> m_pfloat;
	Packet<long> m_plong;
	Packet<byte> m_pbyte;
	Packet<unsigned long> m_ptime;

	// Last Type
	unsigned int m_Type;

	// Sensor Address of Last Read
	unsigned int m_LastAddr;

	// Is there new data?
	bool m_newdata;

public:
	// Construstor
	SensingHub();

	// Destructor
	~SensingHub(){}

	// Main Function: Check i2c for new data, at addr
	void CheckAddress(unsigned int addr);

	// Get Last data, typecasted
	bool GetLastBool();
	int GetLastInt();
	float GetLastFloat();
	long GetLastLong();
	byte GetLastByte();
	unsigned long GetLastTime();

	// Get Last Type
	int GetLastType(){ return m_Type; }
	// Get Last Unit
	char* GetLastUnit();
	// Get Last Status
	bool GetLastStatus();
	// Get the address of last data read(Last Data Transmission)
	unsigned int GetLastAddr(){ return m_LastAddr; }

	// See if data new?
	bool IsDataNew(){ return m_newdata; }
	// Set data to Used
	void SetDataUsed(){ m_newdata = false; }

	// Serial Print all NEW data
	void SerialPrintAllNew();
	// Serial Print Last Data, Any State
	void SerialPrintAllLast();

private:

	// Internals for Handling Packets
	void handleBool();
	void handleInt();
	void handleFloat();
	void handleLong();
	void handleByte();
	void handleTime();
};