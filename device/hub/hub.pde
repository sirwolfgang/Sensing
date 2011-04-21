

#include <Wire.h> //need to have first so that it gets compiled  & Defined...solution??
#include <Sensing.h>

SensingNet master;

void setup()
{
  master.begin();
  Serial.begin(9600);
}

void loop()
{
  for (int i=1; i<100; i++)
  {  
    if (master.updateNodeData(i) == 0)
    {    
      Serial.print(millis());
      Serial.print(",");
      Serial.print(i);
      Serial.print(",");
      Serial.print(master.getSensorReading());
      Serial.print(",");
      Serial.print(master.getSensorUnit());
      Serial.print(",");
      Serial.print(master.getSensorStatus());
      Serial.println("");
    }
  }
}


