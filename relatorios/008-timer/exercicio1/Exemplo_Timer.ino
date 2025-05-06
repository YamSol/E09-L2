#define led (1<<PD0)

//Variável de contagem global
unsigned int cont = 0;

int main(){

  //Configura PD0 como saída
  DDRD = led;

  //Inicializa o PD0 como desligado
  PORTD &= ~(led);

  //Configuração de Timer -------------------------------------------------------------------

  //Mode de operação CTC (Comparação)
  TCCR0A = (1<<WGM01);

  //Escolha do Pré - Scaler 8 -> 2MHz -> 500ns
  TCCR0B = (1<<CS01);

  //Habilitação da interrupção
  TIMSK0 = (1<<OCIE0A);

  //Definição do comparador
  OCR0A = 199; //100us //150ms -> cont == 1500

  //Habilitar as interrupções globais
  sei();

  while(1){
    //Vazio
  }

}

ISR(TIMER0_COMPA_vect){

  cont++;
  if(cont >= 5000){ //500ms
    PORTD ^= led;
    cont = 0;
  }

}

