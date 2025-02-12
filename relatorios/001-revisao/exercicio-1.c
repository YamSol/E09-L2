#include <stdio.h>

/*
Questão 1) Em uma banca de frutas o preço das laranjas pode assumir 2 valores 
distintos, R$0,80 cada se forem adquiridas menos de uma dúzia, e R$0,65 se forem 
adquiridas pelo menos doze. Utilizando a estrutura de decisão if-else, elabore
um programa que leia o número de laranjas compradas e imprima o valor total da 
compra.
*/

int main (void) {
    int num_laranjas;
    float preco = 0.0f;

//    printf("Digite o número total de laranjas: ");
    scanf("%d", &num_laranjas);

    if (num_laranjas < 12) {
	preco = 0.8f;
    } else {
	preco = 0.65f;
    }

    float preco_final = preco*num_laranjas;

    printf("Preco da unidade: R$%.2f\n", preco);
    printf("Preco total: R$%.2f\n", preco_final);

    return 0;
}
