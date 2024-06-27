#include "PiComm.h"

PiComm::PiComm() {
  Serial.begin(115200);
}

// expected message format: 
void PiComm::handleIncomingMessages(Adafruit_NeoPixel *neoPixel, MessageHandler *handler) {
  uint8_t max_id = HANDLERS_LENGTH;
  while(available() > 0) {
    unsigned char message[MESSAGE_LENGTH];

    Serial.readBytes(message, MESSAGE_LENGTH);

    if(message[MESSAGE_LENGTH - 1] == MESSAGE_TERMINATOR) {
      LightMessage lightMessage;

      lightMessage.lightGroupID = uint8_t(message[0]);
      lightMessage.patternID = uint8_t(message[1]);
      lightMessage.variantID = message[2];
      lightMessage.options = message[3];

      handler->handleMessage(neoPixel, lightMessage);
    }
  }
}

int PiComm::available() {
  return Serial.available() / MESSAGE_LENGTH;
}