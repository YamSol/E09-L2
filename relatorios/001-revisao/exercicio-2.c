#include <stdio.h>

int main (void) {
    int value = -1;
    int remainder;

    // read int value [0-50]
    while(1) {
	printf("Digite um valor no intervalo de [0-50]: ");
	scanf("%d", &value);
	if (value >= 0 && value <= 50) {
	    break;
	}
    }

    for (int i = value-1; i > 0; i--) {
	remainder = value % i;
	printf("Resto da divisao de %d por %d: %d\n", value, i, remainder);
    }
    
    
    return 0;
}
