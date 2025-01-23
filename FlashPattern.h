#pragma once
#include <stdint.h>
#include <Adafruit_NeoPixel.h>
#include "Pattern.h"
#include "Lists.h"

class FlashPattern : public Pattern  {
  public:
    FlashPattern(uint8_t id, unsigned long flashInterval, ColorList* variantsList);
    virtual void updatePixels(Adafruit_NeoPixel* neoPixel, LightGroup* group);

  protected:
    uint32_t getVariantColor(unsigned char variantID);
    unsigned char getFlashCount(unsigned char options);
    unsigned long getTimestamp(LightGroup* group);

    uint8_t patternID;
    unsigned long interval;
    ColorList* variants;
};