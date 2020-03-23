// this library is public domain. enjoy!
// www.ladyada.net/learn/sensors/thermocouple

class MAX6675 {
 public:
  MAX6675(pin_t max_clock, pin_t max_select, pin_t max_data);

  void init(void);
  uint8_t read8(void);
  uint16_t read16(void);
 private:
  pin_t sclk, cs, miso;
};
