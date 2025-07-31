#pragma once
#include <stdint.h>
#include <Adafruit_NeoPixel.h>
#include "FlashPattern.h"
#include "Lists.h"

class FlashOnPattern : public FlashPattern  {
  public:
    FlashOnPattern(uint8_t id, unsigned long flashInterval, ColorList* variantsList);

  protected:
    unsigned char getMaxInterval(unsigned char options);
};