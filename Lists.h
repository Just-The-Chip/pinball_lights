#pragma once

class ColorList {
  public: 
    ColorList(uint32_t* colors, uint8_t length);
    virtual uint32_t getColor(int index);
    virtual uint8_t getLength();

  protected: 
    uint32_t* colors;
    uint8_t length;
}
