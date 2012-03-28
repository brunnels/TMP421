#include <Wire.h>
#include <TMP421.h>
TMP421 temp = TMP421(0x4C);

void setup() 
{
  Serial.begin(9600);
}

void loop() 
{
  float intTemp = temp.getIntTemp(); // Get local temperature in Celcius degree
  float extTemp = temp.getExtTemp(); // Get remote temperature in Celcius degree
  Serial.print("Local Temp = ");
  Serial.print(intTemp,DEC);
  Serial.print(" C  ");
  Serial.print("Remote Temp = ");
  Serial.print(extTemp,DEC);
  Serial.println(" C");
  
  float intTempF = temp.getIntTempF();// Get local temperature in Fahrenheit degree
  float extTempF = temp.getExtTempF();// Get remote temperature in Fahrenheit degree
  Serial.print("Local Temp = ");
  Serial.print(intTempF,DEC);
  Serial.print(" F  ");
  Serial.print("Remote Temp = ");
  Serial.print(extTempF,DEC);
  Serial.println(" F");
  
  delay(1000);
}