/*
    Name:       PSX.cpp
    Descr:      Playstation 2 controller library for Arduino implementation
    Version:    1.0.1
    Author:     Christoph Honal
    Date:       2016-04-11
    Update:     2020-04-25
*/

#include "PSX.h"


// Implement the routines defined in PSX.h

PSX::PSX()
{
}

void PSX::sendCommand(byte command, byte &response)
{
    // Write out a byte command, or read a byte from the controller
    // When reading, the "command" is usually IDLE (0), thus no data gets written
    // The response is always the response from the previous command
    response = 0;
    for (int i=0; i<8; i++)
    {
        // Write command bit
        digitalWrite(_cmdPin, (command & (1 << i))? HIGH:LOW);
        digitalWrite(_clockPin, LOW);
        delayMicroseconds(_delay);
        // Read response bit
        if (digitalRead(_dataPin)) response |= 1 << i;
        digitalWrite(_clockPin, HIGH);
        delayMicroseconds(_delay);
    }
}

void PSX::setupPins(byte dataPin, byte cmdPin, byte attPin, byte clockPin, byte delay)
{
    // Assign pins
    _dataPin = dataPin;
    _cmdPin = cmdPin;
    _attPin = attPin;
    _clockPin = clockPin;
    _delay = delay;
    // Setup pins and pin states
    pinMode(dataPin, INPUT);
    digitalWrite(dataPin, HIGH);
    pinMode(cmdPin, OUTPUT);
    pinMode(attPin, OUTPUT);
    digitalWrite(attPin, HIGH);
    pinMode(clockPin, OUTPUT);
    digitalWrite(clockPin, HIGH);
}

int PSX::read(PSXDATA &psxdata)
{
    // Send data request
    digitalWrite(_attPin, LOW);
    byte response;
    sendCommand(PSXPROT_HANDSHAKE, response);
    sendCommand(PSXPROT_GETDATA, response);
    sendCommand(PSXPROT_IDLE, response);
    // Check response
    if(response == PSXPROT_STARTDATA)
    {
        // Decode response
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
    // Perform initial handshake with the controller
    // Enter config
    byte response;
    digitalWrite(_attPin, LOW);
    sendCommand(PSXPROT_HANDSHAKE, response);
    sendCommand(PSXPROT_CONFIG, response);
    sendCommand(PSXPROT_IDLE, response);
    sendCommand(PSXPROT_ENTERCONFIG, response);
    sendCommand(PSXPROT_ZERO, response);    
    digitalWrite(_attPin, HIGH);
    delayMicroseconds(_delay);
    // Set mode
    digitalWrite(_attPin, LOW); 
    sendCommand(PSXPROT_HANDSHAKE, response);
    sendCommand(PSXPROT_CONFIGMODE, response);
    sendCommand(PSXPROT_IDLE, response);
    sendCommand(mode, response);
    sendCommand(PSXPROT_MODELOCK, response);
    for(int i=0; i<4; i++) sendCommand(PSXPROT_ZERO, response);  
    digitalWrite(_attPin, HIGH);    
    delayMicroseconds(_delay);
    // Disable vibration motors
    digitalWrite(_attPin, LOW); 
    sendCommand(PSXPROT_HANDSHAKE, response);
    sendCommand(PSXPROT_CONFIGMOTOR, response);
    sendCommand(PSXPROT_IDLE, response);
    sendCommand(PSXPROT_ZERO, response);
    sendCommand(PSXPROT_MOTORMAP, response);
    for(int i=0; i<4; i++) sendCommand(PSXPROT_NONZERO, response);   
    digitalWrite(_attPin, HIGH);    
    delayMicroseconds(_delay);
    // Finish config
    digitalWrite(_attPin, LOW);
    sendCommand(PSXPROT_HANDSHAKE, response);
    sendCommand(PSXPROT_CONFIG, response);
    sendCommand(PSXPROT_IDLE, response);
    sendCommand(PSXPROT_EXITCONFIG, response);
    for(int i=0; i<5; i++) sendCommand(PSXPROT_EXITCFGCNT, response);        
    digitalWrite(_attPin, HIGH);
}
