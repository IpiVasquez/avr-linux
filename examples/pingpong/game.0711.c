#define F_CPU 16000000UL
#include <avr/interrupt.h>
#include <avr/io.h>
#include <util/delay.h>

int inc = 0;         // Determines where to shift LEDs
int celebrating = 0; // Flag is on if celebrating (avoid interruptions)
int scoreA = 0;      // Player A score (0-3)...
int scoreB = 0;      // Player B score (0-3)...
int speed;

/**
 * A celebration when a player wins! Points LEDs to match winner.
 * Once celebration is over, resets all.
 * @param 1 if player A won, -1 if player B did.
 */
void celebration(int winner) {
  celebrating = 1;
  for (int i = 0; i < 36; i++) {
    // Shift bits to point to winner every 50 ms
    PORTC = winner == 1 ? 0x01 << (i % 6) : PORTC;
    PORTC = winner == -1 ? 0x20 >> (i % 6) : PORTC;
    _delay_ms(50);
  }
  // Reset
  scoreA = 0;
  scoreB = 0;
  PORTC = 0;
  // Deactivating flag
  celebrating = 0;
}

int main() {
  // Specifying outputs
  DDRC = 0x3F; // Gaming LEDs
  DDRA = 0x0F; // Score LEDs
  DDRB = 0x80;
  PORTB = 0;
  {
    // Selecting interruption activation type and initialize interruptions
    // Specify which PINs will be used to interruptions
    PCMSK2 = 0x03; // Last 2
    // Specify which DDRX will use the PINs specified above
    PCICR = 0x01; // DDRB
    // Arduino >> DDRB last to are D53, D52
    sei();
  }
  // Infinite loop
  while (speed = 300)
    // Game ON!
    while (inc) {
      if (inc == 1) {
        // Player A to Player B
        PORTC >>= 1;
        if (!(PORTC & 0x3F))
          PORTC = 0x20;
      } else if (inc == -1) {
        // Player B to Player A
        PORTC <<= 1;
        if (!(PORTC & 0x3F))
          PORTC = 0x01;
      }
      // Updating speed of the 'ball' as delaying
      _delay_ms(speed /= 1.03);
      // Validate if someone won the game
      if ((inc == 1 && PORTC == 0x01) || (inc == -1 && PORTC == 0x20)) {
        inc == 1 ? scoreB++ : scoreA++; // Increment game winner
        if (scoreA == 4 || scoreB == 4) // Match winner ?
          celebration(inc);             // Celebrate!
        inc = PORTC = 0;                // Reset
      }
      // Displaying outputs (only need two bits from each number..)
      PORTA = scoreA & 0x03;
      PORTA <<= 2;
      PORTA |= scoreB & 0x03;
    }

  return 0; // Never gets here but ... old traditions
}

ISR(INT0_vect) {
  inc = (celebrating == 0 && (PORTC == 0x01 || PORTC == 0)) ? -1 : inc;
}

ISR(INT1_vect) {
  inc = (celebrating == 0 && (PORTC == 0x20 || PORTC == 0)) ? 1 : inc;
}

ISR(PCINT2_vect) {
  PORTB = 0x80;
}
