#include <stdint.h>
#pragma once

#define PATTERN_COUNT 3
#define LIGHT_GROUP_COUNT 4

struct PatternData {
  uint8_t patternID;
  unsigned char variantID;
  unsigned char options;
};

class LightGroup {
  public:
    LightGroup(uint8_t *pixelIDs, uint8_t length);
    virtual void setActivePatternData(PatternData *data);
    virtual PatternData* getActivePatternData();
    virtual unsigned long getPatternTimestamp(uint8_t patternID);
    virtual void setPatternTimestamp(uint8_t patternID, unsigned long timestamp);
    virtual uint8_t getPixelID(int index);
    virtual uint8_t getLength();

  protected:
    uint8_t pixelLength;
    uint8_t *pixelIDs;
    unsigned long patternTimestamps[PATTERN_COUNT];
    PatternData *patternData;
};