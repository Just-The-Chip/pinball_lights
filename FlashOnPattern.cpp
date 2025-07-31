#include <stdint.h>
#include "FlashOnPattern.h"
#include <Adafruit_NeoPixel.h>

FlashOnPattern::FlashOnPattern(unsigned char id, unsigned long flashInterval, ColorList* variantsList) :
  FlashPattern(id, flashInterval, variantsList) {
}

unsigned char FlashOnPattern::getMaxInterval(unsigned char options) {
  return FlashPattern::getMaxInterval(options) + 1;
}