/*
    Name:       TestPSX.ino
    Descr:      Example for the Playstation 2 controller library for Arduino 
    Version:    1.0.1
    Author:     Christoph Honal
    Date:       2020-04-25
*/

#include <PSX.h>

#define dataPin   10  // Brown wire
#define cmdPin    11  // Orange wire
#define attPin    12  // Yellow wire
#define clockPin  13  // Blue wire


// Static instantiation of the library
PSX psx;

// Variables to hold the controller state and error code
PSX::PSXDATA PSXdata;
int PSXerror;


void setup() {
  //Setup the PSX library
  psx.setupPins(dataPin, cmdPin, attPin, clockPin, 10);
  psx.config(PSXMODE_ANALOG);
  // Setup serial communication
  Serial.begin(9600);
}

void loop() {
  // Read controller state
  PSXerror = psx.read(PSXdata);

  // Check if the read was successful
  if(PSXerror == PSXERROR_SUCCESS) {
      // Print the joystick states
      Serial.print("JoyLeft: X: ");
      Serial.print(PSXdata.JoyLeftX);
      Serial.print(", Y: ");
      Serial.print(PSXdata.JoyLeftY);
      Serial.print(", JoyRight: X: ");
      Serial.print(PSXdata.JoyRightX);
      Serial.print(", Y: ");
      Serial.print(PSXdata.JoyRightY);

      //Print the button states
      Serial.print(", Buttons: ");
      if(PSXdata.buttons & PSXBTN_LEFT) {
        Serial.print("Left, ");
      }
      if(PSXdata.buttons & PSXBTN_DOWN) {
        Serial.print("Down, ");
      }
      if(PSXdata.buttons & PSXBTN_RIGHT) {
        Serial.print("Right, ");
      }
      if(PSXdata.buttons & PSXBTN_UP) {
        Serial.print("Up, ");
      }
      if(PSXdata.buttons & PSXBTN_START) {
        Serial.print("Start, ");
      }
      if(PSXdata.buttons & PSXBTN_SELECT) {
        Serial.print("Select, ");
      }
      if(PSXdata.buttons & PSXBTN_SQUARE) {
        Serial.print("Square, ");
      }
      if(PSXdata.buttons & PSXBTN_CROSS) {
        Serial.print("Cross, ");
      }
      if(PSXdata.buttons & PSXBTN_CIRCLE) {
        Serial.print("Circle, ");
      }
      if(PSXdata.buttons & PSXBTN_TRIANGLE) {
        Serial.print("Triangle, ");
      }
      if(PSXdata.buttons & PSXBTN_R1) {
        Serial.print("R1, ");
      }
      if(PSXdata.buttons & PSXBTN_L1) {
        Serial.print("L1, ");
      }
      if(PSXdata.buttons & PSXBTN_R2) {
        Serial.print("R2, ");
      }
      if(PSXdata.buttons & PSXBTN_L2) {
        Serial.print("L2, ");
      }

      Serial.println("");
  } else {
    Serial.print("No success reading data. Check connections and timing.");
  }
}