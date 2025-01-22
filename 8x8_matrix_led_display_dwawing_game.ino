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

const int blink_delay = 750; // Used for cursore blink delay.

void setup() {
  Serial.begin(9600); // Serial begin.

  // Set the shift register pins to output mode.
  pinMode(latch_pin, OUTPUT);
  pinMode(clock_pin, OUTPUT);
  pinMode(data_pin, OUTPUT);

  // Set the button pins to input mode.
  pinMode(action_button, INPUT);
  pinMode(right_button, INPUT);
  pinMode(down_button, INPUT);
  pinMode(left_button, INPUT);
  pinMode(up_button, INPUT);
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
  displayCursor(p_row, p_column);
  // Call the button listener, which update information about button presses.
  buttonListener(p_pressed_button, p_previous_pressed_button);
  
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

void displayCursor(byte * p_row, byte * p_column) {
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

int buttonListener(int * pressed_button, int * previous_pressed_button) {
  // Variables declared as static will only be created one time on the first time a function is called.
  static int left_button_state;
  static int right_button_state;
  static int down_button_state;
  static int up_button_state;

  // Read the state of all buttons.
  left_button_state = digitalRead(left_button);
  right_button_state = digitalRead(right_button);
  down_button_state = digitalRead(down_button);
  up_button_state = digitalRead(up_button);

  /*
  This if statement prevent multiple buttons pressed at the same time.
  */
  if (left_button_state == HIGH && right_button_state == LOW && down_button_state == LOW && up_button_state == LOW) {
    // Store the previous pressed button.
    *previous_pressed_button = *pressed_button;

    // Pressed button was the left button.
    *pressed_button = left_button;
  }
  else if (left_button_state == LOW && right_button_state == HIGH && down_button_state == LOW && up_button_state == LOW) {
    // Store the previous pressed button.
    *previous_pressed_button = *pressed_button;

    // Pressed button was the right button.
    *pressed_button = right_button;
  }
  else if (left_button_state == LOW && right_button_state == LOW && down_button_state == HIGH && up_button_state == LOW) {
    // Store the previous pressed button.
    *previous_pressed_button = *pressed_button;

    // Pressed button was the down button.
    *pressed_button = down_button;
  }
  else if (left_button_state == LOW && right_button_state == LOW && down_button_state == LOW && up_button_state == HIGH) {
    // Store the previous pressed button.
    *previous_pressed_button = *pressed_button;

    // Pressed button was the up button.
    *pressed_button = up_button;
  }
  else {
    // Store the previous pressed button.
    *previous_pressed_button = *pressed_button;

    // None or multiple buttons was pressed.
    *pressed_button = 0;
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