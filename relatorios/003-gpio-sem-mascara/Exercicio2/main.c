#define E0 0
#define E1 1
#define E2 2
#define E3 3


unsigned int estado_atual = E0;

int main() {

  DDRD  = 0b00000011;
  PORTD = 0b00000000;
  
  for(;;) {
    PORTD = estado_atual;
    
    switch(estado_atual) {
    case E0:
      _delay_ms(500);
      estado_atual = E1;
      break;
      
    case E1:
      _delay_ms(500);
      estado_atual = E2;
      break;
      
    case E2:
      _delay_ms(500);
      estado_atual = E3;
      break;
      
    case E3:
      _delay_ms(500);
      estado_atual = E0;
      break;
      
    default:
      estado_atual = E0;
    }

  }
}
