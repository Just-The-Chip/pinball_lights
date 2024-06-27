#include "PiComm.h"
#include "MessageHandler.h"
#include "LightGroup.h"

#include "SimpleOnPattern.h"
#include "OffPattern.h"

PiComm *comm;
MessageHandler *handler;

void setup() {
  comm = new PiComm();
  handler = new MessageHandler();
}

void loop() {
  // put your main code here, to run repeatedly:

}
