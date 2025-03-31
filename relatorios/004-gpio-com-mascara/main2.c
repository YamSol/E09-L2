
#define P4 0b00010000
#define P5 0b00100000
#define P6 0b01000000
#define P7 0b10000000

// inline void function DELAY(int btn1, int btn2) {
//     if (btn1 == 0) {
// 	_delay_ms(100);
//     }
//     if (btn2 == 0) {
// 	_delay_ms(1000);
//     }
// }

#define DELAY(btn1, btn2) do { \
    if (btn1 == 0) {           \
	_delay_ms(100);        \
    }                          \
    if (btn2 == 0) {           \
	_delay_ms(1000);       \
    }                          \
    } while(0);

int main(void) {
    
    DDRD |= P7 | P6; // Pino P7 e P6 definido como saída
    
    PORTD |= P5 | P4; // Habilitar PULL-UP no P5 e P4
    
    PORTD &= ~(P7) & ~(P6); // Desliga a saída P7 e a saida P6

    unsigned int estado_atual = P7;
    
    for (;;) {
	int btn1 = PIND & P5; // Lê o estado do P5
	int btn2 = PIND & P4; // Lê o estado do P5

	
	// DELAY, de acordo com o botao pressionado
	DELAY(btn1, btn2);
	// Liga o LED
	PORTD |= estado_atual; // P7 ou P6 -> HIGH

	// DELAY, de acordo com o botao pressionado
	DELAY(btn1, btn2);
	// Desliga o LED
	PORTD &= ~(estado_atual); // P7 ou P6-> LOW

	// atualizar estado
	switch(estado_atual) {
	case P6:
	    estado_atual = P7;
	    break;
	case P7:
	    estado_atual = P6;
	    break;
	default:
	    estado_atual = P7;
	    break;
	}
		
    }
}
