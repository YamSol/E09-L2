#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define F_CPU 16000000UL  // Define CPU frequency as 16 MHz


//INT0 == PD2
//INT1 == PD3

#define LED1 (1<<PD5)
#define LED2 (1<<PD4)

int main(){

    DDRD |= LED1 | LED2; //ativar saida para portas LED1 e LED2
    PORTD |= (1<<PD2) | (1<<PD3); // ativar pull-up do botao PD2 e PD3 para INT0 e INT1
    
    
    EICRA |= (1<<ISC01) | (1<<ISC00); // 0b00000011 ativar transicao de subida para INT0
    EICRA |= (1<<11); // 0b00001000 ativar transicao de descida para INT1
    
    EIMSK |= (1<<INT0); // ativar INT0
    EIMSK |= (1<<INT1); // ativar INT1

    sei();

    for(;;) {;
	PORTD ^= LED1;
	_delay_ms(2000);
    }
}

ISR(INT0_vect) {
    PORTD |= LED2;
    _delay_ms(4000);
    PORTD &= ~(LED2);
}

ISR(INT1_vect) {
    EIMSK ^= (1<<INT0); // alterar o estado do INT0
}
