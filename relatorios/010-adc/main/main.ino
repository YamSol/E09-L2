/* CODIGO PARTE 2
	Parte 1: A tensão de entrada é aplicada através de um potenciômetro, variando de 0V até 5V. No
programa é feito a conversão de binário para tensão. A dica aqui é trabalhar com a tensão em milivolts
com o objetivo de evitar operações em ponto flutuante.

	Parte 2: Realize a conexão de um LED no pino PD6, e configure o TIMER0 para operar em modo
fast_PWM, depois configure os bits e registradores necessários para que o LED possa ter seu brilho
variado de 0% à 100%, dependendo da tensão entre 0 e 5V obtida do potênciometro.
 */

// this should compile using arduino IDE

#define PINO_ADC  PC0
#define LED_SAIDA PD6

unsigned int valor_lido_adc;
int tensao_milivolts;

unsigned int ler_conversao();
void config_converter();
void config_led();
void config_timer();
void intern_enable_pwm();

int main(void) {
    Serial.begin(115200);
    config_converter();
    config_led();
    config_timer();

    for(;;) {

			valor_lido_adc = ler_conversao();

			tensao_milivolts = (valor_lido_adc * 5000.0) / 1023.0; // 5000 mV

			OCR0A = (valor_lido_adc *255) / 1023;

			/* Serial.print(tensao_milivolts/1000); */
			Serial.print(tensao_milivolts);
			Serial.println(" mV");
    }
		
}

void config_converter() {
	ADMUX |= (0<<REFS1) + (1<<REFS0); // Configurando Tensão de referencia interna de 5V (1023)
  
	/* ADMUX |= PINO_ADC; // Caso seja utilizado apenas um pino. */
  
	ADCSRA |= (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0) | (1<< ADEN); // ativando o pre-scaler /128 e ADC
  
	ADCSRB |= 0; // Modo de conversão unica (manual). Default.
	
	DIDR0 |= PINO_ADC; // (Opcional) Desabilita a utilização do pino como "entrada digital" caso haja uma entrada analógica.
}

unsigned int ler_conversao() {
	// determinar pino de leitura
	// OBS> Exemplo de leitura do valor analogico, caso utilize-se mais de um pino
	//    ADMUX = (ADMUX & 0xF8) | input;
	ADMUX = (ADMUX & 0xF8) | PINO_ADC;
	// iniciar_conversao
	ADCSRA |= (1<<ADSC);
	// esperar_conversa
	/* while (!(ADCSRA & (1<<ADIF))); */
	while((ADCSRA & (1<<ADSC)) == (1<<ADSC));
	
	return ADC;
}

void config_led() {
  DDRD |= (1<<LED_SAIDA);
  PORTD &= ~(1<<LED_SAIDA);
}

void config_timer() {
	/* enable pwm */
	TCCR0A |= (1<<COM0A1); // set OC0A at BOTTOM (non-inverting mode)
	TCCR0A |= (1<<WGM01) | (1<<WGM00); // enable mode Fast PWM
	TCCR0B |= (1<<CS02) | (1<<CS00); // enable a HIGH pre-scaler. OBS: always use HIGH value.
	
}

