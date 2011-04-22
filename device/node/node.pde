#include <Wire.h> //needed for build order
#include <Sensing.h>

SensingNet node;

void setup()
{
  Serial.begin(9600);
  node.begin(5);

  node.setSensorUnit("m");  //The unit normally doesnt change.. 
  
}

void loop()
{
  //read your sensor & send reading (float example)
  /* 
  int myint = random(999);
  float myfloat = random(9999)/(float)10000;
  myfloat += myint;
  node.setSensorReading (myfloat, 2);
  */
  
  //read your sensor & send reading (long example)
  /*
  long mylong = random(9999999);
  node.setSensorReading (mylong);
  */
  
  //read your sensor & send reading (int example)
  
  int myint = random(9999);
  node.setSensorReading (myint);
  
  
  
  node.setSensorStatus(String(millis()));
  
  delay(100);
}

