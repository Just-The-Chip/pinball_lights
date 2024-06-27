#include <stdint.h>
#pragma once

#define PATTERN_COUNT 3
#define LIGHT_GROUP_COUNT 1

class LightGroup {
  public:
    LightGroup(int *pixelIDs, int length);
    virtual void setActivePatternID(uint8_t patternID);
    virtual unsigned long getPatternTimestamp(uint8_t patternID);
    virtual void setPatternTimestamp(uint8_t patternID, unsigned long timestamp);
    virtual uint8_t getPixelID(int index);
    virtual uint8_t getLength();

  protected:
    uint8_t pixelLength;
    uint8_t *pixelIDs;
    unsigned long patternTimestamps[PATTERN_COUNT];
    uint8_t activePatternID;
};