#include <stdint.h>
#include "SimpleOnPattern.h"
#include <Adafruit_NeoPixel.h>

SimpleOnPattern::SimpleOnPattern(uint8_t patternID, ColorList* variants) {
  patternID = patternID;
  variants = variants;
  currentVariantID = 0;
}

void SimpleOnPattern::setVariant(char variantID) {
  uint8_t variantCount = variants.getLength();
  if(variantID >= variantCount) {
    variantID = variantID % variantCount;
  }

  currentVariantID = variantID;
}

void SimpleOnPattern::setOptions(char options) {
  // do nothing
}

uint32_t SimpleOnPattern::getCurrentColor() {
  return variants.getColor(currentVariantID);
}

void SimpleOnPattern::updatePixels(Adafruit_NeoPixel* neopixel, LightGroup* group) {
  uint8_t length = group->getLength();

  for(int i = 0; i < length; i++) {
    uint8_t pixelIDs = group->getPixelID(i);
    neopixel.setPixelColor(i, getCurrentColor());
  }
}