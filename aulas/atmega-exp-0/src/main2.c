#define F_CPU 1000000UL

#include <avr/io.h>
#include <util/delay.h>


int main() {

    DDRD |= (1<<PORTD0);
    PORTD = 0;

    while(1){
	
	PORTD ^= (1<<PORTD0);
	_delay_ms(500);
	
    }
}

