# ArduinoPSX
### A Playstation 2 controller library for Arduino.

#### Features
- Read digital button states
- Read analog joystick values
- Set and lock digital / analog mode
- Turn off vibration motors to save energy

#### Usage

For wire colors and wiring, refer to https://store.curiousinventor.com/guides/PS2. Make sure to connect all the power and ground wires!

A timing delay of `10` microseconds is usually fine.

```c
PSX psx;
PSX::PSXDATA PSXdata;
int PSXerror;

psx.setupPins(dataPin, cmdPin, attPin, clockPin, delay);
psx.config(PSXMODE_ANALOG);

PSXerror = psx.read(PSXdata);
if(PSXerror == PSXERROR_SUCCESS)
{
    byte test = PSXdata.JoyLeftX;
    boolean test2 = (PSXdata.buttons & PSXBTN_LEFT);
}
```

Check the example code or source code documentation for all available attributes.

#### Available on
- GitHub https://github.com/StarGate01/ArduinoPSX
- Platform.io http://platformio.org/lib/show/278/ArduinoPSX

#### Thanks to / Sources:
- http://playground.arduino.cc/Main/PSXLibrary
- http://store.curiousinventor.com/guides/PS2
