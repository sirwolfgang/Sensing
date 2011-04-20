
SensingNet::SensingNet::Packet::Packet()
{
	for (unsigned int i = 0; i < FIELD1_LEN+1; ++i)
		m_sensorReading[i] = '\0';

	for (unsigned int i = 0; i < FIELD2_LEN+1; ++i)
		m_sensorUnit[i] = '\0';

	for (unsigned int i = 0; i < FIELD3_LEN+1; ++i)
		m_sensorStatus[i] = '\0';
}

SensingNet::SensingNet::Packet::Packet( const char* reading, const char* unit, const char* status )
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

SensingNet::SensingNet::Packet::Packet( const Packet& that )
{
	for (unsigned int i = 0; i < FIELD1_LEN +1; ++i)
		m_sensorReading[i] = that.m_sensorReading[i];

	for (unsigned int i = 0; i < FIELD2_LEN +1; ++i)
		m_sensorUnit[i] = that.m_sensorUnit[i];

	for (unsigned int i = 0; i < FIELD3_LEN +1; ++i)
		m_sensorStatus[i] = that.m_sensorStatus[i];
}

SensingNet::SensingNet::Packet SensingNet::SensingNet::Packet::operator=( Packet that )
{
	for (unsigned int i = 0; i < FIELD1_LEN +1; ++i)
		m_sensorReading[i] = that.m_sensorReading[i];

	for (unsigned int i = 0; i < FIELD2_LEN +1; ++i)
		m_sensorUnit[i] = that.m_sensorUnit[i];

	for (unsigned int i = 0; i < FIELD3_LEN +1; ++i)
		m_sensorStatus[i] = that.m_sensorStatus[i];
}

void SensingNet::SensingNet::Packet::PacketParse( const char* packet )
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

char* SensingNet::SensingNet::Packet::BuildPacket()
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
