/*
    Name:       PSX.cpp
    Descr:      Playstation 2 controller library for Arduino
    Version:    0.1
    Author:     Christoph Honal
    Date:       2016-04-11
*/

#include "PSX.h"

PSX::PSX()
{
}

void PSX::sendCommand(byte command, byte &response)
{
    response = 0;
	for (int i=0; i<8; i++)
	{
        digitalWrite(_cmndPin, (command & (1 << i))? HIGH:LOW);
		digitalWrite(_clockPin, LOW);
		delayMicroseconds(_delay);
		if (digitalRead(_dataPin)) response |= 1 << (7 - i);
		digitalWrite(_clockPin, HIGH);
		delayMicroseconds(_delay);
	}
}


void PSX::setupPins(byte dataPin, byte cmndPin, byte attPin, byte clockPin, byte delay)
{
	_dataPin = dataPin;
    _cmndPin = cmndPin;
    _attPin = attPin;
    _clockPin = clockPin;
    _delay = delay;
    pinMode(dataPin, INPUT);
    digitalWrite(dataPin, HIGH);
	pinMode(cmndPin, OUTPUT);
	pinMode(attPin, OUTPUT);
	digitalWrite(attPin, HIGH);
	pinMode(clockPin, OUTPUT);
	digitalWrite(clockPin, HIGH);
}

int PSX::read(PSXDATA &psxdata)
{
	digitalWrite(_attPin, LOW);
    byte response;
	sendCommand(PSXPROT_HANDSHAKE, response);
	sendCommand(PSXPROT_GETDATA, response);
    sendCommand(PSXPROT_IDLE, response);
    if(response == PSXPROT_STARTDATA)
    {
        byte data[6];
        for(int i=0; i<6; i++) sendCommand(PSXPROT_IDLE, data[i]);
        digitalWrite(_attPin, HIGH);
        psxdata.buttons = ~(data[1] + (data[0] << 8));
        psxdata.JoyRightX = data[2];
        psxdata.JoyRightY = data[3];
        psxdata.JoyLeftX = data[4];
        psxdata.JoyLeftY = data[5];
        return PSXERROR_SUCCESS;
    }
    else
    {
        digitalWrite(_attPin, HIGH);
        return PSXERROR_NODATA;
    }
}

void PSX::config(byte mode)
{
    byte response;
    digitalWrite(_attPin, LOW);
	sendCommand(PSXPROT_HANDSHAKE, response);
	sendCommand(PSXPROT_CONFIG, response);
	sendCommand(PSXPROT_IDLE, response);
	sendCommand(PSXPROT_ENTERCONFIG, response);
	sendCommand(PSXPROT_ZERO, response);	
	digitalWrite(_attPin, HIGH);
    delayMicroseconds(_delay);
    digitalWrite(_attPin, LOW); 
	sendCommand(PSXPROT_HANDSHAKE, response);
	sendCommand(PSXPROT_CONFIGMODE, response);
	sendCommand(PSXPROT_IDLE, response);
	sendCommand(mode, response);
	sendCommand(PSXPROT_MODELOCK, response);
	sendCommand(PSXPROT_ZERO, response);
	sendCommand(PSXPROT_ZERO, response);
	sendCommand(PSXPROT_ZERO, response);
	sendCommand(PSXPROT_ZERO, response);	
	digitalWrite(_attPin, HIGH);	
    delayMicroseconds(_delay);
    digitalWrite(_attPin, LOW);
	sendCommand(PSXPROT_HANDSHAKE, response);
	sendCommand(PSXPROT_CONFIG, response);
	sendCommand(PSXPROT_IDLE, response);
	sendCommand(PSXPROT_EXITCONFIG, response);
	sendCommand(PSXPROT_EXITCFGCNT, response);	
	sendCommand(PSXPROT_EXITCFGCNT, response);
	sendCommand(PSXPROT_EXITCFGCNT, response);
	sendCommand(PSXPROT_EXITCFGCNT, response);
	sendCommand(PSXPROT_EXITCFGCNT, response);	
	digitalWrite(_attPin, HIGH);
}