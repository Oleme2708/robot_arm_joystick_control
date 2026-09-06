#include <Arduino.h>
#include <Servo.h>

// =====================
// Servo setup
// =====================

Servo wrist;
Servo thumb;
Servo indexFinger;
Servo middleFinger;
Servo ringFinger;
Servo littleFinger;

// Servo pins
const int wristPin = 2;
const int thumbPin = 3;
const int indexPin = 4;
const int middlePin = 5;
const int ringPin = 6;
const int littlePin = 7;

// =====================
// Joystick setup
// =====================

// Joystick 1
const int joystick1_Xpin = A0; // Thumb
const int joystick1_Ypin = A1; // Index

// Joystick 2
const int joystick2_Xpin = A2; // Middle
const int joystick2_Ypin = A3; // Ring

// Joystick 3
const int joystick3_Xpin = A4; // Little
const int joystick3_Ypin = A5; // Wrist

// =====================
// Timing
// =====================

unsigned long StartTime = 0;

const unsigned long updateInterval = 50;

void setup()
{
  Serial.begin(9600);

  // Attach servos
  wrist.attach(wristPin);
  thumb.attach(thumbPin);
  indexFinger.attach(indexPin);
  middleFinger.attach(middlePin);
  ringFinger.attach(ringPin);
  littleFinger.attach(littlePin);

  // Start all servos at 90 degrees
  wrist.write(90);
  thumb.write(90);
  indexFinger.write(90);
  middleFinger.write(90);
  ringFinger.write(90);
  littleFinger.write(90);
}

void loop()
{
  if (millis() - StartTime >= updateInterval)
  {
    // =====================
    // Read joystick values
    // =====================

    int joy1X = analogRead(joystick1_Xpin);
    int joy1Y = analogRead(joystick1_Ypin);

    int joy2X = analogRead(joystick2_Xpin);
    int joy2Y = analogRead(joystick2_Ypin);

    int joy3X = analogRead(joystick3_Xpin);
    int joy3Y = analogRead(joystick3_Ypin);

    // =====================
    // Map joystick to servo
    // =====================

    int thumbAngle =
        map(joy1X, 0, 1023, 0, 180);

    int indexAngle =
        map(joy1Y, 0, 1023, 0, 180);

    int middleAngle =
        map(joy2X, 0, 1023, 0, 180);

    int ringAngle =
        map(joy2Y, 0, 1023, 0, 180);

    int littleAngle =
        map(joy3X, 0, 1023, 0, 180);

    int wristAngle =
        map(joy3Y, 0, 1023, 0, 180);

    // =====================
    // Control servos
    // =====================

    thumb.write(thumbAngle);
    indexFinger.write(indexAngle);
    middleFinger.write(middleAngle);
    ringFinger.write(ringAngle);
    littleFinger.write(littleAngle);
    wrist.write(wristAngle);
    Serial.println(thumbAngle);
    StartTime = millis();
  }
}