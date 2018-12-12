#include <avr/interrupt.h>
#include <avr/io.h>
#include <inttypes.h>

#define F_CPU 16000000UL //  CPU clk
#define BAUD 9600
#define BAUDRATE (F_CPU / (BAUD * 16UL) - 1)

void init() {
  // Baud ...
  UBRR0L = BAUDRATE;
  UBRR0H = BAUDRATE >> 8;
  // Asincrono
  // Sin paridad
  // 1 bit de paro
  // tama;o de caracter 8
  UCSR0C = (1 << 7) | (3 << UCSZ00);
  // Habilita recibo y envio
  UCSR0B = (1 << RXEN0) | (1 << TXEN0);
}

// Lee
char rx() {
  // Espera en lo que llegan datos
  while (!(UCSR0A & (1 << RXC0)))
    ;
  // Wuw valor!
  return UDR0;
}

// Envia algun caracter
void tx(char data) {
  // Espera a que este listo el transmisor
  while (!(UCSR0A & (1 << UDRE0)))
    ;

  // Escribe en el buffer
  UDR0 = data;
}

void main() {
  char data;
  DDRC = 0xFF;
  DDRB = 0x80;
  init();

  // Interrupciones externas
  EICRA |= 0x0F; // Flanco de subida
  EIMSK |= 0x03; // Interrupciones externas 0
  sei();

  while (1) {
    // Lee
    data = rx();
    // Cuando recibas, devuelvelo
    PORTC = data;
  }
}

ISR(INT0_vect) {
  PORTB = !PORTB;
  tx('0');
  tx('\n');
}