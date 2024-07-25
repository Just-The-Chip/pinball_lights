#include <stdint.h>
#include "SimpleOnPattern.h"
#include <Adafruit_NeoPixel.h>

SimpleOnPattern::SimpleOnPattern(unsigned char id, ColorList* variantsList) {
  patternID = id;
  variants = variantsList;
}

uint32_t SimpleOnPattern::getVariantColor(unsigned char variantID) {
  uint8_t variantCount = variants->getLength();
  if(variantID >= variantCount) {
    // Serial.print("VARIANT ID: ");
    // Serial.print(variantID);
    // Serial.println(" ..... done");
    variantID = 0;
  }

  return variants->getColor(variantID);
}

void SimpleOnPattern::updatePixels(Adafruit_NeoPixel* neoPixel, LightGroup* group) {
  uint8_t length = group->getLength();
  PatternData data = group->getActivePatternData();
  uint32_t color = getVariantColor(data.variantID);

  for(int i = 0; i < length; i++) {
    // TODO: only set each pixel once per setting the pattern like with the Off pattern
    uint8_t pixelID = group->getPixelID(i);
    neoPixel->setPixelColor(pixelID, color);
  }
}