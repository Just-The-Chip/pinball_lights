#pragma once
#include <stdint.h>
#include <Adafruit_NeoPixel.h>
#include "Arduino.h"
#include "MessageHandler.h"

#define MESSAGE_TERMINATOR '\n'
#define MESSAGE_LENGTH 4
#define HANDLERS_LENGTH 15

struct PiMessage {
  uint8_t id;
  unsigned char content;
};

class PiComm {
  public:
    PiComm();
    virtual void handleIncomingMessages(Adafruit_NeoPixel *neopixel, MessageHandler *handler);

  protected:
    virtual int available();
};