#include <stdint.h>
#pragma once

#define PATTERN_COUNT 3
#define LIGHT_GROUP_COUNT 12

struct PatternData {
  unsigned char patternID;
  unsigned char variantID;
  unsigned char options;
  bool logPattern;
  PatternData(): logPattern(false) {}
};

class LightGroup {
  public:
    LightGroup(uint8_t *ids, uint8_t length);
    virtual void setActivePatternData(PatternData data);
    virtual PatternData getActivePatternData();
    virtual unsigned long getPatternTimestamp(unsigned char patternID);
    virtual void setPatternTimestamp(unsigned char patternID, unsigned long timestamp);
    virtual uint8_t getPixelID(int index);
    virtual uint8_t getLength();

  protected:
    uint8_t pixelLength;
    uint8_t *pixelIDs;
    unsigned long patternTimestamps[PATTERN_COUNT];
    PatternData patternData;
};