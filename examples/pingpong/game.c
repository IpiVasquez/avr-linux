#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

int inc = 0;
int scoreA = 0;
int scoreB = 0;

int main() {
  DDRD = 0x03;
  DDRB = 0x80;
  DDRC = 0x3F;
  DDRA = 0x0F;
  // Selecting activation type
  EICRA |= 0x0F;
  EIMSK |= 0x03;
  sei();
  PORTB = 0x80;
  while (1) {
    while(inc) {
      if (inc > 0) {
        PORTC >>= 1;
        if (!(PORTC & 0x3F)) {
          PORTC = 0x20;
        }
      } else if (inc < 0) {
        PORTC <<= 1;
        if (!(PORTC & 0x3F)) {
          PORTC = 0x01;
        }
      }
      _delay_ms(400);
      if (inc == 1 && PORTC == 0x01) {
        scoreB++;
        inc = PORTC = 0;
      } else if (inc == -1 && PORTC == 0x20) {
        scoreA++;
        inc = PORTC = 0;
      }
      PORTA = scoreA & 0x03;
      PORTA <<= 2;
  PORTA |= scoreB;
    }
  }
  return 0;
}

ISR(INT0_vect) {
  PORTB = 0x80;
  if (PORTC == 0x01 || PORTC == 0) {
    inc = -1;
  }
}

ISR(INT1_vect) {
  PORTB = 0x00;
  if (PORTC == 0x20 || PORTC == 0) {
    inc = 1;
  }
}
