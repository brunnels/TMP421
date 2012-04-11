#include "Arduino.h"
#include <I2C.h>
#include "TMP421.h"

extern I2C I2c;

/******************************************************************************
 * Constructors
 ******************************************************************************/

/**
 * Initialize the sensor
 */
TMP421::TMP421(uint8_t addr)
{
  _address = addr;
  I2c.begin();
}

/******************************************************************************
 * Global Functions
 ******************************************************************************/

/**********************************************************
 * getIntTemp - Gets the current internal temperature from the sensor.
 *
 * @return float - The internal temperature in degrees C
 **********************************************************/
float TMP421::getIntTemp(void)
{
  uint8_t highByte = 0x00, lowByte = 0x00;

//  Wire.beginTransmission(_address);
//  Wire.write((byte)0x00);
//  Wire.endTransmission();
//  Wire.requestFrom((int)_address, 2); // request 2 byte from address 1001000
//  while(Wire.available())
//  {
//    highByte = Wire.read(); // Read the first octet
//    lowByte = Wire.read(); // Read the second octet
//  }

  I2c.write(_address, (byte) 0x00);
  I2c.read(_address, (uint8_t) 2);
  if(I2c.available()) {
    highByte = I2c.receive();
    lowByte = I2c.receive();
  }

  return getFraction(highByte, lowByte);
}

/**********************************************************
 * getIntTempF - Gets the current internal temperature from the sensor.
 *
 * @return float - The internal temperature in degrees F
 **********************************************************/
float TMP421::getIntTempF(void)
{
  return (getIntTemp() * 9 / 5 + 32);
}

/**********************************************************
 * getExtTemp - Gets the current external temperature from the sensor.
 *
 * @return float - The external temperature in degrees C
 **********************************************************/
float TMP421::getExtTemp(void)
{
  uint8_t highByte = 0x00, lowByte = 0x00;

//  I2c.beginTransmission(_address);
//  I2c.write(0x01);
//  I2c.endTransmission();
//  I2c.requestFrom((int)_address, 2); // request 2 byte from address 1001000
//  while(I2c.available())
//  {
//    highByte = I2c.read(); // Read the first octet
//    lowByte = I2c.read(); // Read the second octet
//  }

  I2c.write(_address, (byte) 0x01);
  I2c.read(_address, (uint8_t) 2);
  if(I2c.available()) {
    highByte = I2c.receive();
    lowByte = I2c.receive();
  }

  return getFraction(highByte, lowByte);
}

/**********************************************************
 * getExtTempF - Gets the current external temperature from the sensor.
 *
 * @return float - The external temperature in degrees F
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
