#pragma once
#include <stdint.h>
#include <Adafruit_NeoPixel.h>
#include "LightGroup.h"

class Pattern {
  public:
    virtual void setVariant(char variantID) = 0;
    virtual void setOptions(char options) = 0;
    virtual void updatePixels(Adafruit_NeoPixel* neopixel, Lightgroup* lightGroup) = 0;
    virtual void setTimestamp(LightGroup* lightGroup) = 0;
} 