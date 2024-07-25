#include "Orchestrator.h"

Orchestrator::Orchestrator() {}

void Orchestrator::registerLightGroup(unsigned char lightGroupID, LightGroup *lightGroup) {
  // NOTE: if the pattern sets a light group's pixels on every single frame, it has the potential to 
  // overwrite a pixel if that pixel belongs to more than one group. Patterns should be mindfu of this
  // but if it becomes an continuous issue I might have to implement some sort of priority system. 
  if(lightGroupID >= LIGHT_GROUP_COUNT) {
    return;
  }

  lightGroups[lightGroupID] = lightGroup;
}

void Orchestrator::registerPattern(unsigned char patternID, Pattern *pattern) {
  if(patternID >= PATTERN_COUNT) {
    return;
  }

  patterns[patternID] = pattern;
}

void Orchestrator::handleMessage(LightMessage message) {
  LightGroup *group = getLightGroup(message.lightGroupID);
  Pattern *pattern = getPattern(message.patternID);

  if(group == NULL || pattern == NULL) {
    return;
  }

  PatternData current = group->getActivePatternData();

  if(current.patternID != message.patternID || current.variantID != message.variantID 
      || current.options != message.options) {

    PatternData patternData;
    patternData.patternID = message.patternID;
    patternData.variantID = message.variantID;
    patternData.options = message.options;
 
    group->setPatternTimestamp(message.patternID, 0);

    group->setActivePatternData(patternData);

    // only use println once.
    // Serial.print("variant ID: ");
    // Serial.print(patternData.variantID);
    // Serial.println("....done.");
  }
}

void Orchestrator::updateLightGroups(Adafruit_NeoPixel *neoPixel) {
  for(int i = 0; i < LIGHT_GROUP_COUNT; i++) {
    LightGroup *group = getLightGroup(i);
    PatternData patternData = group->getActivePatternData();
    Pattern *pattern = getPattern(patternData.patternID);

    if (group != NULL && pattern != NULL) {
      pattern->updatePixels(neoPixel, group);
    }
  }
}

LightGroup* Orchestrator::getLightGroup(unsigned char lightGroupID) {
  if(lightGroupID >= LIGHT_GROUP_COUNT) {
    return NULL;
  }

  return lightGroups[lightGroupID];
}

Pattern* Orchestrator::getPattern(unsigned char patternID) {
  if(patternID >= PATTERN_COUNT) {
    return NULL;
  }
  
  return patterns[patternID];
}