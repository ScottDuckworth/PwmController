#include "PwmController.h"

PwmController::PwmController() : PwmController(Wire) {}

PwmController::PwmController(TwoWire& i2c) : i2c(i2c) {}

bool PwmController::read() {
  uint8_t buffer[5];
  i2c.requestFrom(i2c_addr, sizeof(buffer));
  size_t n = i2c.readBytes(buffer, sizeof(buffer));
  if (n != sizeof(buffer)) return false;

  channel1 = (static_cast<uint16_t>(buffer[1]) << 8 | static_cast<uint16_t>(buffer[2]));
  channel2 = (static_cast<uint16_t>(buffer[3]) << 8 | static_cast<uint16_t>(buffer[4]));
  channel3 = buffer[0] & 0b00000001;
  channel4 = buffer[0] & 0b00000010;
  channel5 = buffer[0] & 0b00000100;
  return true;
}

uint16_t PwmController::getChannel1Microseconds() const {
  return channel1 * 100 / 302;
}

uint16_t PwmController::getChannel2Microseconds() const {
  return channel2 * 100 / 302;
}

bool PwmController::writeRaw(uint16_t channel1, uint16_t channel2) {
  uint8_t buffer[4];
  buffer[0] = channel1 >> 8;
  buffer[1] = channel1 & 0xff;
  buffer[2] = channel2 >> 8;
  buffer[3] = channel2 & 0xff;
  i2c.beginTransmission(i2c_addr);
  i2c.write(buffer, sizeof(buffer));
  i2c.endTransmission();
  return true;
}

bool PwmController::writeMicroseconds(uint16_t channel1, uint16_t channel2) {
  return writeRaw(channel1 * 302 / 100, channel2 * 302 / 100);
}
