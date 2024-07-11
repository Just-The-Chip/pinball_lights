#include <stdint.h>
#include "OffPattern.h"
#include <Adafruit_NeoPixel.h>

OffPattern::OffPattern(uint8_t patternID) {
  patternID = patternID;
}

void OffPattern::updatePixels(Adafruit_NeoPixel *neoPixel, LightGroup *group) {
  uint8_t length = group->getLength();

  for(int i = 0; i < length; i++) {
    uint8_t pixelIDs = group->getPixelID(i);
    neoPixel->setPixelColor(i, 0);
  }
}