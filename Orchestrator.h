#pragma once
#include <stdint.h>
#include <Adafruit_NeoPixel.h>
#include "LightGroup.h"
#include "Pattern.h"

struct LightMessage {
  unsigned char lightGroupID;
  unsigned char patternID;
  unsigned char variantID;
  unsigned char options;
};

class Orchestrator {
  public:
    Orchestrator();
    virtual void registerLightGroup(unsigned char lightGroupID, LightGroup *lightGroup);
    virtual void registerPattern(unsigned char patternID, Pattern *pattern);
    virtual void handleMessage(LightMessage message);
    virtual void updateLightGroups(Adafruit_NeoPixel *neoPixel);

  protected:
    LightGroup* lightGroups[LIGHT_GROUP_COUNT];
    Pattern* patterns[PATTERN_COUNT];

    virtual LightGroup* getLightGroup(unsigned char lightGroupID);
    virtual Pattern* getPattern(unsigned char patternID);
};