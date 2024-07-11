#include <stdint.h>
#include "LightGroup.h"

LightGroup::LightGroup(uint8_t *pixelIDs, uint8_t length) {
  pixelIDs = pixelIDs;
  pixelLength = length;
}

uint8_t LightGroup::getPixelID(int index) {
  if(index >= pixelLength) {
    index = pixelLength - 1;
  }

  return *(pixelIDs + index);
}

uint8_t LightGroup::getLength() {
  return pixelLength;
}

void LightGroup::setActivePatternData(PatternData *data) {
  patternData = data;
}

PatternData* LightGroup::getActivePatternData(){
  return patternData;
}

void LightGroup::setPatternTimestamp(uint8_t patternID, unsigned long timestamp) {
  patternTimestamps[patternID] = timestamp;
}

unsigned long LightGroup::getPatternTimestamp(uint8_t patternID) {
  return patternTimestamps[patternID];
}