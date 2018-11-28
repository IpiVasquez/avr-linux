#define F_CPU 16000000UL
#define tiempo 1000
#include <avr/io.h> /* Definición de los pines, puertos, etc */
#include <avr/interrupt.h>
#include <util/delay.h> /* Retardos */
int p1=0, p2=0, dir=1, led=1;
int inicio = 0;

int main(void) {
	EICRA = 0b00001111;
	EIMSK = 0b00000011;

	PCMSK2 = 0b00000011;
	PCICR = 0b00000100;
	

	sei();
	DDRB |= (1 << PB5); DDRB |= (1 << PB4); DDRB |= (1 << PB3); DDRB |= (1 << PB2); DDRB |= (1 << PB1); DDRB |= (1 << PB0);
	DDRC |= (1 << PC5); DDRC |= (1 << PC4); DDRC |= (1 << PC3); DDRC |= (1 << PC2); DDRC |= (1 << PC1); DDRC |= (1 << PC0);
	_delay_ms(tiempo);
	while (1){
		if(inicio){
			if(p1 == 7){
				PORTC = 0b00000111;
				_delay_ms(tiempo/5);
				PORTC = 0b00000000;
				_delay_ms(tiempo/5);
				PORTB = 0b00000000;
			}
			else if(p2 == 7){
				PORTC = 0b00111000;
				_delay_ms(tiempo/5);
				PORTC = 0b00000000;
				_delay_ms(tiempo/5);
				PORTB = 0b00000000;
			}
			else{
				PORTB = led;
				int temp = p2 << 3;
				temp += p1;
				PORTC = temp;
				_delay_ms(tiempo);
				if(dir)
				led <<= 1;
				else
				led >>= 1;
				if(led == 0b10000000 && dir == 1){
					p1++;
					led = 1;
					inicio = 0;
					_delay_ms(tiempo/5);
				}
				if(led == 0 && dir == 0){
					p2++;
					led = 0b00100000;
					inicio=0;
					_delay_ms(tiempo/5);
				}
			}
		}
	}
}
ISR(INT0_vect){
	//push del jugador
	if(led == 0b00000001)
	dir=1;
}
ISR(INT1_vect){
	//push del jugador 2
	if(led == 0b00100000);
	dir=0;
}

ISR(PCINT2_vect){
	inicio = 1;
}
