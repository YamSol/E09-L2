#include <avr/io.h>
#include <avr/interrupt.h>
#define F_CPU 10000000UL
#include <util/delay.h>

#define LED (1 << PD6)
#define BOTAO (1 << PB0)
#define BOTAO_ATIVO ((PINB & BOTAO) == 0)

unsigned int contagem = 0;

void set_ocr0a(int duty_cycle_value) {
    if (duty_cycle_value < 0 || duty_cycle_value > 100) {
        return;
    }
    OCR0A = (int)((duty_cycle_value / 100.0) * 255);
}

int main() {
    DDRD |= LED; // PD6 como saída
    PORTB |= BOTAO; // Ativa pull-up no PB0
    
    // Configura PWM
    TCCR0A |= (1 << COM0A1) | (1 << WGM01) | (1 << WGM00);
    TCCR0B |= (1 << CS02) | (1 << CS00); // Pre-Scaler 1024

    set_ocr0a(0); // Inicia PWM desligado

    // Configura interrupção
    PCICR = (1 << PCIE0);
    PCMSK0 |= BOTAO; 
    sei(); // Ativa interrupções globais
    
    for (;;) {
        // Loop vazio
    }
}

ISR(PCINT0_vect) {
    _delay_ms(50); // Debounce
    if (BOTAO_ATIVO) {
        return;
    }

    contagem += 10; // Aumenta contagem

    if (contagem > 100) {
        contagem = 0; // Reseta contagem
        set_ocr0a(0); // Desliga LED
    } else {
        set_ocr0a(contagem); // Atualiza LED
    }
}
