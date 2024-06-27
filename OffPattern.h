#pragma once
#include <stdint.h>
#include <Adafruit_NeoPixel.h>
#include "Pattern.h"
#include "Lists.h"

class OffPattern : public Pattern  {
  public:
    OffPattern(uint8_t patternID);
    void setVariant(char variantID);
    void setOptions(char options);
    void updatePixels(Adafruit_NeoPixel *neoPixel, LightGroup *group);

  protected:
    char patternID;
};