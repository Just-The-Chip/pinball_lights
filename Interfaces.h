#pragma once
#include <stdint.h>

class MessageHandler {
  public:
    virtual void handleMessage(uint8_t lightGroupID, uint8_t patternID, char variant, char options) = 0;
};