#include <Adafruit_NeoPixel.h>

#include "PiComm.h"
#include "Orchestrator.h"
#include "LightGroup.h"

#include "SimpleOnPattern.h"
#include "OffPattern.h"
#include "FlashPattern.h"
#include "MeterPattern.h"

#define FRAME_INTERVAL 1000 / 30
#define TOTAL_PIXELS 28
#define NEOPIXEL_PIN 6

unsigned long lastFrameTime;

PiComm *comm;
Orchestrator *handler;
Adafruit_NeoPixel *pixel;

OffPattern *offPat;

static uint32_t onPatColors[4];
SimpleOnPattern *onPat;
ColorList *onPatVariants;

static uint32_t specialOnPatColors[5];
SimpleOnPattern *specialOnPat;
ColorList *specialOnPatVariants;

FlashPattern *flashPat;
FlashPattern *grbFlashPat;

static uint32_t grbRainbowColors[7];
MeterPattern *sliderPattern;
ColorList *grbRainbowColorList;


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

static uint8_t magBallCatchPixels[2];
LightGroup *magBallCatch;

static uint8_t plinkoLane1Pixels[1];
LightGroup *plinkoLane1;

static uint8_t plinkoLane2Pixels[1];
LightGroup *plinkoLane2;

static uint8_t plinkoLane3Pixels[1];
LightGroup *plinkoLane3;

static uint8_t plinkoLane4Pixels[1];
LightGroup *plinkoLane4;

static uint8_t leftWallTarget1Pixels[1];
LightGroup *leftWallTarget1;

static uint8_t leftWallTarget2Pixels[1];
LightGroup *leftWallTarget2;

static uint8_t leftWallTarget3Pixels[1];
LightGroup *leftWallTarget3;

static uint8_t leftWallTarget4Pixels[1];
LightGroup *leftWallTarget4;

static uint8_t sliderPixels[7];
LightGroup *slider;


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

  specialOnPatColors[0] = pixel->Color(255, 0, 128);
  specialOnPatColors[1] = pixel->Color(255, 255, 0);
  specialOnPatColors[2] = pixel->Color(0, 255, 255);
  specialOnPatColors[3] = pixel->Color(128, 0, 255);
  specialOnPatColors[4] = pixel->Color(255, 64, 0);
  specialOnPatVariants = new ColorList(specialOnPatColors, 5);
  specialOnPat = new SimpleOnPattern(2, specialOnPatVariants);
  handler->registerPattern(2, specialOnPat);

  flashPat = new FlashPattern(3, 100, onPatVariants);
  handler->registerPattern(3, flashPat);

  grbRainbowColors[0] = pixel->Color(0, 255, 0);
  grbRainbowColors[1] = pixel->Color(64, 255, 0);
  grbRainbowColors[2] = pixel->Color(128, 255, 0);
  grbRainbowColors[3] = pixel->Color(255, 0, 0);
  grbRainbowColors[4] = pixel->Color(255, 0, 255);
  grbRainbowColors[5] = pixel->Color(0, 0, 255);
  grbRainbowColors[6] = pixel->Color(0, 128, 255);
  grbRainbowColorList = new ColorList(grbRainbowColors, 7);

  grbFlashPat = new FlashPattern(4, 100, grbRainbowColorList);
  handler->registerPattern(4, grbFlashPat);

  sliderPattern = new MeterPattern(5, grbRainbowColorList);
  handler->registerPattern(5, sliderPattern);

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
  magSwitch1 = new LightGroup(magSwitch1Pixels, 1);
  handler->registerLightGroup(6, magSwitch1);
  magSwitch1->setActivePatternData(defaultPattern);

  magSwitch2Pixels[0] = 17;
  magSwitch2 = new LightGroup(magSwitch2Pixels, 1);
  handler->registerLightGroup(7, magSwitch2);
  magSwitch2->setActivePatternData(defaultPattern);

  magSwitch3Pixels[0] = 18;
  magSwitch3 = new LightGroup(magSwitch3Pixels, 1);
  handler->registerLightGroup(8, magSwitch3);
  magSwitch3->setActivePatternData(defaultPattern);

  magSwitch4Pixels[0] = 19;
  magSwitch4 = new LightGroup(magSwitch4Pixels, 1);
  handler->registerLightGroup(9, magSwitch4);
  magSwitch4->setActivePatternData(defaultPattern);

  handler->registerLightGroup(10, NULL); // 10 represents \n so we gotta skip it

  magBallCatchPixels[0] = 14;
  magBallCatchPixels[1] = 15;
  magBallCatch = new LightGroup(magBallCatchPixels, 2);
  handler->registerLightGroup(11, magBallCatch);
  magBallCatch->setActivePatternData(defaultPattern);

  plinkoLane1Pixels[0] = 20;
  plinkoLane1 = new LightGroup(plinkoLane1Pixels, 1);
  handler->registerLightGroup(12, plinkoLane1);
  plinkoLane1->setActivePatternData(defaultPattern);

  plinkoLane2Pixels[0] = 21;
  plinkoLane2 = new LightGroup(plinkoLane2Pixels, 1);
  handler->registerLightGroup(13, plinkoLane2);
  plinkoLane2->setActivePatternData(defaultPattern);

  plinkoLane3Pixels[0] = 22;
  plinkoLane3 = new LightGroup(plinkoLane3Pixels, 1);
  handler->registerLightGroup(14, plinkoLane3);
  plinkoLane3->setActivePatternData(defaultPattern);

  plinkoLane4Pixels[0] = 23;
  plinkoLane4 = new LightGroup(plinkoLane4Pixels, 1);
  handler->registerLightGroup(15, plinkoLane4);
  plinkoLane4->setActivePatternData(defaultPattern);

  leftWallTarget1Pixels[0] = 24;
  leftWallTarget1 = new LightGroup(leftWallTarget1Pixels, 1);
  handler->registerLightGroup(16, leftWallTarget1);
  leftWallTarget1->setActivePatternData(defaultPattern);

  leftWallTarget2Pixels[0] = 25;
  leftWallTarget2 = new LightGroup(leftWallTarget2Pixels, 1);
  handler->registerLightGroup(17, leftWallTarget2);
  leftWallTarget2->setActivePatternData(defaultPattern);

  leftWallTarget3Pixels[0] = 26;
  leftWallTarget3 = new LightGroup(leftWallTarget3Pixels, 1);
  handler->registerLightGroup(18, leftWallTarget3);
  leftWallTarget3->setActivePatternData(defaultPattern);

  leftWallTarget4Pixels[0] = 27;
  leftWallTarget4 = new LightGroup(leftWallTarget4Pixels, 1);
  handler->registerLightGroup(19, leftWallTarget4);
  leftWallTarget4->setActivePatternData(defaultPattern);

  sliderPixels[0] = 7;
  sliderPixels[1] = 8;
  sliderPixels[2] = 9;
  sliderPixels[3] = 10;
  sliderPixels[4] = 11;
  sliderPixels[5] = 12;
  sliderPixels[6] = 13;
  slider = new LightGroup(slingRPixels, 7);
  handler->registerLightGroup(20, slider);
  slider->setActivePatternData(defaultPattern);

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
