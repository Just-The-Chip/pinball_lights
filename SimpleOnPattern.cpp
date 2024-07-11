#include <stdint.h>
#include "SimpleOnPattern.h"
#include <Adafruit_NeoPixel.h>

SimpleOnPattern::SimpleOnPattern(uint8_t patternID, ColorList* variants) {
  patternID = patternID;
  variants = variants;
}

uint32_t SimpleOnPattern::getVariantColor(unsigned char variantID) {
  uint8_t variantCount = variants->getLength();
  if(variantID >= variantCount) {
    variantID = variantID % variantCount;
  }

  return variants->getColor(variantID);
}

void SimpleOnPattern::updatePixels(Adafruit_NeoPixel* neoPixel, LightGroup* group) {
  uint8_t length = group->getLength();
  PatternData *data = group->getActivePatternData();
  uint32_t color = variants->getColor(data->variantID);
  // Serial.println(color);

  for(int i = 0; i < length; i++) {
    uint8_t pixelIDs = group->getPixelID(i);
    neoPixel->setPixelColor(i, color);
  }
}