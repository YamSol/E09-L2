#define RX_BUFFER_SIZE 10

#define LED_VERDE PD3
#define LED_VERMELHO PD4
#define SET_VERDE PORTD |= (1<<LED_VERDE);
#define CLEAR_VERDE PORTD &= ~(1<<LED_VERDE);
#define SET_VERMELHO PORTD |= (1<<LED_VERMELHO);
#define CLEAR_VERMELHO PORTD &= ~(1<<LED_VERMELHO);

char RX_index = 0;
char RX_buffer[RX_BUFFER_SIZE];
char msg_tx[20];
char old_rx_hs[RX_BUFFER_SIZE];
 
// A inicialização do UART consiste em definir a taxa de transmissão,
// definir o formato de quadro, e ativar o Transmissor ou o receptor. 
void UART_init(int baud);
void UART_send(char *TX_buffer);
void limpa_RX_buffer(void);

int main()
{
    // Configuração do UART
    UART_init(9600);
		
		// Configurar leds
		DDRD |= (1<<LED_VERDE)|(1<<LED_VERMELHO);
		PORTD = 0;

    sei();

    while (1) {
			

			// Delay de 1s
			_delay_ms(1000);

			switch(RX_buffer[0]) {
			case '8':
				SET_VERMELHO;
				CLEAR_VERDE;
				UART_send("Estado 1\n");
				break;
			case '9':
				SET_VERDE;
				CLEAR_VERMELHO;
				UART_send("Estado 2\n");
				break;
			}

			/* _delay_ms(200); */

			// Limpa o buffer
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
    while (UCSR0A & (1 << RXC0))
    {
        // Lê o dado
        dummy = UDR0;
    }
 
    // Reseta o índice
    RX_index = 0;
 
    // Limpa todos os dados do buffer
    for (int i = 0; i < RX_BUFFER_SIZE; i++)
    {
        old_rx_hs[i] = RX_buffer[i];
        RX_buffer[i] = 0;
    }
}
 
// Função ISR que salva um array de dados recebidos via UART
ISR(USART_RX_vect) {
    // Salva o dado recebido
    RX_buffer[RX_index] = UDR0;
    RX_buffer[RX_index +1] = 0;
 
    //UART_send("Recebido\n");
 
    // Adiciona mais 1 na contagem
    RX_index++;
}
 
