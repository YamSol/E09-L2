#include <avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>

// Definição dos tipos de caixa
#define TIPO_PEQUENO 0
#define TIPO_MEDIO   1
#define TIPO_GRANDE  2

// Saídas
#define MOTOR     (1 << PD1)
#define LED_ON    (1 << PD2)
#define LED_OFF   (1 << PD3)
#define LED_ALARM (1 << PD4)

// Entradas (todas com lógica negativa)
#define BTN_ON   (1 << PB0)
#define BTN_OFF  (1 << PB1)
#define S1       (1 << PB2)
#define S2       (1 << PB3)
#define S3       (1 << PB4)
#define CHV1     (1 << PD5)
#define CHV2     (1 << PD6)

// Macros de leitura
#define BTN_ON_PRESSED   (!(PINB & BTN_ON))
#define BTN_OFF_PRESSED  (!(PINB & BTN_OFF))
#define S1_ATIVO         (!(PINB & S1))
#define S2_ATIVO         (!(PINB & S2))
#define S3_ATIVO         (!(PINB & S3))
#define CHV1_ATIVA       (!(PIND & CHV1))
#define CHV2_ATIVA       (!(PIND & CHV2))

// Macro de interrupção do Motor
#define PARAR_E_ALARME() do { \
    isOn = 0;                 \
    PORTD |= LED_ALARM;       \
} while(0);                   \

int main(void) {
    // Configuração de portas
    DDRD |= MOTOR | LED_ON | LED_OFF | LED_ALARM;
    DDRB &= ~(BTN_ON | BTN_OFF | S1 | S2 | S3);
    DDRD &= ~(CHV1 | CHV2);
    
    // Ativar pull-ups
    PORTB |= BTN_ON | BTN_OFF | S1 | S2 | S3;
    PORTD |= CHV1 | CHV2;
    
    // Estados
    uint8_t isOn = 0, tipo_caixa = TIPO_PEQUENO;
    
    for(;;) {
        // Controle ON/OFF
        if (BTN_ON_PRESSED)  isOn = 1;
        if (BTN_OFF_PRESSED) isOn = 0;
        
        if (!isOn) {
            PORTD |= LED_OFF;
            PORTD &= ~(LED_ON | MOTOR);
            continue;
        }
        
        // Sistema ligado
        PORTD |= LED_ON | MOTOR;
        PORTD &= ~(LED_OFF | LED_ALARM);
        
        // Determinar tipo de caixa
        if (!CHV1_ATIVA && !CHV2_ATIVA) {
            tipo_caixa = TIPO_PEQUENO;
        } else if (!CHV1_ATIVA && CHV2_ATIVA) {
            tipo_caixa = TIPO_MEDIO;
        } else if (CHV1_ATIVA && !CHV2_ATIVA) {
            tipo_caixa = TIPO_GRANDE;
        }

        // Verificar sensores conforme tipo de caixa
        if (tipo_caixa == TIPO_PEQUENO && (S1_ATIVO || S2_ATIVO)) {
	    PARAR_E_ALARME();
	} else if (tipo_caixa == TIPO_MEDIO && S1_ATIVO) {
	    PARAR_E_ALARME();
        }
    }
}
