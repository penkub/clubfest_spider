#include <Wire.h>
#include "PCA9685.h"

PCA9685 driver;

// PCA9685 outputs = 12-bit = 4096 steps
// 2.5% of 20ms = 0.5ms ; 12.5% of 20ms = 2.5ms
// 2.5% of 4096 = 102 steps; 12.5% of 4096 = 512 steps
// we will use 112 and 500 to avoid pushing the servo to its physical limits
PCA9685_ServoEval pwmServo(112, 500); // (-90deg, +90deg)

void setup() {
  Wire.begin();                 // Wire must be started first
  driver.resetDevices();         // Software resets all PCA9685 devices on Wire line
  driver.init();
  driver.setPWMFrequency(50);   // Set frequency to 50Hz
}

void loop() {
  driver.setChannelPWM(0, pwmServo.pwmForAngle(-90));
  driver.setChannelPWM(1, pwmServo.pwmForAngle(-90));
  delay(1000);
  driver.setChannelPWM(0, pwmServo.pwmForAngle(0));
  driver.setChannelPWM(1, pwmServo.pwmForAngle(0));
  delay(1000);
  driver.setChannelPWM(0, pwmServo.pwmForAngle(90));
  driver.setChannelPWM(1, pwmServo.pwmForAngle(90));
  delay(1000);
}