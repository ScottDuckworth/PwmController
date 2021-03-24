#include <Arduino.h>
#include <Wire.h>

class PwmController {
  TwoWire& i2c;
  const uint8_t i2c_addr = 0x09;

 public:
  struct Input {
    uint16_t channel1 = 0;
    uint16_t channel2 = 0;
    bool channel3 = false;
    bool channel4 = false;
    bool channel5 = false;
  };

  PwmController();
  explicit PwmController(TwoWire& i2c);

  bool readRaw(Input* input);
  bool writeRaw(uint16_t channel1, uint16_t channel2);
  bool readMicroseconds(Input* input);
  bool writeMicroseconds(uint16_t channel1, uint16_t channel2);
};
