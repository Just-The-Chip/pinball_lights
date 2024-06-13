#pragma once
#include <stdint.h>
#include <Adafruit_NeoPixel.h>
#include "Pattern.h"
#include "Lists.h"

class OffPattern : public Pattern  {
  public:
    OffPattern(char patternID);
    void setVariant(char variantID);
    void setOptions(char options);
    void updatePixels(Adafruit_NeoPixel* neopixel, LightGroup* group);

  protected:
    char patternID;
}