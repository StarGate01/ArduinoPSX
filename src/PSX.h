/*
    Name:       PSX.h
    Descr:      Playstation 2 controller library for Arduino definition
    Version:    1.0.1
    Author:     Christoph Honal
    Date:       2016-04-11
    Update:     2020-04-25
*/

#ifndef Psx_h
#define Psx_h

#include "Arduino.h"


// Button bitfield constants

#define PSXBTN_LEFT         0x8000
#define PSXBTN_DOWN         0x4000
#define PSXBTN_RIGHT        0x2000
#define PSXBTN_UP           0x1000
#define PSXBTN_START        0x0800
#define PSXBTN_SELECT       0x0100
#define PSXBTN_SQUARE       0x0080
#define PSXBTN_CROSS        0x0040
#define PSXBTN_CIRCLE       0x0020
#define PSXBTN_TRIANGLE     0x0010
#define PSXBTN_R1           0x0008
#define PSXBTN_L1           0x0004
#define PSXBTN_R2           0x0002
#define PSXBTN_L2           0x0001

// Protocol commands and constants

#define PSXPROT_IDLE        0x00
#define PSXPROT_NONZERO     0xFF
#define PSXPROT_ZERO        0x00
#define PSXPROT_HANDSHAKE   0x01
#define PSXPROT_GETDATA     0x42
#define PSXPROT_STARTDATA   0x5A
#define PSXPROT_CONFIG      0x43
#define PSXPROT_CONFIGMOTOR 0x4D
#define PSXPROT_MOTORMAP    0x01
#define PSXPROT_ENTERCONFIG 0x01
#define PSXPROT_EXITCONFIG  0x00
#define PSXPROT_EXITCFGCNT  0x5A
#define PSXPROT_CONFIGMODE  0x44
#define PSXPROT_MODELOCK    0x03
#define PSXMODE_ANALOG      0x01
#define PSXMODE_DIGITAL     0x00

// Read function return codes

#define PSXERROR_SUCCESS    0
#define PSXERROR_NODATA     1


// See PSX.cpp for implementation

/**
 * @brief Provides routines to interface a Playstation 2 (PSX) controller
 * 
 */
class PSX
{
    public:

        /**
         * @brief Holds the state of the controller
         * 
         */
        struct PSXDATA
        {
            unsigned int buttons;   //!< The state of all buttons encoded as a bitfield
            byte JoyLeftX;          //!< The horizontal value of the left joystick
            byte JoyLeftY;          //!< The vertical value of the left joystick
            byte JoyRightX;         //!< The horizontal value of the right joystick
            byte JoyRightY;         //!< The vertical value of the right joystick
        };

        /**
         * @brief Construct a new PSX::PSX object
         * 
         */
        PSX();

        /**
         * @brief Assign the pins to be used for communication and set the protocol timing
         * 
         * @param dataPin The data pin (usually brown wire)
         * @param cmdPin The command pin (usually orange wire)
         * @param attPin The attention pin (usually yellow wire)
         * @param clockPin The clock pin (usually blue wire)
         * @param delay The protocol timing delay in microseconds (usually 10)
         */
        void setupPins(byte dataPin, byte cmdPin, byte attPin, byte clockPin, byte delay);

        /**
         * @brief Read the state of all joysticks and buttons from the controller
         * 
         * @param psxdata The state read from the controller
         * @return int Error code, PSXERROR_SUCCESS or PSXERROR_NODATA
         */
        int read(PSXDATA &psxdata);

        /**
         * @brief Configures the controller, disables vibration and sets either analog or digital mode
         * 
         * @param mode What mode to set. PSXMODE_ANALOG or PSXMODE_DIGITAL.
         */
        void config(byte mode);
        
    private:
    
        /**
         * @brief Send a command to the PSX controller
         * 
         * @param command The command to send
         * @param response The response from the controller
         */
        void sendCommand(byte command, byte &response);

        byte _dataPin, _cmdPin, _attPin, _clockPin, _delay;

};

#endif
