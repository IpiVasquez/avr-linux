#include <avr/interrupt.h>
#include <avr/io.h>

// Report
// System description
// Implementation
// Results
// Apendix
//   Code!
// Spanish: juego_vasquez.pdf
int main() {
  // Setting up ADC
  DIDR0 = 0x00; // Digital input disables for ADC ports
  // MUX => 0000 => PIN0
  // REFS => 01 => Vcc
  // ADLAR => 1 => From 10bits sends 8 to ADCH and 2 to ADCL
  ADMUX = 0x60;
  // ADC and interruption!
  // ADEN => 1 => ADC enabled
  // ADSC => 1 => To start for the first time
  // ADATE => 1 => Auto start
  ADCSRA = 0xEF;
  sei();

  // Specifying output for PWM
  DDRB = 0x80;
  // Timer 0 compares to modulate pulse width
  TCCR0B |= 1 << CS00; // I think PWM's frecuency really doesn't matter
  TCCR0A |= 1 << COM0A1 | 1 << COM0A0 | 1 << WGM00; // Compare to A
  OCR0A = 255;

  while(1);

  return 0; // Never gets here but ... old traditions
}

ISR(ADC_vect) {
  OCR0A = ADCH;
}
