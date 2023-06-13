#pragma once
#include "PSX.h"
#include "SigmaIO.hpp"

class PSX1 : public PSX
{
public:
    void pinMode(byte pin, byte mode){sigmaIO->PinMode(pin, mode);};
    void digitalWrite(byte pin, byte value) { sigmaIO->DigitalWrite(pin, value); };
    byte digitalRead(byte pin) { return sigmaIO->DigitalRead(pin); };
};