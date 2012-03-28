#include "Arduino.h"
#include <Wire.h>
#include "TMP421.h"

/******************************************************************************
 * Constructors
 ******************************************************************************/

/**
 * Initialize the sensor
 */
TMP421::TMP421(uint8_t addr)
{
  _address = addr;
  Wire.begin();
}

/******************************************************************************
 * Global Functions
 ******************************************************************************/

/**********************************************************
 * getIntTemp - Gets the current internal temperature from the sensor.
 *
 * @return float - The local temperature in degrees C
 **********************************************************/
float TMP421::getIntTemp(void)
{
  uint8_t highByte, lowByte;  
  
  Wire.beginTransmission(_address);
  Wire.write((byte)0x00);
  Wire.endTransmission();
  Wire.requestFrom((int)_address, 2); // request 2 byte from address 1001000
  while(Wire.available())
  {
    highByte = Wire.read(); // Read the first octet
    lowByte = Wire.read(); // Read the second octet
  }
  
  return getFraction(highByte, lowByte);
}

/**********************************************************
 * getIntTempF - Gets the current internal temperature from the sensor.
 *
 * @return float - The local temperature in degrees F
 **********************************************************/
float TMP421::getIntTempF(void)
{
  return (getIntTemp() * 9 / 5 + 32);
}

/**********************************************************
 * getExtTemp - Gets the current external temperature from the sensor.
 *
 * @return float - The local temperature in degrees C
 **********************************************************/
float TMP421::getExtTemp(void)
{
  uint8_t highByte, lowByte;  
  
  Wire.beginTransmission(_address);
  Wire.write(0x01);
  Wire.endTransmission();
  Wire.requestFrom((int)_address, 2); // request 2 byte from address 1001000
  while(Wire.available())
  {
    highByte = Wire.read(); // Read the first octet
    lowByte = Wire.read(); // Read the second octet
  }
  
  return getFraction(highByte, lowByte);
}

/**********************************************************
 * getExtTempF - Gets the current external temperature from the sensor.
 *
 * @return float - The local temperature in degrees F
 **********************************************************/
float TMP421::getExtTempF(void)
{
  return (getExtTemp() * 9 / 5 + 32);
}

/******************************************************************************
 * Private Functions
 ******************************************************************************/

float TMP421::getFraction(uint8_t highByte, uint8_t lowByte)
{
  float frac = 0.0;
  uint8_t bit;
  lowByte >>= 4; //shift-off the unused bits
  
  /* Assemble the fraction */
  bit = lowByte & 0x01;
  frac += (bit * 0.5) * (bit * 0.5) * (bit * 0.5) * (bit * 0.5);

  lowByte >>= 1;
  bit = lowByte & 0x01;
  frac += (bit * 0.5) * (bit * 0.5) * (bit * 0.5);

  lowByte >>= 1;
  bit = lowByte & 0x01;
  frac += (bit * 0.5) * (bit * 0.5);

  lowByte >>= 1;
  bit = lowByte & 0x01;
  frac += (bit * 0.5);

  /* Add the MSB to the fraction */
  frac += highByte;

  return frac;
}
