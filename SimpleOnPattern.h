#pragma once
#include <stdint.h>
#include <Adafruit_NeoPixel.h>
#include "Pattern.h"
#include "Lists.h"

class SimpleOnPattern : public Pattern  {
  public:
    SimpleOnPattern(uint8_t patternID, ColorList* variants);
    void setVariant(char variantID);
    void setOptions(char options);
    void updatePixels(Adafruit_NeoPixel* neoPixel, LightGroup* group);

  protected:
    uint32_t getCurrentColor();

    uint8_t patternID;
    char currentVariantID;
    ColorList* variants;
};