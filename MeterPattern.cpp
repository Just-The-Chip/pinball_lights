#include <stdint.h>
#include "MeterPattern.h"
#include <Adafruit_NeoPixel.h>

MeterPattern::MeterPattern(unsigned char id, ColorList* colorList) {
  patternID = id;
  colors = colorList;
}

uint32_t MeterPattern::getPixelColor(uint8_t index) {
  uint8_t colorCount = index % colors->getLength();

  return colors->getColor(index);
}

void MeterPattern::updatePixels(Adafruit_NeoPixel* neoPixel, LightGroup* group) {
  uint8_t length = group->getLength();
  PatternData data = group->getActivePatternData();
  
  for(int i = 0; i < length; i++) {
    // TODO: only set each pixel once per setting the pattern like with the Off pattern
    uint8_t pixelID = group->getPixelID(i);

    uint32_t color = data.options <= i ? getPixelColor(i) : 0;
    neoPixel->setPixelColor(pixelID, color);
  }
}