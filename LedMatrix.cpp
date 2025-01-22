#include "LedMatrix.h"

LedMatrix::LedMatrix(int l_pin, int c_pin, int d_pin) {
  // Pin connected to 74HC959's RCLK pin a.k.a. latch pin (pin 12).
  latch_pin = l_pin; 
  clock_pin = c_pin; // Pin connected to 74HC595's SRCLK pin a.k.a. clock pin (pin 11).
  data_pin = d_pin; // Pin connected to 74HC959's SER pin a.k.a. data pin (pin 14).

  // Set the shift register pins to output mode.
  pinMode(latch_pin, OUTPUT);
  pinMode(clock_pin, OUTPUT);
  pinMode(data_pin, OUTPUT);
}

void LedMatrix::displayCursor(byte * p_row, byte * p_column) {
  // Set latch pin down while data is writing. This prevent wrong led lit up.
  digitalWrite(latch_pin, LOW);

  /* 
  Send 2 bytes (column and row) to the shift registers. 
  The first byte (column) passes through the first register and ends up in at the second one.
  The second byte (row) remains in the first register.
  */
  shiftOut(data_pin, clock_pin, LSBFIRST, ~*p_column); // Reverse bits for column.
  shiftOut(data_pin, clock_pin, LSBFIRST, *p_row);
  
  // Set latch pin up so data will be sent to the led matrix.
  digitalWrite(latch_pin, HIGH);
}