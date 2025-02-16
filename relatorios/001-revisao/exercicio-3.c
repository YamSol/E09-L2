#include <stdio.h> // printf, scanf
#include <string.h> // memset

/*
Faça um código que recebe um valor n, referente a quantidade de 
testes que serão feitos. Logo em seguida, monte uma função que recebe 5 valores 
inteiros e mostra quantos valores digitados foram pares, quantos valores 
digitados foram ímpares, quantos valores digitados foram positivos e quantos 
valores digitados foram negativos e mostre na tela
*/

typedef enum {
    ODD = 0,
    EVEN,
    POSITIVE,
    NEGATIVE,
    SENTINEL_VALUE
} COUNTS_TYPE;

void func_test(int n) {
    const int VALS_SIZE = 5;
    const int COUNTS_SIZE = 4;
    int vals[VALS_SIZE];
    int counts[COUNTS_SIZE];

    memset(vals, 0, VALS_SIZE * sizeof(int));
    memset(counts, 0, COUNTS_SIZE * sizeof(int));
    
    // read 5 values
    for (int i = 0; i < VALS_SIZE; i++) {
	scanf("%d", &vals[i]);
    }

    // update countes
    for (int i = 0; i < VALS_SIZE; i++) {
	// even-odd
	if (vals[i] % 2 == 0) {
	    ++counts[EVEN];
	} else {
	    ++counts[ODD];
	}

	// positive-negative
	if (vals[i] > 0) {
	    ++counts[POSITIVE];
	} else if(vals[i] < 0) {
	    ++counts[NEGATIVE];
	}
    }

    // display results
    printf("<---------TEST (%d) -------->\n", n);
    printf("\tPARES:\t\t%d\n",	 counts[EVEN]);
    printf("\tIMPARES:\t%d\n",	 counts[ODD]);
    printf("\tPOSITIVOS:\t%d\n", counts[POSITIVE]);
    printf("\tNEGATIVOS:\t%d\n", counts[NEGATIVE]);
    printf("<-------------------------->\n");
}

int main (void) {
    int num_testes;
    printf("Digite o número de testes: ");
    scanf("%d", &num_testes);

    // run tests
    for (int i = 0; i < num_testes; i++) {
	func_test(i);
    }
    
    return 0;
}
