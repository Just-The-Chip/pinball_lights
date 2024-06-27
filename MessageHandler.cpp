#include "MessageHandler.h"

MessageHandler::MessageHandler() {}

void MessageHandler::registerLightGroup(uint8_t lightGroupID, LightGroup *lightGroup) {
  if(lightGroupID >= LIGHT_GROUP_COUNT) {
    return;
  }

  lightGroups[lightGroupID] = lightGroup;
}

void MessageHandler::registerPattern(uint8_t patternID, Pattern *pattern) {
  if(patternID >= PATTERN_COUNT) {
    return;
  }

  patterns[patternID] = pattern;
}

void MessageHandler::handleMessage(Adafruit_NeoPixel *neoPixel, LightMessage message) {
  LightGroup *group = getLightGroup(message.lightGroupID);
  Pattern *pattern = getPattern(message.patternID);

  if(group == NULL || pattern == NULL) {
    return;
  }

  pattern->setVariant(message.variantID);
  pattern->setOptions(message.options);
  pattern->updatePixels(neoPixel, group);
}

LightGroup* MessageHandler::getLightGroup(uint8_t lightGroupID) {
  if(lightGroupID >= LIGHT_GROUP_COUNT) {
    return NULL;
  }

  return lightGroups[lightGroupID];
}

Pattern* MessageHandler::getPattern(uint8_t patternID) {
  if(patternID >= PATTERN_COUNT) {
    return NULL;
  }
  
  return patterns[patternID];
}