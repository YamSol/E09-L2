//botoes ON e OFF em pull-up
#define BTN_ON  0b00000001
#define BTN_OFF 0b00000010

//chaves S1,S2,S3 em pull-down
#define S1 		0b00000100
#define S2 		0b00001000
#define S3 		0b00010000

//saidas
#define M1 			0b00000010
#define LED_ON 		0b00000100
#define LED_OFF 	0b00001000
#define LED_ALARME 	0b00010000

//chaves CH1 e CH2 em pull-down
#define CH1 		0b00100000
#define CH2 		0b01000000

int ON = 0;
int chave;

int main(void){
  
  DDRB = 0b00000000; //todos os pinos como entrada
  PORTB &= ~(S1 | S2 | S3); //ativando pull-down
  
  DDRD = M1 | LED_ON | LED_OFF | LED_ALARME;  //0b00011110
  PORTD &= ~(CH1 | CH2); 	//ativando pull-down

  ON = 0;
  chave = 'P';
  
  for(;;){

    //botao ON pressionado
    if((PINB & BTN_ON) == 0){
    	ON = 1;
      	PORTD &= ~LED_ALARME;
    }
  
    //botao OFF pressionado
    if((PINB & BTN_OFF) == 0)
    	ON = 0;

    //desligando sitema
    if (!ON){
      PORTD &= ~(M1) & ~(LED_ON);
      PORTD |= LED_OFF;
      continue;
    }
    
    //segue o codigo caso botao ON
    PORTD |= LED_ON | M1;
    PORTD &= ~LED_OFF;
    
    //verificando chaves
    if (!(PIND & CH1) && (PIND & CH2))
        chave = 'M';
    else if ((PIND & CH1) && !(PIND & CH2))
        chave = 'G';
    else if (!(PIND & CH1) && !(PIND & CH2))
        chave = 'P';

    //verificando caixas
    if (chave == 'P' && ((PINB & S2) || (PINB & S1))) {
        PORTD |= LED_ALARME;
        PORTD &= ~M1;
        ON = 0;
    }

    if (chave == 'M' && ((PINB & S1) || !(PINB & S3))) {
        PORTD |= LED_ALARME;
        PORTD &= ~M1;
        ON = 0;
    }

    if (chave == 'G' && (!(PINB & S1) || !(PINB & S2) || !(PINB & S3)) ) {
        PORTD |= LED_ALARME;
        PORTD &= ~M1;
        ON = 0;
    }

  }
}
