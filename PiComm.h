#pragma once
#include <stdint.h>
#include <Adafruit_NeoPixel.h>
#include "Arduino.h"
#include "Orchestrator.h"

#define MESSAGE_TERMINATOR '\n'
#define MESSAGE_LENGTH 5

struct PiMessage {
  uint8_t id;
  unsigned char content;
};

class PiComm {
  public:
    PiComm();
    virtual void handleIncomingMessages(Orchestrator *handler);

  protected:
    virtual int available();
};