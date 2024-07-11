#include <Adafruit_NeoPixel.h>

#include "PiComm.h"
#include "Orchestrator.h"
#include "LightGroup.h"

#include "SimpleOnPattern.h"
#include "OffPattern.h"

#define FRAME_INTERVAL 1000 / 60
#define TOTAL_PIXELS 16
#define NEOPIXEL_PIN 6

unsigned long lastFrameTime;

PiComm *comm;
Orchestrator *handler;
Adafruit_NeoPixel *pixel;

OffPattern *offPat;
SimpleOnPattern *onPat;
ColorList *onPatVariants;

LightGroup *allLights;
uint8_t allPixels[TOTAL_PIXELS];

LightGroup *pop1;
uint8_t pop1Pixels[] = {0};

LightGroup *pop2;
uint8_t pop2Pixels[] = {1};

LightGroup *pop3;
uint8_t pop3Pixels = {2};

// LightGroup *slingshotL;
// uint8_t slingLPixels = {3, 4};

// LightGroup *slingshotR;
// uint8_t slingRPixels = {5, 6};

void setup() {
  pixel = new Adafruit_NeoPixel(TOTAL_PIXELS, NEOPIXEL_PIN, NEO_GRB + NEO_KHZ800);
  comm = new PiComm();
  handler = new Orchestrator();

  // patterns
  offPat = new OffPattern(0);
  handler->registerPattern(0, offPat);

  uint32_t onPatColors[3] = {pixel->Color(255, 0, 0), pixel->Color(0, 255, 0), pixel->Color(0, 0, 255)};
  onPatVariants = new ColorList(onPatColors, 3);
  onPat = new SimpleOnPattern(1, onPatVariants);
  handler->registerPattern(1, onPat);

  // light groups
  for(uint8_t i = 0; i < TOTAL_PIXELS; i++){
    allPixels[i] = i;
  }
  allLights = new LightGroup(allPixels, TOTAL_PIXELS);
  handler->registerLightGroup(0, allLights);

  pop1 = new LightGroup(pop1Pixels, 1);
  handler->registerLightGroup(1, pop1);

  pop2 = new LightGroup(pop2Pixels, 1);
  handler->registerLightGroup(2, pop2);

  pop3 = new LightGroup(pop3Pixels, 1);
  handler->registerLightGroup(3, pop3);

  pixel->begin();
}

void loop() {
  comm->handleIncomingMessages(handler);

  unsigned long currentTime = millis();
  if (currentTime >= lastFrameTime + FRAME_INTERVAL) {
    lastFrameTime = currentTime;
    handler->updateLightGroups(pixel);
    pixel->show();
  }
}
