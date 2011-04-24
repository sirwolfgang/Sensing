#include "Packet.h"

template<typename Type>
Packet<Type>::Packet( Packet<Type>& packet )
{
	SetReading(packet.GetReading());
	SetUnit(packet.GetUnit());
	SetStatus(packet.GetStatus());
}

template<typename Type>
Packet<Type>::Packet( Type reading, char* unit, bool status )
{
	m_sensorReading = reading;
	for(unsigned int i = 0; i < UNIT_LEN+1; ++i)
		m_sensorUnit[i] = unit[i];
	m_sensorStatus = status;
}

template<typename Type>
Packet<Type> Packet<Type>::operator=( Packet<Type>& that )
{
	SetReading(that.GetReading());
	SetUnit(that.GetUnit());
	SetStatus(that.GetStatus());

	return *this;
}