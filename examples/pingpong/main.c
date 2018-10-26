/*
 * interrupciones.c
 * Created: 23/10/18 16:47:20
 * Author : Luis Medina
 */
#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>


int main(void){
    // Se coloca PD4 en salida
	DDRB |= 0b10000000;
	//DDRD &= 0b11110011;
	// Seleccionar tipo de activacion
	EICRA |= 0b00001111;
	// Se activa las interrupciones INT0 e INT1
	EIMSK |= 0b00000011;
	PORTB |= 0b10000000;
	sei();
    while(1){
	}
}

ISR(INT0_vect){
	PORTB |= 0x80;
	//PORTD ^= 0b00010000;
}

ISR(INT1_vect){
	PORTB &= 0b01111111;
}