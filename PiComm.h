#pragma once
#include <stdint.h>
#include "Arduino.h"
#include "Interfaces.h"

#define MESSAGE_TERMINATOR '\n'
#define MESSAGE_LENGTH 4
#define HANDLERS_LENGTH 15

struct PiMessage {
  uint8_t id;
  unsigned char content;
};

class PiComm : public MessageQueue {
  public:
    PiComm();
    virtual void handleIncomingMessages(MessageHandler* handlers[]);

  protected:
    virtual int available();
};