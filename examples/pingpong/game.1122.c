#include <avr/interrupt.h>
#include <avr/io.h>

int inc = 0;    // Determina hacia donde recorrer LEDs
int scoreA = 0; // Jugador A score (0-3)...
int scoreB = 0; // Jugador B score (0-3)...

/**
 * Reset.
 * @param 1 si jugador A gana, -1 jugador B.
 */
void resetPort(int winner) {
  // Reset
  scoreA = 0;
  scoreB = 0;
  PORTC = 0;
}

int main() {
  // Especifica salidas
  // LEDs del juego: 32, 33, ..., 37
  DDRC |= 1 << PC5 | 1 << PC4 | 1 << PC3 | 1 << PC2 | 1 << PC1 | 1 << PC0;
  // LEDs del marcador: 25, 24, 23, 22
  DDRA |= 1 << PA0 | 1 << PA1 | 1 << PA2 | 1 << PA3;
  {
    // Interrupciones externas
    EICRA |= 0x0F; // Flanco de subida
    EIMSK |= 0x03; // Interrupciones externas 0 & 1
    // Interruciones del Timer
    TCCR1B |= 1 << WGM12;            // CTC
    TCCR1B |= 1 << CS12 | 1 << CS10; // Prescalador 1024
    TIMSK1 |= 1 << OCIE1A;           // Permite interrupción
    // Interrupciones del ADC
    DIDR0 = 0;
    ADMUX |= 1 << REFS0 | 1 << ADLAR;
    ADCSRA |= 1 << ADIE | 1 << ADATE | 1 << ADSC | 1 << ADEN;
    ADCSRA |= 1 << ADPS2 | 1 << ADPS1 | 1 << ADPS0;
    sei();
  }
  // Ciclo infinito
  while (1)
    // Pelota en juegao
    while (inc) {
      // Valida si alguien gano
      if (inc && (PORTC & 0x3F) == 0) {
        inc == 1 ? scoreB++ : scoreA++; // Incrementa el ganador
        if (scoreA == 4 || scoreB == 4) // Verifica si alguien gano la partida
          resetPort(inc);               // Reset scores
        inc = PORTC = 0;                // Reset quien tiene la pelota
        TCCR1B &= ~(1 << CS12 | 1 << CS10);
        // Configura para activar la interrupción del ADC
        ADCSRA |= 1 << ADIE | 1 << ADATE | 1 << ADSC;
      }
      // Desplegando salidas (Sólo dos bits de cada número)
      PORTA = (scoreA << 2) & 0b1100 | (scoreB & 0b0011);
    }

  return 0;
}

// Movimientos del jugador A
ISR(INT0_vect) {
  if (inc)
    inc = (PORTC == (1 << PC0) || PORTC == 0) ? -1 : inc;
  else {
    PORTC = 1 << PC0;
    inc = -1;
    // Desactiva si la pelota esta en juego
    ADCSRA &= ~(1 << ADIE | 1 << ADATE | 1 << ADSC);
    TCCR1B |= 1 << CS12 | 1 << CS10;
  }
}

// Movimientos del jugador B
ISR(INT1_vect) {
  if (inc)
    inc = (PORTC == (1 << PC5) || PORTC == 0) ? 1 : inc;
  else {
    PORTC = 1 << PC5;
    inc = 1;
    // Desactiva si la pelota esta en juego
    ADCSRA &= ~(1 << ADIE | 1 << ADATE | 1 << ADSC);
    TCCR1B |= 1 << CS12 | 1 << CS10;
  }
}

// Mueve la bola
ISR(TIMER1_COMPA_vect) {
  if (inc == 1)
    // Jugador A a Jugador B
    PORTC >>= 1;
  else if (inc == -1)
    // Jugador B a Jugador A
    PORTC <<= 1;
}

// Cambia velocidad
ISR(ADC_vect) {
  OCR1A = ADCH;
  OCR1A <<= 6;
}
