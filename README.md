# ArduinoPSX
### A Playstation 2 controller library for Arduino

#### Features:
- Read digital button states
- Read analog joystick values
- Set and lock digital / analog mode
- Turn off vibration motors to save energy

#### Usage:
```c
PSX psx;
PSX::PSXDATA PSXdata;
int PSXerror;

psx.setupPins(dataPin, cmndPin, attPin, clockPin, 10);
psx.config(PSXMODE_ANALOG);

PSXerror = psx.read(PSXdata);
if(PSXerror == PSXERROR_SUCCESS)
{
    byte test = PSXdata.JoyLeftX;
    boolean test2 = (PSXdata.buttons & PSXBTN_LEFT);
}
```

#### Thanks to:
- http://playground.arduino.cc/Main/PSXLibrary
- http://store.curiousinventor.com/guides/PS2
