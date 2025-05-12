#define PINO 4

unsigned int Leitura_AD;
float tensao;

int main(){

	Serial.begin(115200);
	
	ADMUX = (0 << REFS1) + (1 << REFS0); //Utiliza 5V como referência (1023)
	
	ADCSRA = (1 << ADEN) + (1 << ADPS2) + (1 << ADPS1) + (1 << ADPS0); //Habilita ADC e PS 128 (10 bits)
	
	ADCSRB = 0; //Conversão Única
	
	DIDR0 = (1 << PINO); //Desabilita o PCx como pino digital - Não obrigatório
	
	for(;;){
	
		//Determinar o pino de leitura
		ADMUX = (ADMUX & 0xF8) | PINO;
		
		ADCSRA |= (1 << ADSC); //Inicia a conversão
		
		while((ADCSRA & (1<<ADSC)) == (1<<ADSC)); //Esperar a conversão
		
		Leitura_AD = ADC;
		
		tensao = (Leitura_AD * 5.0) / 1023.0; //Cálculo da Tensão
		
		Serial.print(tensao);
    Serial.println(" volts");
	}
	
}