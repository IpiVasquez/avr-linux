#include <avr/interrupt.h>
#include <avr/io.h>

int inc = 0;         // Determines where to shift LEDs
int scoreA = 0;      // Player A score (0-3)...
int scoreB = 0;      // Player B score (0-3)...
int speed;

/**
 * Resets all.
 * @param 1 if player A won, -1 if player B did.
 */
void celebration(int winner) {
  // Reset
  scoreA = 0;
  scoreB = 0;
  PORTC = 0;
}

int main() {
  // Specifying outputs
  DDRC = 0x3F; // Gaming LEDs: 32, 33, ..., 37
  DDRA = 0x0F; // Score LEDs: 25, 24, 23, 22
  {
    // Selecting interruption activation type and initialize interruptions
    EICRA |= 0x0F; // Down to up
    EIMSK |= 0x03; // External interruption 0 & 1
    // Timer interruptions
    TIMSK1 |= 1 << OCIE1A; // Interrupt on cmp A = true
    // OCR1AH =0x1; // Number to compare | (first 8 bits)
    // OCR1AL = 0; // Number to compare | (last 8 bits)
    OCR1A = 0x008;
    TCCR1A |= 0x00;
    TCCR1B |= 1 << CS11 | 1 << CS10;
    TCCR1C |= 0x80;
    // ADC interruptions
    DIDR0 = 0;
    ADMUX = 0x60;
    ADCSRA = 0xEF;
    sei();
  }
  // Infinite loop
  while (1)
    // Game ON!
    while (inc) {
      // Validate if someone won the game
      if (inc && (PORTC & 0x3F) == 0) {
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

// Handle player moves
ISR(INT0_vect) {
  if (inc)
    inc = (PORTC == 0x01 || PORTC == 0) ? -1 : inc;
  else {
    PORTC = 0x01;
    inc = -1;
  }
}

// Handle player moves
ISR(INT1_vect) {
  if (inc)
    inc = (PORTC == 0x20 || PORTC == 0) ? 1 : inc;
  else {
    PORTC = 0x20;
    inc = 1;
  }
}

// Moves the ball
ISR(TIMER1_COMPA_vect) {
  if (inc == 1)
    // Player A to Player B
    PORTC >>= 1;
  else if (inc == -1)
    // Player B to Player A
    PORTC <<= 1;

}

ISR(ADC_vect) {
  OCR1AL = ADCH;
}