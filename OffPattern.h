#pragma once
#include <stdint.h>
#include <Adafruit_NeoPixel.h>
#include "Pattern.h"
#include "Lists.h"

class OffPattern : public Pattern  {
  public:
    OffPattern(unsigned char id);
    virtual void updatePixels(Adafruit_NeoPixel *neoPixel, LightGroup *group);

  protected:
    unsigned char patternID;
};