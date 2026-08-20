#include "HardwareSerial.h"
#include "PiComm.h"

PiComm::PiComm() {
  Serial.begin(9600);
}

// expected message format: 
void PiComm::handleIncomingMessages(Orchestrator *handler) {
  while(available() > 0) {
    unsigned char message[MESSAGE_LENGTH];

    int bytesRead = Serial.readBytesUntil(MESSAGE_TERMINATOR, message, MESSAGE_LENGTH);

    if(bytesRead == (MESSAGE_LENGTH - 1)) {
      LightMessage lightMessage;

      lightMessage.lightGroupID = message[0];
      lightMessage.patternID = message[1];
      lightMessage.variantID = message[2];
      lightMessage.options = message[3];

      handler->handleMessage(lightMessage);
    } else {
      Serial.print("LIGHT BYTES READ: ");
      Serial.print(bytesRead);

      if(bytesRead >= MESSAGE_LENGTH) {
        Serial.print(", Byte0=");
        Serial.print(uint8_t(message[0]));

        Serial.print(", Byte1=");
        Serial.print(uint8_t(message[1]));

        Serial.print(", Byte2=");
        Serial.print(uint8_t(message[2]));

        Serial.print(", Byte3=");
        Serial.print(uint8_t(message[3]));

        Serial.print(", Byte4=");
        Serial.print(uint8_t(message[4]));

        int remaining_messages = available();
        flushSerialBuffer(remaining_messages * MESSAGE_LENGTH);
      } else {
        Serial.print(", msg too small ");

        for(int i = 0; i < bytesRead; i++) {
          Serial.print(", Byte");
          Serial.print(i);
          Serial.print("=");
          Serial.print(uint8_t(message[i]));
        }
        Serial.print(" --end too small msg--");


      }

      Serial.println("...end");
    }
  }
}

void PiComm::flushSerialBuffer(uint8_t flush_until = 0) {
  while(Serial.available() > flush_until) {
    char t = Serial.read();
    Serial.print(" flushed: ");
    Serial.print(uint8_t(t));
    Serial.print(", ");
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