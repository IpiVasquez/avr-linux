#include <avr/io.h>
// http://winavr.scienceprog.com/example-avr-projects/4x4-keypad-example-using-avr-gcc-c-language.html
int main() {
  // high nibble for output(columns) low for input(rows);
  DDRC = 0xF0;
  // enable internal pullups for PB0-PB3
  PORTC = 0x0F;
  // Port D for indication only
  DDRD = 0xFF;
  while (1) // loop key check forever
  {
    // first column
    PORTC = 0b01111111;
    // check for rows and send key number to portD
    // instead sending key number to PORTD you can use
    // any function that serves pressed button
    if (bit_is_set(PINC, 3))
      PORTD = 1;
    if (bit_is_set(PINC, 2))
      PORTD = 2;
    if (bit_is_set(PINC, 1))
      PORTD = 3;
    if (bit_is_set(PINC, 0))
      PORTD = 4;
    // second column
    PORTB = 0b10111111;
    if (bit_is_set(PINC, 3))
      PORTD = 5;
    if (bit_is_set(PINC, 2))
      PORTD = 6;
    if (bit_is_set(PINC, 1))
      PORTD = 7;
    if (bit_is_set(PINC, 0))
      PORTD = 8;
    // third column
    PORTB = 0b11011111;
    if (bit_is_set(PINC, 3))
      PORTD = 9;
    if (bit_is_set(PINC, 2))
      PORTD = 10;
    if (bit_is_set(PINC, 1))
      PORTD = 11;
    if (bit_is_set(PINC, 0))
      PORTD = 12;
    // fourth column
    PORTB = 0b11101111;
    if (bit_is_set(PINC, 3))
      PORTD = 13;
    if (bit_is_set(PINC, 2))
      PORTD = 14;
    if (bit_is_set(PINC, 1))
      PORTD = 15;
    if (bit_is_set(PINC, 0))
      PORTD = 16;
  }
}