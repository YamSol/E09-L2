// Variáveis para entrada e saída
char RX_buffer[32];
char RX_index = 0;
unsigned int cont = 0;
 
char msg_tx[20];
 
// Buffer para estado anterior do RX
char old_rx_hs[32];
 
// A inicialização do UART consiste em definir a taxa de transmissão,
// definir o formato de quadro, e ativar o Transmissor ou o receptor.
 
// Função de configuração do UART
void UART_init(int baud)
{
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
void UART_send(char *TX_buffer)
{
    // Enquanto tiver caracteres para enviar
    while (*TX_buffer != 0)
    {
        // Prepara o buffer para o envio
        UDR0 = *TX_buffer;
 
        // Espera o envio ser completado
        while (!(UCSR0A & (1 << UDRE0))){};
 
        // Avança o ponteiro do buffer
        TX_buffer++;
    }
}
 
// Limpa o buffer de entrada e saída
void limpa_RX_buffer(void)
{
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
    for (int i = 0; i < 32; i++)
    {
        old_rx_hs[i] = RX_buffer[i];
        RX_buffer[i] = 0;
    }
}
 
// Função ISR que salva um array de dados recebidos via UART
ISR(USART_RX_vect)
{
    // Salva o dado recebido
    RX_buffer[RX_index] = UDR0;
    RX_buffer[RX_index +1] = 0;
 
    //UART_send("Recebido\n");
 
    // Adiciona mais 1 na contagem
    RX_index++;
}
 
ISR(INT0_vect){ //INTERRUPCAO
    cont ++;
    itoa(cont, msg_tx, 10);
            // Envia o dado recebido
        UART_send(msg_tx);
        UART_send("\n");
				_delay_ms(50);
  }
 
int main()
{
    // Configuração do UART
    UART_init(9600);
    DDRD = 0;
		PORTD |= (1<<PD2);
    EICRA |= (1<< ISC00)|(1<< ISC01);
    EIMSK |= (1<<INT0);
    // Habilitando a interrupção
    sei();
 
    // Super Loop
    while (1)
    {

        // Delay de 1s
        _delay_ms(1000);
 
        
        if((RX_buffer[0] == 'z') && (RX_buffer[1] == 'e') && (RX_buffer[2] == 'r') && (RX_buffer[3] == 'a') && (RX_buffer[4] == 'r')){
          cont = 0;
          UART_send("Zerado!\n");
        }
 
 
        // Limpa o buffer
        limpa_RX_buffer();
 
        // Delay de 1s
        _delay_ms(1000);
    }
}
