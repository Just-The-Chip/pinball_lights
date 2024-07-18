#include "Lists.h"

ColorList::ColorList(uint32_t *colors, uint8_t length) {
  colorList = colors;
  colorLength = length;
}

uint32_t ColorList::getColor(int index) {
  if(index >= colorLength) {
    index = colorLength - 1;
  }

  return *(colorList + index);
}

uint8_t ColorList::getLength() {
  return colorLength;
}