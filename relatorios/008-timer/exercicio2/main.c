#include <avr/io.h>
#include <avr/interrupt.h>

#define LED_1 (1<<PD0)
#define LED_2 (1<<PD1) 
#define SET_LED_1 PORTD |= LED_1
#define CLEAR_LED_1 PORTD &= ~LED_1
#define SET_LED_2 PORTD |= LED_2
#define CLEAR_LED_2 PORTD &= ~LED_2

unsigned int count_1 = 0;
unsigned int count_2 = 0;

void enable_timer();

int main(void) {
    enable_timer();

    DDRD |= LED_1 | LED_2;

    sei();
    for(;;) {

    }
}

void enable_timer() {
    TCCR0A |= (1<<WGM01);
    TCCR0B |= (1<<CS02) | (1<<CS00);
    OCR0A  = 255;
    TIMSK0  |= (1<<OCIE0A);
}

ISR(TIMER0_COMPA_vect) {
    // CONFIGURAÇÃO: 64us * 255 -> 16,32ms
    // | 61.27 (contagem)	= 1s
    // | 6.12			= 100ms
    // | 3676			= 60s
    count_1++; // contador de 1 segundo para led 1    
    count_2++; // contador de 60 segundos para led 2

    if(count_1 >= 61) {
	SET_LED_1;
	count_1 = 0;
    }
    if (count_1 == 6) {
	CLEAR_LED_1;
    }


    
    if(count_2 >= 3676) {
	SET_LED_2;
	count_2 = 0;
    }
    if (count_2 == 6) {
	CLEAR_LED_2;
    }

}
