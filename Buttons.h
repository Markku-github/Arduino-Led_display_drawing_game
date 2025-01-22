#ifndef Buttons_h
#define Buttons_h

#include <Arduino.h>

class Buttons {
  private:
    // Pins for the buttons.
    int action_button;
    int right_button;
    int down_button;
    int left_button;
    int up_button;

  public:
    Buttons(int action_button, int right_button, int down_button, int left_button, int up_button);
    void buttonListener(int * pressed_button, int * previous_pressed_button);
};

#endif