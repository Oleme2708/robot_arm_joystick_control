#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40);

const uint8_t ServoChannels[] = {0, 1, 2, 3, 4};
const uint8_t ServoCount = sizeof(ServoChannels) / sizeof(ServoChannels[0]);

const uint16_t ServoLeft = 250;
const uint16_t ServoMiddle = 350;
const uint16_t ServoRight = 450;
const uint16_t MoveDelayMs = 1000;

bool scanForPCA()
{
  bool pcaFound = false;
  bool anyDeviceFound = false;

  Serial.println("Scanning I2C...");

  for (uint8_t address = 1; address < 127; address++)
  {
    Wire.beginTransmission(address);
    uint8_t error = Wire.endTransmission();

    if (error == 0)
    {
      anyDeviceFound = true;

      Serial.print("Found I2C device at 0x");
      if (address < 16)
      {
        Serial.print("0");
      }
      Serial.println(address, HEX);

      if (address == 0x40)
      {
        pcaFound = true;
      }
    }
  }

  if (pcaFound)
  {
    Serial.println("I2C device connected at 0x40");
  }
  else if (anyDeviceFound)
  {
    Serial.println("Cannot find I2C device at 0x40");
  }
  else
  {
    Serial.println("Cannot find I2C device");
  }

  return pcaFound;
}

void moveServo(uint8_t channel, const char *direction, uint16_t pulse)
{
  Serial.print("Servo ");
  Serial.print(channel);
  Serial.print(": ");
  Serial.println(direction);

  pwm.setPWM(channel, 0, pulse);
  delay(MoveDelayMs);
}

void setup()
{
  Serial.begin(9600);
  delay(1000);

  Wire.begin();
  Wire.setClock(50000);

  while (!scanForPCA())
  {
    Serial.println("Retry in 2 seconds...");
    delay(2000);
  }

  pwm.begin();
  pwm.setOscillatorFrequency(27000000);
  pwm.setPWMFreq(50);

  delay(500);
  Serial.println("Start 5-servo test on PCA9685 channels 0-4");
}

void loop()
{
  for (uint8_t i = 0; i < ServoCount; i++)
  {
    uint8_t channel = ServoChannels[i];

    moveServo(channel, "left", ServoLeft);
    moveServo(channel, "middle", ServoMiddle);
    moveServo(channel, "right", ServoRight);
    moveServo(channel, "middle", ServoMiddle);
  }
}
