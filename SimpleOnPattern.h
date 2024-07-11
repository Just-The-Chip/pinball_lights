#pragma once
#include <stdint.h>
#include <Adafruit_NeoPixel.h>
#include "Pattern.h"
#include "Lists.h"

class SimpleOnPattern : public Pattern  {
  public:
    SimpleOnPattern(uint8_t patternID, ColorList* variants);
    virtual void updatePixels(Adafruit_NeoPixel* neoPixel, LightGroup* group);

  protected:
    uint32_t getVariantColor(unsigned char variantID);

    uint8_t patternID;
    ColorList* variants;
};