#pragma once

#define TYPENULL	0	// Null
#define TYPEBOOL	1	// Bool
#define TYPEINT		2	// Int
#define TYPEFLOAT	3	// Float
#define TYPELONG	4	// Long int
#define TYPEBYTE	5	// Byte
#define TYPETIME	6	// unsigned long

#define UNIT_LEN	5	// Unit Char[] len

template<typename Type> class Packet{

	Type m_sensorReading;
	char m_sensorUnit[UNIT_LEN+1]; // +1 to allow for Null Terminator
	bool m_sensorStatus; // bit mask flags OR num code?

public:
	// Default Constructor
	Packet(){};

	//Destructor
	~Packet(){}

	// Copy Constructor
	// Constructor: Parse raw packet into packet
	Packet(Packet<Type>& packet);

	// Constructor: Parse raw data into packet
	Packet(Type reading, char* unit, bool status);

	// Operator= Overload
	Packet<Type> operator=(Packet<Type>& that);

	void SetReading(Type data){ m_sensorReading = data; }
	void SetUnit(char* unit)
	{
		for(unsigned int i = 0; i < UNIT_LEN; ++i)
			m_sensorUnit[i] = unit[i];
		m_sensorUnit[UNIT_LEN+1] = '\0';
	}
	void SetStatus(bool status){ m_sensorStatus = status; }

	Type GetReading(){ return m_sensorReading; }
	char* GetUnit(){ return m_sensorUnit; }
	bool GetStatus(){ return m_sensorStatus; }
};