#include "PiComm.h"
#include <ArduinoQueue.h>

PiComm::PiComm() {
  Serial.begin(115200);
}

// expected message format: 
void PiComm::handleIncomingMessages(MessageHandler* handler) {
  uint8_t max_id = HANDLERS_LENGTH;
  while(available() > 0) {
    unsigned char message[MESSAGE_LENGTH];

    Serial.readBytes(message, MESSAGE_LENGTH);

    if(message[MESSAGE_LENGTH - 1] == MESSAGE_TERMINATOR) {
      uint8_t lightGroupID = uint8_t(message[0]);
      uint8_t patternID = uint8_t(message[1]);
      
      unsigned char variantID = message[2];
      unsigned char options = message[3];

      // if handler_id is within bounds of the handlers array
      if(handler_id < max_id && handlers[handler_id] != NULL) {
        handlers[handler_id]->handleMessage(handler_id, message_content);
      }
    }
  }
}

int PiComm::available() {
  return Serial.available() / MESSAGE_LENGTH;
}