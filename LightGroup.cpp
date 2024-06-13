#include <stdint.h>
#include "LightGroup.h"

LightGroup::LightGroup(int* pixelIDs, int length) {
  pixelIDs = pixelIDs;
  pixelLength = length;
}

uint8_t LightGroup::getPixelID(uint8_t index) {
  if(index >= pixelLength) {
    index = pixelLength - 1;
  }

  return *(pixelIDs + index);
}

uint8_t LightGroup::getLength() {
  return pixelLength;
}

void LightGroup::setActivePatternID(uint8_t patternID) {
  patternID = patternID;
}

void LightGroup::setPatternTimestamp(uint8_t patternID, unsigned long timestamp) {
  patternTimestamps[patternID] = timestamp;
}

unsigned long LightGroup::getPatternTimestamp(uint8_t patternID) {
  return patternTimestamps[patternID];
}