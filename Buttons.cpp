#include "Buttons.h"

Buttons::Buttons(int a_button, int r_button, int d_button, int l_button, int u_button) {
  // Pins for the buttons.
  action_button = a_button;
  right_button = r_button;
  down_button = d_button;
  left_button = l_button;
  up_button = u_button;

  // Set the button pins to input mode.
  pinMode(action_button, INPUT);
  pinMode(right_button, INPUT);
  pinMode(down_button, INPUT);
  pinMode(left_button, INPUT);
  pinMode(up_button, INPUT);
}

void Buttons::buttonListener(int * pressed_button, int * previous_pressed_button) {
  // Variables declared as static will only be created one time on the first time a function is called.
  static int left_button_state;
  static int right_button_state;
  static int down_button_state;
  static int up_button_state;
  static int action_button_state;

  // Read the state of all buttons.
  left_button_state = digitalRead(left_button);
  right_button_state = digitalRead(right_button);
  down_button_state = digitalRead(down_button);
  up_button_state = digitalRead(up_button);
  action_button_state = digitalRead(action_button);

  /*
  This if statement prevent multiple buttons pressed at the same time.
  */
  if (left_button_state == HIGH && right_button_state == LOW && down_button_state == LOW && up_button_state == LOW && action_button_state == LOW) {
    // Store the previous pressed button.
    *previous_pressed_button = *pressed_button;

    // Pressed button was the left button.
    *pressed_button = left_button;
  }
  else if (left_button_state == LOW && right_button_state == HIGH && down_button_state == LOW && up_button_state == LOW && action_button_state == LOW) {
    // Store the previous pressed button.
    *previous_pressed_button = *pressed_button;

    // Pressed button was the right button.
    *pressed_button = right_button;
  }
  else if (left_button_state == LOW && right_button_state == LOW && down_button_state == HIGH && up_button_state == LOW && action_button_state == LOW) {
    // Store the previous pressed button.
    *previous_pressed_button = *pressed_button;

    // Pressed button was the down button.
    *pressed_button = down_button;
  }
  else if (left_button_state == LOW && right_button_state == LOW && down_button_state == LOW && up_button_state == HIGH && action_button_state == LOW) {
    // Store the previous pressed button.
    *previous_pressed_button = *pressed_button;

    // Pressed button was the up button.
    *pressed_button = up_button;
  }
  else if (left_button_state == LOW && right_button_state == LOW && down_button_state == LOW && up_button_state == LOW && action_button_state == HIGH) {
    // Store the previous pressed button.
    *previous_pressed_button = *pressed_button;

    // Pressed button was the action button.
    *pressed_button = action_button;
  }
  else {
    // Store the previous pressed button.
    *previous_pressed_button = *pressed_button;

    // None or multiple buttons was pressed.
    *pressed_button = 0;
  }
}