#include <unistd.h>
#include <stdio.h>


#define VERDE    0
#define AMARELO  1
#define VERMELHO 2

#define T_VERDE    12
#define T_AMARELO  3
#define T_VERMELHO 15

unsigned int estado_atual = VERDE, cor = 0, timer = 0; 


int main(void) {
    for(;;) {
	switch(estado_atual) {
	case VERDE:
	    printf("VERDE\n");
	    cor = 0;
	    // _delay_ms(T_VERDE);
	    sleep(T_VERDE);
	    estado_atual = AMARELO;
	    break;

	    case AMARELO:
	    printf("AMARELO\n");
	    cor = 1;
	    // _delay_ms(T_AMARELO);
	    sleep(T_AMARELO);
	    estado_atual = VERMELHO;
	    break;
	
	case VERMELHO:
	    printf("VERMELHO\n");
	    cor = 2;
	    // _delay_ms(T_VERMELHO);
	    sleep(T_VERMELHO);
	    estado_atual = VERDE;
	    break;

	default:
	    break;
	}
    }
    return 0;
}
