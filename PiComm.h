#pragma once
#include <stdint.h>
#include <Adafruit_NeoPixel.h>
#include "Arduino.h"
#include "Orchestrator.h"

#define MESSAGE_TERMINATOR '\n'
#define MESSAGE_LENGTH 5

class PiComm {
  public:
    PiComm();
    virtual void handleIncomingMessages(Orchestrator *handler);

  protected:
    virtual int available();
};