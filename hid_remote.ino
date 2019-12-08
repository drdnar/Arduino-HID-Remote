#include "HIDRemote.h"

#define ROWS 3
#define COLUMNS 3

// Rows, used as drivers
const uint8_t rows[] = { 5, 3, 2 };
// Columns, used for sense
const uint8_t columns[] = { 7, 4, 6 };

/* Layout of keyboard matrix
 *      C1      C2      C3
 * R1   Prev    Next    Vol up
 * R2   Stop    Play/Ps Vol down
 * R3   RR      FF      Mute
 */
const uint16_t key_codes[3][3] = {
  { HID_REMOTE_PREVIOUS, HID_REMOTE_NEXT, HID_REMOTE_VOLUME_UP },
  { HID_REMOTE_STOP, HID_REMOTE_PLAY_PAUSE, HID_REMOTE_VOLUME_DOWN },
  { HID_REMOTE_REWIND, HID_REMOTE_FAST_FORWARD, HID_REMOTE_MUTE }
};

bool key_states[ROWS][COLUMNS] = {
  {1, 1, 1},
  {1, 1, 1},
  {1, 1, 1},
};

void idle_key_matrix() {
  for (uint8_t i = 0; i < ROWS; i++)
    digitalWrite(rows[i], LOW);
}

void reset_key_matrix() {
  for (uint8_t i = 0; i < ROWS; i++)
    digitalWrite(rows[i], HIGH);  
}

bool check_key_matrix() {
  return digitalRead(columns[0]) && digitalRead(columns[1]) && digitalRead(columns[2]);
}

void setup() {
  HIDRemote.begin();
  for (uint8_t i = 0; i < ROWS; i++)
  {
    pinMode(rows[i], OUTPUT);
    digitalWrite(rows[i], HIGH);
  }
  for (uint8_t i = 0; i < COLUMNS; i++)
    pinMode(columns[i], INPUT_PULLUP);
}

void loop() {
  for (uint8_t i = 0; i < ROWS; i++)
  {
    digitalWrite(rows[i], LOW);
    // Wait for a moment to negate any possible capacitive effects.
    delay(1);
    for (uint8_t j = 0; j < COLUMNS; j++)
    {
      bool key_state = digitalRead(columns[j]);
      if (key_states[i][j] != key_state)
      {
        key_states[i][j] = key_state;
        if (key_state)
          HIDRemote.release(key_codes[i][j]);
        else
          HIDRemote.press(key_codes[i][j]);
      } 
    }
    digitalWrite(rows[i], HIGH);
  }
}
