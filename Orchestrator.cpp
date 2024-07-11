#include "Orchestrator.h"

Orchestrator::Orchestrator() {}

void Orchestrator::registerLightGroup(uint8_t lightGroupID, LightGroup *lightGroup) {
  if(lightGroupID >= LIGHT_GROUP_COUNT) {
    return;
  }

  lightGroups[lightGroupID] = lightGroup;
}

void Orchestrator::registerPattern(uint8_t patternID, Pattern *pattern) {
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

  PatternData *current = group->getActivePatternData();

  if(current->patternID != message.patternID || current->variantID != message.variantID 
      || current->options != message.options) {

    // Serial.println("Pattern ID: " + current->patternID);
    // Serial.println();

    PatternData *patternData = new PatternData;
    patternData->patternID = message.patternID;
    patternData->variantID = message.variantID;
    patternData->options = message.options;

    // pattern ID is picked up correctly up to this point
    Serial.print("Pattern ID: ");
    Serial.print(patternData->patternID);
    Serial.println("....done.");


    // something bad happens here though. maybe. investigate here. 
    // also only use println once. 
    group->setPatternTimestamp(message.patternID, 0);
    group->setActivePatternData(patternData);
  }
}

void Orchestrator::updateLightGroups(Adafruit_NeoPixel *neoPixel) {
  for(int i = 0; i < LIGHT_GROUP_COUNT; i++) {
    LightGroup *group = getLightGroup(i);
    PatternData *patternData = group->getActivePatternData();
    Pattern *pattern = patternData != NULL ? getPattern(patternData->patternID): NULL;

    if (group != NULL && pattern != NULL) {
      // Serial.println("Pattern ID: " + patternData->patternID);
      pattern->updatePixels(neoPixel, group);
    }
  }
}

LightGroup* Orchestrator::getLightGroup(uint8_t lightGroupID) {
  if(lightGroupID >= LIGHT_GROUP_COUNT) {
    return NULL;
  }

  return lightGroups[lightGroupID];
}

Pattern* Orchestrator::getPattern(uint8_t patternID) {
  if(patternID >= PATTERN_COUNT) {
    return NULL;
  }
  
  return patterns[patternID];
}