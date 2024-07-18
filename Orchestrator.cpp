#include "Orchestrator.h"

Orchestrator::Orchestrator() {}

void Orchestrator::registerLightGroup(unsigned char lightGroupID, LightGroup *lightGroup) {
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

  // TODO: see if you can avoid pointers here
  PatternData current = group->getActivePatternData();

  if(current.patternID != message.patternID || current.variantID != message.variantID 
      || current.options != message.options) {

    PatternData patternData;
    patternData.patternID = message.patternID;
    patternData.variantID = message.variantID;
    patternData.options = message.options;


    // something bad happens past here though. maybe. investigate here. 
    // also only use println once. 
    group->setPatternTimestamp(message.patternID, 0);

    // TODO: see if you can avoid pointers here
    group->setActivePatternData(patternData);

    // // pattern ID is picked up correctly up to this point
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