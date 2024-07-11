#pragma once
#include <stdint.h>
#include <Adafruit_NeoPixel.h>
#include "Pattern.h"
#include "Lists.h"

class OffPattern : public Pattern  {
  public:
    OffPattern(uint8_t patternID);
    virtual void updatePixels(Adafruit_NeoPixel *neoPixel, LightGroup *group);

  protected:
    uint8_t patternID;
};