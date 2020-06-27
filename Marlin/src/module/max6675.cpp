// this library is public domain. enjoy!
// www.ladyada.net/learn/sensors/thermocouple

#include "../HAL/shared/Marduino.h"
#include "../MarlinCore.h"

#include <stdlib.h>
#include "max6675.h"

MAX6675::MAX6675(pin_t max_clock, pin_t max_select, pin_t max_data) {
  sclk = max_clock;
  cs = max_select;
  miso = max_data;
}

void MAX6675::init(void) {
  //define pin modes
  SET_OUTPUT(cs);
  SET_OUTPUT(sclk); 
  SET_INPUT_PULLUP(miso);

  WRITE(cs, HIGH);
}

uint16_t MAX6675::read16(void) {

  uint16_t v;

  WRITE(cs, LOW);
  delayMicroseconds(100);

  v = read8();
  v <<= 8;
  v |= read8();

  WRITE(cs, HIGH);
  delayMicroseconds(100);

  return v;
}

uint8_t MAX6675::read8(void) { 
  int i;
  uint8_t d = 0;

  for (i=7; i>=0; i--)
  {
    WRITE(sclk, LOW);
    delayMicroseconds(100);

    if (READ(miso)) {
      //set the bit to 0 no matter what
      d |= (1 << i);
    }

    WRITE(sclk, HIGH);
    delayMicroseconds(100);
  }

  return d;
}
