#include <stdint.h>
#pragma once

#define PATTERN_COUNT 8
#define LIGHT_GROUP_COUNT 28

struct PatternData {
  unsigned char patternID;
  unsigned char variantID;
  unsigned char options;
  bool logPattern;
  bool isPatternComplete;
  unsigned long timestamp;
  PatternData(): logPattern(false), isPatternComplete(false), timestamp(0) {}
};

class LightGroup {
  public:
    LightGroup(uint8_t *ids, uint8_t length);
    virtual void setActivePatternData(PatternData data);
    virtual PatternData getActivePatternData();
    virtual unsigned long getPatternTimestamp();
    virtual void setPatternTimestamp(unsigned long timestamp);
    virtual uint8_t getPixelID(int index);
    virtual uint8_t getLength();
    //TODO: getters and setters for other PaternData values

  protected:
    uint8_t pixelLength;
    uint8_t *pixelIDs;
    // unsigned long patternTimestamps[PATTERN_COUNT];
    PatternData patternData;
};