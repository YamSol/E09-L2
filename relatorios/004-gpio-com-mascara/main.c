
#define PD4 0b00010000
#define PD5 0b00100000
#define PD6 0b01000000
#define PD7 0b10000000

int main(void) {
    
    DDRD |= PD7 | PD6; // Pino PD7 e PD6 definido como saída
    
    PORTD |= PD5 | PD4; // Habilitar PULL-UP no PD5 e PD4
    
    PORTD &= ~(PD7) & ~(PD6); // Desliga a saída PD7 e a saida PD6
    
    for (;;) {
	int btn1 = PIND & PD5; // Lê o estado do PD5
	int btn2 = PIND & PD4; // Lê o estado do PD5
	
	if (btn1 == 0) // Botão 2 (acionado em 0)
	{
	    PORTD |= PD7; // PD7 -> HIGH
	    _delay_ms(1000);
	    PORTD &= ~(PD7); // PD7 -> LOW
	}

	if (btn2 == 0) // Botão 2 (acionado em 0)
	{
	    PORTD |= PD6; // PD7 -> HIGH
	    _delay_ms(1000);
	    PORTD &= ~(PD6); // PD7 -> LOW
	}
		
    }
}
