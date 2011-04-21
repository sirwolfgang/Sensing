#include <Wire.h> //needed for Sensing Library
#include <Sensing.h>

SensingNet hub;

void setup()
{
  hub.begin();
  Serial.begin(9600);
}

void loop()
{
  for (int i=1; i<100; i++)  //scans i2c addresses from 1 to 99
  {  
    if (hub.updateNodeData(i) == 0)
    {    
      Serial.print(millis());
      Serial.print(",");
      Serial.print(i);
      Serial.print(",");
      Serial.print(hub.getSensorReading().trim());
      Serial.print(",");
      Serial.print(hub.getSensorUnit().trim());
      Serial.print(",");
      Serial.print(hub.getSensorStatus().trim());
      Serial.println("");
    }
  }
}


