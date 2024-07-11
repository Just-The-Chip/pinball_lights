#pragma once
#include <stdint.h>
#include <Adafruit_NeoPixel.h>
#include "LightGroup.h"

class Pattern {
  public:
    virtual void updatePixels(Adafruit_NeoPixel* neopixel, LightGroup* lightGroup) = 0;
};