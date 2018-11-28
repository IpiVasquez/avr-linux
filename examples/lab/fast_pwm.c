#include <avr/io.h>
#include <avr/interrupt.h>

void resetTimer();

int inc = 2;

int main() {
  // Blinking LED
  DDRB = 0x80;
  // Timer 1 on overflow to change pulse width
  TCCR1B |= 1 << CS01; // clk / 1024
  resetTimer();
  TIMSK1 |= 2; // A CompA interruption
  sei();
  // Timer 0 compares to modulate pulse width
  TCCR0B |= 1 << CS00; // | 1 << WGM02; // clk / 1024
  TCCR0A |= 1 << COM0A1 | 1 << COM0A0 | 1 << WGM00; // Compare to A
  OCR0A = 0;

  while (1) { }

  return 0;
}

ISR(TIMER1_COMPA_vect) {
  resetTimer();
  if (OCR0A < 5 && inc < 0)
    inc = 2;
  if (OCR0A == 250 && inc > 0)
    inc = -2;
  OCR0A += inc;
}

void resetTimer() {
  OCR1AH = 0x00;
  OCR1AL = 0x01;
}