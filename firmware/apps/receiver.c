/*! \file receiver.c
  \brief Radio morse receiver
*/

#include<stdio.h>
#include<string.h>
#include<msp430.h>
#include "api.h"
#include "receiver.h"

const int BUZZ_FREQ = 32768 / 7000;
static int rssi_thresh;

//! Enter the receive app.
void receiver_init() {
  radio_on();
  codeplug_setfreq();
  clearperiods();
  rssi_thresh = radio_getrssi() + 2;
  lcd_number(rssi_thresh);
}

//! Exit the receive app.
int receiver_exit() {
  //Cut the radio off and drop the CPU frequency.
  radio_off();

  // Turn off the buzzer
  buzz(0);

  //Allow the exit.
  return 0;
}

//! Draw the screen
void receiver_draw(int forced) {
  // Previous state
  static uint8_t prev = 0;

  // Enable/disable left-most dot and buzzer
  // if state changed
  uint8_t on = rssi_thresh < radio_getrssi();
  if(on != prev){
    setperiod(7, on);
    buzz(on ? BUZZ_FREQ : 0);
    prev = on;
  }

  // Update LCD and draw RSSI threshhold if keypress
  if(forced) {
    lcd_number(rssi_thresh);
  }
}

//! Handle a keypress in the receive application.
int receiver_keypress(char ch) {
  if(!ch)
    return 0;

  switch(ch){
    case '+':
      rssi_thresh++;
      break;
    case '-':
      rssi_thresh--;
      break;
    case '=':
      rssi_thresh = radio_getrssi();
      break;
  }

  return 1; // Redraw
}
