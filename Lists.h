#include <stdint.h>
#pragma once

class BaseList {
  public:
    BaseList(uint8_t length);
    virtual uint8_t getLength();

  protected: 
    uint8_t listLength;
    virtual uint8_t sanitizedIndex(uint8_t index);
};

class ColorList: public BaseList {
  public: 
    ColorList(uint32_t *colors, uint8_t length);
    virtual uint32_t getColor(uint8_t index);

  protected: 
    uint32_t *colorList;
};