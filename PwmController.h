#include <Arduino.h>
#include <Wire.h>

class PwmController {
  TwoWire& i2c;
  const uint8_t i2c_addr = 0x09;
  uint16_t channel1 = 0;
  uint16_t channel2 = 0;
  bool channel3 = false;
  bool channel4 = false;
  bool channel5 = false;
  uint8_t last_revs = 0;
  uint32_t total_revs = 0;

 public:
  PwmController();
  explicit PwmController(TwoWire& i2c);

  bool writeRaw(uint16_t channel1, uint16_t channel2);
  bool writeMicroseconds(uint16_t channel1, uint16_t channel2);
  bool read();
  uint16_t getChannel1Microseconds() const;
  uint16_t getChannel2Microseconds() const;
  uint16_t getChannel1Raw() const { return channel1; }
  uint16_t getChannel2Raw() const { return channel2; }
  bool getChannel3() const { return channel3; }
  bool getChannel4() const { return channel4; }
  bool getChannel5() const { return channel5; }
  uint32_t getRevolutionCount() const { return total_revs; }
};
