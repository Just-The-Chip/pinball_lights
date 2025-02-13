#pragma once
#include <stdint.h>
#include <Adafruit_NeoPixel.h>
#include "Pattern.h"
#include "Lists.h"

class MeterPattern : public Pattern  {
  public:
    MeterPattern(uint8_t id, ColorList* colorList);
    virtual void updatePixels(Adafruit_NeoPixel* neoPixel, LightGroup* group);

  protected:
    uint32_t getPixelColor(uint8_t index);

    uint8_t patternID;
    ColorList* colors;
};