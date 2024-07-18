#include "HardwareSerial.h"
#include "PiComm.h"

PiComm::PiComm() {
  Serial.begin(115200);
}

// expected message format: 
void PiComm::handleIncomingMessages(Orchestrator *handler) {
  while(available() > 0) {
    unsigned char message[MESSAGE_LENGTH];

    int bytesRead = Serial.readBytesUntil(MESSAGE_TERMINATOR, message, MESSAGE_LENGTH);

    if(bytesRead == 4) {
      LightMessage lightMessage;

      lightMessage.lightGroupID = message[0];
      lightMessage.patternID = message[1];
      lightMessage.variantID = message[2];
      lightMessage.options = message[3];

      // Serial.print("VARIANT NEAT: ");
      // Serial.print(lightMessage.variantID);

      handler->handleMessage(lightMessage);
    } else {
      Serial.print("BYTES READ: ");
      Serial.print(bytesRead);
      Serial.println(" INVALID MESSAGE OH NOES!");
    }
  }
}

int PiComm::available() {
  // int available =  Serial.available();

  // if(available > 0 && available < MESSAGE_LENGTH) {
  //   Serial.print("MESSAGE LENGTH: ");
  //   Serial.print(available);
  //   Serial.println(".... done");
  // }
  return Serial.available() / MESSAGE_LENGTH;
}