#ifndef TMP421_H
#define TMP421_H

#include "Arduino.h"
#include <Wire.h>

class TMP421
{
  public:
    TMP421(uint8_t address);
    float getIntTemp(void);
    float getIntTempF(void);
    float getExtTemp(void);
    float getExtTempF(void);
    
  private:
    uint8_t _address;
    float getFraction(uint8_t highByte, uint8_t lowByte);
};

#endif