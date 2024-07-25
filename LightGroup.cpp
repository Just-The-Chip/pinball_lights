#include <stdint.h>
#include "LightGroup.h"

LightGroup::LightGroup(uint8_t *ids, uint8_t length) {
  pixelIDs = ids;
  pixelLength = length;

  for(int i = 0; i < PATTERN_COUNT; i++) {
    patternTimestamps[0] = 0;
  }
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

void LightGroup::setActivePatternData(PatternData data) {
  patternData = data;
}

PatternData LightGroup::getActivePatternData(){
  return patternData;
}

void LightGroup::setPatternTimestamp(unsigned char patternID, unsigned long timestamp) {
  patternTimestamps[patternID] = timestamp;
}

unsigned long LightGroup::getPatternTimestamp(unsigned char patternID) {
  return patternTimestamps[patternID];
}