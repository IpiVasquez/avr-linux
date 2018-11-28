#define F_CPU 16000000UL
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

int main(void){
	// Choose which PINs from DDRX selected will be used
	PCMSK2 = 0b00111111;
	// Select DDRX to use
	PCICR = 0b00000100;

	DDRC |= 0b00000111;
	DDRD &= 0b11000000;
	PORTC &= 0b11111000;
	sei();
	while(1){

	}
}


ISR(PCINT2_vect){
	unsigned char puertas = PIND & 0x0F;
	unsigned char cajuela = PIND & 0x10;
	unsigned char cofre = PIND & 0x20;
	//PORTC |= 0b00000001;
	if(puertas)
		PORTC |= 0b00000001;
	else
		PORTC &= 0b11111110;

	if(cajuela)
		PORTC |= 0b00000010;
	else
		PORTC &= 0b11111101;

	if(cofre)
		PORTC |= 0b00000100;

	else
		PORTC &= 0b11111011;
}
