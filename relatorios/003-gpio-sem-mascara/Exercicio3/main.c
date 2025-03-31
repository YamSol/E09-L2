/* Mudancas de estado
  01 -> 10 -> 00 -> 01 -> ..
*/

#define E0 0b00000001
#define E1 0b00000010
#define E2 0b00000000

unsigned int estado_atual = E0, botao = 0;

int main() {

  DDRD  = 0b00000011;
  PORTD = E0;
 
  for(;;) {
    PORTD = estado_atual;

    botao = (PIND & 0b00000100);
    if (botao) {
      
      switch(estado_atual) {
      case E0:
	estado_atual = E1;
	break;
      case E1:
	estado_atual = E2;
	break;
      case E2:
	estado_atual = E0;
	break;
	
      default:
	estado_atual = E0;
      }

      _delay_ms(500);
    }
    
  }
}

