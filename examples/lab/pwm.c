#include <avr/io.h>
#include <avr/interrupt.h>

void blink();
void interruptions();
void probing();

int main() {
  // Timer settings
  TCCR0A = (TCCR0A & 0xF6) | 0x00;
  TCCR0B = (TCCR0B & 0xF0) | 0x01;
  // LED to blink
  DDRB = 0x80;
  interruptions();
  // probing();

  return 0;
}

void interruptions() {
  TIMSK0 = 1;
  sei();
  while (1);
}

void probing() {
  while(1) {
    if (TIFR0 & 0x01) {
      blink();
      TIFR0 |= 0x01;
    }
  }
}

void blink() {
  PORTB = PORTB ^ 0x80;
}

ISR(TIMER0_OVF_vect) {
  blink();
}