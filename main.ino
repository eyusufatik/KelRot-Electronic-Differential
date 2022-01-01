#define LEFTENCA 13
#define LEFTENCB 12

#define RIGHTENCA 7
#define RIGHTENCB 6

#define STEERINGA A0
#define STEERINGB A1

#define RADIUS 1

#include <Encoder.h>
#include "DriveWheel.h"
#include "SteeringWheel.h"
#include "Differential.h"

Encoder leftEncoder(LEFTENCA, LEFTENCB);
volatile long leftStep = 0;

Encoder rightEncoder(RIGHTENCA, RIGHTENCB);
volatile long rightStep = 0;

Encoder steeringEncoder(STEERINGA, STEERINGB);
volatile long steeringStep = 0;

DriveWheel leftWheel(&leftStep, RADIUS);
DriveWheel rightWheel(&rightStep, RADIUS);
SteeringWheel steering(&steeringStep);

Differential diff(1.20, 1.10);
Coefficients coefs;

void pciSetup(byte pin)
{
    *digitalPinToPCMSK(pin) |= bit(digitalPinToPCMSKbit(pin)); // enable pin
    PCIFR |= bit(digitalPinToPCICRbit(pin));                   // clear any outstanding interrupt
    PCICR |= bit(digitalPinToPCICRbit(pin));                   // enable interrupt for the group
}

ISR(PCINT0_vect) // handle pin change interrupt for D8 to D13 here
{
    leftStep = leftEncoder.read();
}

ISR(PCINT1_vect) // handle pin change interrupt for A0 to A5 here
{
    steeringStep = steeringEncoder.read();
}

ISR(PCINT2_vect) // handle pin change interrupt for D0 to D7 here
{
    rightStep = rightEncoder.read();
}

void setup()
{
    Serial.begin(9600);
    pciSetup(LEFTENCA);
    pciSetup(RIGHTENCA);
    pciSetup(STEERINGA);
}

void loop()
{
    double leftAngle = steering.getAngle();
    coefs = diff.getWheelCoefficients(leftAngle);

    double leftSpeed = leftWheel.getSpeed();
    double rightSpeed = rightWheel.getSpeed();

    delay(10);
}
