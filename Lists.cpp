#include "Lists.h"

ColorList::ColorList(uint32_t* colors, uint8_t length) {
  colors = colors;
  length = length;
}

uint32_t ColorList::getColor(int index) {
  if(index >= length) {
    index = length - 1;
  }

  return *(pixelIDs + index);
}

uint8_t ColorList::getLength() {
  return length;
}