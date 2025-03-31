#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>


// SAIDAS
// PBx
// PDx
#define MOTOR 0b00000010
#define LED_ON     0b00000100
#define LED_OFF    0b00001000
#define LED_ALARME 0b00010000

// ENTRADAS (OBS: todas as entradas possúem ativação com nivel lógico BAIXO/0)
// PBx
#define BTN_ON 0b00000001
#define BTN_OFF 0b00000010
#define S1 0b00000100
#define S2 0b00001000
#define S3 0b00010000
// PDx
#define CHV1 0b00100000
#define CHV2 0b01000000

// LEITURA
#define LER_DDRD(pin) !(PIND & pin)
#define LER_DDRB(pin) !(PINB & pin)

// TIPOS CAIXAS (Valor maximo para leitura dos sensores)
#define TIPO_PEQUENO 0
#define TIPO_MEDIO   1
#define TIPO_GRANDE  2

int main(void) {
    // CONFIGURACAO PORTAIS
    // saidas
    DDRD |= MOTOR | LED_ON | LED_OFF | LED_ALARME;
    // entradas
    DDRB &= ~(BTN_ON | BTN_OFF | S1 | S2 | S3);
    DDRD &= ~(CHV1 | CHV2);

    
    // PULL-UP INTERNOS
    PORTB |= BTN_ON | BTN_OFF | S1 | S2 | S3;
    PORTD |= CHV1 | CHV2;
    

    // ESTADOS
    // unsigned int state = 0b00000000; // bits: {isOn, chave, -, -, -, -, -, -}
    unsigned int isOn = 0, chave = 0, a;
    
    for(;;){
	// Botao ON e Botao OFF
	if (LER_DDRB(BTN_ON))  isOn = 1;
	if (LER_DDRB(BTN_OFF)) isOn = 0;
	
	if (!isOn) {
	    PORTD |= LED_OFF;
	    PORTD &= ~(LED_ON) & ~(MOTOR);
	    continue;
	}
	// else

	PORTD |= LED_ON;
	PORTD |= MOTOR;
	PORTD &= ~(LED_ALARME | LED_OFF);

	// atualizar chaves
	if (!LER_DDRD(CHV1) && !LER_DDRD(CHV2)) {
	    chave = TIPO_PEQUENO;
	} else if (!LER_DDRD(CHV1) && LER_DDRD(CHV2)) {
	    chave = TIPO_MEDIO;
	} else if (LER_DDRD(CHV1) && !LER_DDRD(CHV2)) {
	    chave = TIPO_MEDIO;
	}

	// verificar sensores
	
	// if (
	// ((a> TIPO_PEQUENO) && (chave == TIPO_PEQUENO)) ||
	// ((a> TIPO_MEDIO)   && (chave == TIPO_MEDIO)) ||
	// ((a> TIPO_GRANDE)  && (chave == TIPO_GRANDE))
	// ) {
	//     isOn = 0;
	//     PORTD |= LED_ALARME;
	// }
	
	 if  ( LER_DDRB(S3) && (chave == TIPO_MEDIO || chave == TIPO_GRANDE)) {
	    // desligar, ativar led alarme
	    isOn = 0;
	    PORTD |= LED_ALARME;
	}
	 if  ( LER_DDRB(S2) && (chave == TIPO_GRANDE)) {
	    // desligar, ativar led alarme
	    isOn = 0;
	    PORTD |= LED_ALARME;
	}

    }
}
