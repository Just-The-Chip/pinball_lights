#include "Arduino.h"
#include <stdint.h>
#include "OffPattern.h"
#include <Adafruit_NeoPixel.h>

OffPattern::OffPattern(uint8_t id) {
  patternID = id;
}

void OffPattern::updatePixels(Adafruit_NeoPixel *neoPixel, LightGroup *group) {
  unsigned long timestamp = group->getPatternTimestamp(patternID);

  // pixels get turned off only once for each time the orchestrator changes to this pattern
  if(timestamp == 0) {
    uint8_t length = group->getLength();

    for(int i = 0; i < length; i++) {
      uint8_t pixelID = group->getPixelID(i);
      neoPixel->setPixelColor(pixelID, 0);
    }

    group->setPatternTimestamp(patternID, millis());
  }
}