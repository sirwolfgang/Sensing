#include <Wire.h> //needed for build order
#include <Sensing.h>

SensingNet node;

void setup()
{
  Serial.begin(9600);
  node.begin(9);

  node.setSensorUnit("m");  //The unit normally doesnt change.. 
  
}

void loop()
{
  //read your sensor
  int myint = random(999);
  float myfloat = random(9999)/(float)10000;
  myfloat += myint;
  
  //update the sensor reading...
  
  
  node.setSensorReading (myfloat, 2);
  node.setSensorStatus(String(millis()));
  
  delay(100);
}

