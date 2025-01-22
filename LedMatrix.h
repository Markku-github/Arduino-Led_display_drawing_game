#ifndef LedMatrix_h
#define LedMatrix_h

#include <Arduino.h>

class LedMatrix {
  private:
    // Pin connected to the shift register.
    int latch_pin;
    int clock_pin;
    int data_pin;

  public:
    LedMatrix(int latch_pin, int clock_pin, int data_pin);
    void displayCursor(byte * p_row, byte * p_column);
};

#endif