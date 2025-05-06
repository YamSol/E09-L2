#include <avr/io.h>
#include <avr/interrupt.h>

#define F_CPU 16000000UL
#include <util/delay.h>

#define LED5 (1<<PD5)
#define LED5_DELAY 250
#define LED5_ON  PORTD |= LED5
#define LED5_OFF PORTD &= ~(LED5)

#define LED7 (1<<PD7)
#define LED7_DELAY 1000
#define LED7_ON  PORTD |= LED7
#define LED7_OFF PORTD &= ~(LED7)

#define LED6 (1<<PD6)
#define LED6_DELAY 500
#define LED6_ON  PORTD |= LED6
#define LED6_OFF PORTD &= ~(LED6)

#define LED15 (1<<PB1)
#define LED15_DELAY 2000
#define LED15_ON  PORTB |= LED15
#define LED15_OFF PORTB &= ~(LED15)

#define BTN1 (1<<PB0) // PCINT0 -> PB0 
#define BTN1_ATIVADO ((PINB & BTN1) == 0)

#define BTN2 (1<<PB2) // PCINT2 -> PB2
#define BTN2_ATIVADO ((PINB & BTN2) == 0)

#define BTN3 (1<<PD4) // PCINT20 -> PD4
#define BTN3_ATIVADO ((PIND & BTN3) == 0)


ISR(PCINT0_vect) {
  if (BTN1_ATIVADO) {
    LED7_ON;
    _delay_ms(LED7_DELAY);
    LED7_OFF;
  }

  if (BTN2_ATIVADO) {
    LED6_ON;
    _delay_ms(LED6_DELAY);
    LED6_OFF;
  }
  
}


ISR(PCINT2_vect) {
    if (BTN3_ATIVADO) {
    LED15_ON;
    _delay_ms(LED15_DELAY);
    LED15_OFF;
  }

}

int main(void) {

  DDRD |= LED5 | LED6 | LED7;
  DDRB |= LED15;

  // ativar pull-up interno das entradas
  PORTB |= BTN1 | BTN2;
  PORTD |= BTN3;

  // ativar os 3 Registradores de interrupção PCI
  PCICR |= (1<<PCIE2) | (1<<PCIE0);

  // ativar a interrupcao nos pinos PCINT0, 2 e 20
  PCMSK0 |= (1<<PCINT2) | (1<<PCINT0);
  PCMSK2 |= (1<<PCINT20);

  
  sei();
  for(;;) {
    PORTD ^= LED5;
    _delay_ms(LED5_DELAY);
  }
}
