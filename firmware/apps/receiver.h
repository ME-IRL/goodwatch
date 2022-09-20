/*! \file receiver.h
  \brief Radio morse receiver
*/

//! Enter the receive app.
void receiver_init();

//! Exit the receive app.
int receiver_exit();

//! Draw the screen
void receiver_draw(int forced);

//! Handle a keypress in the receive application.
int receiver_keypress(char ch);
