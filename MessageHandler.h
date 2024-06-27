#pragma once
#include <stdint.h>
#include <Adafruit_NeoPixel.h>
#include "LightGroup.h"
#include "Pattern.h"

struct LightMessage {
  uint8_t lightGroupID;
  uint8_t patternID;
  unsigned char variantID;
  unsigned char options;
};

class MessageHandler {
  public:
    MessageHandler();
    virtual void registerLightGroup(uint8_t lightGroupID, LightGroup *lightGroup);
    virtual void registerPattern(uint8_t patternID, Pattern *pattern);
    virtual void handleMessage(Adafruit_NeoPixel *neoPixel, LightMessage message);

  protected:
    LightGroup* lightGroups[LIGHT_GROUP_COUNT];
    Pattern* patterns[PATTERN_COUNT];

    virtual LightGroup* getLightGroup(uint8_t lightGroupID);
    virtual Pattern* getPattern(uint8_t patternID);
};