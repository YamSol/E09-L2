#include <avr/io.h>
#include <avr/interrupt.h>


#define LED (1<<PD6)

#define BTN (1<<PB0)
#define BTN_ON  PORTD |= BTN
#define BTN_OFF PORTD &= ~BTN
#define IS_BTN_PRESSED ((PINB & BTN) == 0)

#define SET_OCR0A(dc_value) ((dc_value >= 0 && dc_value <= 100) ? (int)((dc_value / 100.0) * 255) : 0)

void enable_pwm();

int main() {
    
    DDRD |= LED;
    PORTD &= ~LED;

    PORTB |= BTN;
    enable_pwm();

    PCICR = (1 << PCIE0);
    PCMSK0 |= BTN;
    
    sei();

    
    for(;;){
	
    }
}


void enable_pwm() {
    TCCR0A |= (1<<COM0A1); // set OC0A at BOTTOM (non-inverting mode)
    TCCR0A |= (1<<WGM01) | (1<<WGM00); // enable mode Fast PWM
    
    TCCR0B |= (1<<CS02) | (1<<CS00); // enable a HIGH pre-scaler. OBS: always use HIGH value.

}

ISR(PCINT0_vect) {
    if((PINB & BTN) == 0) {
	OCR0A = 127;
    }
    else {
	OCR0A = 0;
    }
}
	
