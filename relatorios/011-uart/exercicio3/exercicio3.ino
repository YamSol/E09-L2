#include <stdint.h>
#include <stdlib.h>

#define RX_BUFFER_SIZE 3

#define LED PD6

char RX_index = 0;
char RX_buffer[RX_BUFFER_SIZE];
char old_rx_hs[RX_BUFFER_SIZE];
unsigned int duty_cycle = 0;
char tx_msg[20];
 
// A inicialização do UART consiste em definir a taxa de transmissão,
// definir o formato de quadro, e ativar o Transmissor ou o receptor. 
void UART_init(int baud);
void UART_send(char *TX_buffer);
void limpa_RX_buffer(void);
void set_ocr0a(int duty_cycle);
void PWM_init();
void PWM_update();

int main() {
  // Configurar leds
  DDRD |= (1<<LED);
  PORTD = 0;
  
  UART_init(9600);	 
  PWM_init();
  
  sei();
  while (1) {
    
    // Delay de 1s
    _delay_ms(1000);
    
    itoa(duty_cycle, tx_msg, 10);
    UART_send("num:");
    UART_send(tx_msg);
    UART_send("\n");

		duty_cycle = atoi(RX_buffer);
		if (duty_cycle != 0) {
			PWM_update(duty_cycle);
    }

    limpa_RX_buffer();
  }		
}

 
// Função de configuração do UART
void UART_init(int baud) {
  // Calcula a taxa de transmissão
  int MYUBRR = 16000000 / 16 / baud - 1;
  
  // Definindo a taxa de transmissão
  UBRR0H = (unsigned char)(MYUBRR >> 8);
  UBRR0L = (unsigned char)(MYUBRR);
  
  // Definindo o formato de quadro, 8 bits e 1 stop bit
  UCSR0C = (0 << USBS0) | (1 << UCSZ00) | (1 << UCSZ01);
		
  // Ativa o Transmissor, receptor e define a interrupção
  UCSR0B = (1 << RXEN0) | (1 << TXEN0) | (1 << RXCIE0);
}
 
// Função para envio de dados via UART
void UART_send(char *TX_buffer) {
  // Enquanto tiver caracteres para enviar
  while (*TX_buffer != 0) {
    // Prepara o buffer para o envio
    UDR0 = *TX_buffer;
 
    // Espera o envio ser completado
    while (!(UCSR0A & (1 << UDRE0))){};
 
    // Avança o ponteiro do buffer
    TX_buffer++;
  }
}
 
// Limpa o buffer de entrada e saída
void limpa_RX_buffer(void) {
  unsigned char dummy;
 
  // Enquanto houver dados no buffer
  while (UCSR0A & (1 << RXC0)) {
      // Lê o dado
      dummy = UDR0;
	}
 
  // Reseta o índice
  RX_index = 0;
 
  // Limpa todos os dados do buffer
  for (int i = 0; i < RX_BUFFER_SIZE; i++) {
      old_rx_hs[i] = RX_buffer[i];
      RX_buffer[i] = 0;
	}
}
 
// Função ISR que salva um array de dados recebidos via UART
ISR(USART_RX_vect) {
  // Salva o dado recebido
  RX_buffer[RX_index] = UDR0;
  RX_buffer[RX_index +1] = 0; 
  // Adiciona mais 1 na contagem
  RX_index++;

}

void PWM_init() {	
  // Configura PWM
  TCCR0A |= (1 << COM0A1) | (1 << WGM01) | (1 << WGM00);
  TCCR0B |= (1 << CS02) | (1 << CS00); // Pre-Scaler 1024
  // inicia o estado do OCR0A
  PWM_update(0);
}

// Função PWM que seta o valor do OCR0A de acordo com o duty cycle
void PWM_update(int duty_cycle) {
  if (duty_cycle < 0 || duty_cycle > 100) {
    return;
  }		
  OCR0A = (int)((duty_cycle / 100.0) * 255);
}
