#include <stdint.h>
#include "FlashPattern.h"
#include <Adafruit_NeoPixel.h>

FlashPattern::FlashPattern(unsigned char id, unsigned long flashInterval, ColorList* variantsList) {
  patternID = id;
  variants = variantsList;
  interval = flashInterval;
}

uint32_t FlashPattern::getVariantColor(unsigned char variantID) {
  uint8_t variantCount = variants->getLength();
  if(variantID >= variantCount) {
    // Serial.print("VARIANT ID: ");
    // Serial.print(variantID);
    // Serial.println(" ..... done");
    variantID = 0;
  }

  return variants->getColor(variantID);
}

unsigned char FlashPattern::getFlashCount(unsigned char options) {
  // minimum flash of 1
  return options > 0 ? options : 1;
}

unsigned long FlashPattern::getTimestamp(LightGroup* group) {
  unsigned long timestamp = group->getPatternTimestamp(patternID);

  if(timestamp == 0) {
    unsigned long now = millis();
    group->setPatternTimestamp(patternID, now);
    timestamp = now;
  }

  return timestamp;
}

void FlashPattern::updatePixels(Adafruit_NeoPixel* neoPixel, LightGroup* group) {
  unsigned long timePassed = millis() - getTimestamp(group);
  unsigned long intervalCount = timePassed / interval;

  PatternData data = group->getActivePatternData();

  if(intervalCount > getFlashCount(data.options) * 2) {
    return;
  }

  uint8_t length = group->getLength();
  uint32_t color = intervalCount % 2 > 0 ? getVariantColor(data.variantID) : 0;

  for(int i = 0; i < length; i++) {
    uint8_t pixelID = group->getPixelID(i);
    neoPixel->setPixelColor(pixelID, color);
  }
}