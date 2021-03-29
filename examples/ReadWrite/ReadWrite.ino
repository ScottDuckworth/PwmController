#include <PwmController.h>

PwmController pwm_controller;

void setup() {
  Serial.begin(115200);
  Wire.begin();
}

void loop() {
  static unsigned long last_write = 0;
  static unsigned long last_read = 0;
  unsigned long now = millis();

  if (last_write + 10 <= now) {
    last_write = now;
    static uint16_t pw = 1000, pw_inc = 0;
    pw += pw_inc;
    pwm_controller.writeMicroseconds(pw, pw);
    if (pw <= 1000) pw_inc = 10;
    if (pw >= 2000) pw_inc = -10;
  }

  if (last_read + 100 <= now) {
    last_read = now;
    pwm_controller.read();
    Serial.print(pwm_controller.getChannel1Microseconds());
    Serial.print(' ');
    Serial.print(pwm_controller.getChannel2Microseconds());
    Serial.print(' ');
    Serial.print(pwm_controller.getChannel3());
    Serial.print(' ');
    Serial.print(pwm_controller.getChannel4());
    Serial.print(' ');
    Serial.print(pwm_controller.getChannel5());
    Serial.println();
  }
}
