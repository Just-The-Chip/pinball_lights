#include "Lists.h"

BaseList::BaseList(uint8_t length) {
  listLength = length;
}

uint8_t BaseList::getLength() {
  return listLength;
}

uint8_t BaseList::sanitizedIndex(uint8_t index) {
  uint8_t listLength = getLength();

  if(index >= listLength) {
    return listLength - 1;
  }

  return index;
}

ColorList::ColorList(uint32_t *colors, uint8_t length)
: BaseList(length) {
  colorList = colors;
}

uint32_t ColorList::getColor(uint8_t index) {
  index = sanitizedIndex(index);

  return *(colorList + index);
}