#include <Adafruit_NeoPixel.h>

#include "PiComm.h"
#include "Orchestrator.h"
#include "LightGroup.h"

#include "SimpleOnPattern.h"
#include "OffPattern.h"

#define FRAME_INTERVAL 1000 / 30
#define TOTAL_PIXELS 20
#define NEOPIXEL_PIN 6

unsigned long lastFrameTime;

PiComm *comm;
Orchestrator *handler;
Adafruit_NeoPixel *pixel;

OffPattern *offPat;

static uint32_t onPatColors[4];
SimpleOnPattern *onPat;
ColorList *onPatVariants;

static uint32_t specialOnPatColors[4];
SimpleOnPattern *specialOnPat;
ColorList *specialOnPatVariants;


static uint8_t allPixels[TOTAL_PIXELS];
LightGroup *allLights;

static uint8_t pop1Pixels[1];
LightGroup *pop1;

static uint8_t pop2Pixels[1];
LightGroup *pop2;

static uint8_t pop3Pixels[1];
LightGroup *pop3;

static uint8_t slingLPixels[2];
LightGroup *slingshotL;

static uint8_t slingRPixels[2];
LightGroup *slingshotR;

static uint8_t magSwitch1Pixels[1];
LightGroup *magSwitch1;

static uint8_t magSwitch2Pixels[1];
LightGroup *magSwitch2;

static uint8_t magSwitch3Pixels[1];
LightGroup *magSwitch3;

static uint8_t magSwitch4Pixels[1];
LightGroup *magSwitch4;

void setup() {
  pixel = new Adafruit_NeoPixel(TOTAL_PIXELS, NEOPIXEL_PIN, NEO_GRB + NEO_KHZ800);
  comm = new PiComm();
  handler = new Orchestrator();

  // patterns
  offPat = new OffPattern(0);
  handler->registerPattern(0, offPat);

  onPatColors[0] = pixel->Color(255, 0, 0);
  onPatColors[1] = pixel->Color(0, 255, 0);
  onPatColors[2] = pixel->Color(0, 255, 255);
  onPatColors[3] = pixel->Color(0, 0, 255);
  onPatVariants = new ColorList(onPatColors, 4);
  onPat = new SimpleOnPattern(1, onPatVariants);
  handler->registerPattern(1, onPat);

  specialOnPatColors[0] = pixel->Color(255, 0, 255);
  specialOnPatColors[1] = pixel->Color(255, 255, 0);
  specialOnPatColors[2] = pixel->Color(0, 255, 255);
  specialOnPatColors[3] = pixel->Color(128, 0, 255);
  specialOnPatVariants = new ColorList(specialOnPatColors, 4);
  specialOnPat = new SimpleOnPattern(2, specialOnPatVariants);
  handler->registerPattern(2, specialOnPat);

  PatternData defaultPattern;
  defaultPattern.patternID = 0;
  defaultPattern.options = 0;
  defaultPattern.variantID = 0;

  // light groups
  for(uint8_t i = 0; i < TOTAL_PIXELS; i++){
    allPixels[i] = i;
  }
  allLights = new LightGroup(allPixels, TOTAL_PIXELS);
  handler->registerLightGroup(0, allLights);
  allLights->setActivePatternData(defaultPattern);

  pop1Pixels[0] = 0;
  pop1 = new LightGroup(pop1Pixels, 1);
  handler->registerLightGroup(1, pop1);
  pop1->setActivePatternData(defaultPattern);

  pop2Pixels[0] = 1;
  pop2 = new LightGroup(pop2Pixels, 1);
  handler->registerLightGroup(2, pop2);
  pop2->setActivePatternData(defaultPattern);

  pop3Pixels[0] = 2;
  pop3 = new LightGroup(pop3Pixels, 1);
  handler->registerLightGroup(3, pop3);
  pop3->setActivePatternData(defaultPattern);

  slingLPixels[0] = 5;
  slingLPixels[1] = 6;
  slingshotL = new LightGroup(slingLPixels, 2);
  handler->registerLightGroup(4, slingshotL);
  slingshotL->setActivePatternData(defaultPattern);

  slingRPixels[0] = 3;
  slingRPixels[1] = 4;
  slingshotR = new LightGroup(slingRPixels, 2);
  handler->registerLightGroup(5, slingshotR);
  slingshotR->setActivePatternData(defaultPattern);

  magSwitch1Pixels[0] = 16;
  magSwitch1 = new LightGroup(magSwitch1Pixels,1);
  handler->registerLightGroup(6,magSwitch1);
  magSwitch1->setActivePatternData(defaultPattern);

  magSwitch2Pixels[0] = 17;
  magSwitch2 = new LightGroup(magSwitch2Pixels,1);
  handler->registerLightGroup(7,magSwitch2);
  magSwitch2->setActivePatternData(defaultPattern);

  magSwitch3Pixels[0] = 18;
  magSwitch3 = new LightGroup(magSwitch3Pixels,1);
  handler->registerLightGroup(8,magSwitch3);
  magSwitch3->setActivePatternData(defaultPattern);

  magSwitch4Pixels[0] = 19;
  magSwitch4 = new LightGroup(magSwitch4Pixels,1);
  handler->registerLightGroup(9,magSwitch4);
  magSwitch4->setActivePatternData(defaultPattern);

  pixel->begin();
  // pixel->clear();

  // this is, like, a sanity check or something
  for(uint8_t i = 0; i < TOTAL_PIXELS; i++) {
    pixel->setPixelColor(i, pixel->Color(255, 255, 0));
    pixel->show();
  }
}

// int frame = 0;
void loop() {
  comm->handleIncomingMessages(handler);

  unsigned long currentTime = millis();
  if (currentTime >= lastFrameTime + FRAME_INTERVAL) {
    lastFrameTime = currentTime;
    handler->updateLightGroups(pixel);

    // frame += 1;

    // if(frame == 15) {
    //   Serial.print("A frame has been done!!!");
    //   Serial.println(" wow.");
    //   frame = 0;
    // }
    
    pixel->show();
  }
}
