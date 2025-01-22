#include "LedMatrix.h"
#include "Buttons.h"

// Pins for the 74HC595 shift register.
const int latch_pin = 4; // Pin connected to 74HC959's RCLK pin a.k.a. latch pin (pin 12).
const int clock_pin = 5; // Pin connected to 74HC595's SRCLK pin a.k.a. clock pin (pin 11). 
const int data_pin = 3; // Pin connected to 74HC959's SER pin a.k.a. data pin (pin 14).

// Pins for the buttons.
const int action_button = 8;
const int right_button = 9;
const int down_button = 10;
const int left_button = 11;
const int up_button = 12;

// Create led matrix object.
LedMatrix led_matrix(latch_pin, clock_pin, data_pin);
// Create buttons object.
Buttons buttons(action_button, right_button, down_button, left_button, up_button);

void setup() {
  Serial.begin(9600); // Serial begin.
}

void loop() {
  /*
  Variables declared as static will only be created and initialized one time on the first time a function is called.
  */

  // Bytes for led matrix. 
  static byte row = B10000000;
  static byte column = B10000000;

  // Declare constant pointer for row and column.
  static byte *const p_row = &row;
  static byte *const p_column = &column;

  static int pressed_button = 0; // Store just pressed button. Default is set to 0.
  static int previous_pressed_button = 0; // Store previous pressed button. Default is set to 0.

  // Declare constant pointer for pressed button and previous pressed button.
  static int *const p_pressed_button = &pressed_button;
  static int *const p_previous_pressed_button = &previous_pressed_button;

  // Update position a.k.a. cursor to the led matrix. i.e. lit correct led.
  led_matrix.displayCursor(p_row, p_column);
  // Call the button listener, which update information about button presses.
  buttons.buttonListener(p_pressed_button, p_previous_pressed_button);
  
  // Execute only if the previous pressed button was different that the just pressed button.
  // This prevent multiple bit shift if the button press was too long.
  if (previous_pressed_button != pressed_button) {
    // Check whether the pressed button was left or right button and if so pass the column byte as a parameter.
    if (pressed_button == right_button || pressed_button == left_button) {
      bitShift(p_pressed_button, p_column);
    }
    // Check whether the pressed button was up or down button and if so pass the row byte as a parameter.
    if (pressed_button == up_button || pressed_button == down_button) {
      bitShift(p_pressed_button, p_row);
    }
  }
}

void bitShift(int * pressed_button, byte * pByte)  {
    // This switch statement check which button pressed and shift bytes based on that.
    switch(*pressed_button) {
      case action_button:
        break;

      case right_button:
        if (*pByte == (byte)1) {
          *pByte = (byte)128;
        }
        else {
          *pByte = *pByte >> 1;
        }
        break;

      case down_button:
        if (*pByte == (byte)1) {
          *pByte = (byte)128;
        }
        else {
          *pByte = *pByte >> 1;
        }
        break;

      case left_button:
        if (*pByte == (byte)128) {
          *pByte = (byte)1;
        }
        else {
          *pByte = *pByte << 1;
        }
        break;

      case up_button:
        if (*pByte == (byte)128) {
          *pByte = (byte)1;
        }
        else {
          *pByte = *pByte << 1;
        }
        break;

      default:
        break;
    }
    
}