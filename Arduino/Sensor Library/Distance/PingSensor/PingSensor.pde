#include <Wire.h>
#include <Sensing.h>
#include <Packet.h>
/*
PreDefines|    PacketType    | DataType
TYPEBOOL    1              Bool
TYPEINT        2              Int
TYPEFLOAT    3              Float
TYPELONG    4              Long int
TYPEBYTE    5              Byte
TYPETIME    6              unsigned long
*/

// User Section: Defines ---------- ---------- ---------- ---------- 
#define PACKET_TYPE 3            // Use the above table as reference
#define DATA_TYPE    float

#define DATA_UNIT    "in"        // 5 char max

#define ADDRESS_TYPE    false    // True = Preset, False = pin based
#define ADDRESS            2        // Preset Value 
#define ADDRESS_PINS    8,9,10    // Digital Pins to Address off of 
// ---------- ---------- ---------- ---------- ---------- ---------- 

const int pingPin=7;
Packet<DATA_TYPE> g_packet;

unsigned long g_timeout;
int g_stage;

// User Section: Sensor Setup        ---------- ---------- ---------- 
void input()
{
  // establish variables for duration of the ping,
  // and the distance result in inches and centimeters:
  long duration, inches, cm;

  // The PING))) is triggered by a HIGH pulse of 2 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  pinMode(pingPin, OUTPUT);
  digitalWrite(pingPin, LOW);
  delayMicroseconds(2);
  digitalWrite(pingPin, HIGH);
  delayMicroseconds(5);
  digitalWrite(pingPin, LOW);

  // The same pin is used to read the signal from the PING))): a HIGH
  // pulse whose duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode(pingPin, INPUT);
  duration = pulseIn(pingPin, HIGH);

  // convert the time into a distance
  inches = microsecondsToInches(duration);
//  Serial.println(inches);
  delay(300);
    
    g_packet.SetReading(inches);     
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
//  Serial.begin(9600);
}

void loop()
{
    input();
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

float microsecondsToInches(long microseconds)
{
  // According to Parallax's datasheet for the PING))), there are
  // 73.746 microseconds per inch (i.e. sound travels at 1130 feet per
  // second).  This gives the distance travelled by the ping, outbound
  // and return, so we divide by 2 to get the distance of the obstacle.
  // See: http://www.parallax.com/dl/docs/prod/acc/28015-PING-v1.3.pdf
  return microseconds / 74 / 2;
}