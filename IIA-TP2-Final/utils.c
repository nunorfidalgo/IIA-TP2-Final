#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "funcoes.h"
#include "utils.h"

// Inicializa o gerador de numeros aleatorios
void init_rand() {
	srand((unsigned)time(NULL));
}

// Devolve valor inteiro aleatorio entre min e max
int random_l_h(int min, int max) {
	return min + rand() % (max - min + 1);
}

// Devolve um valor real aleatorio do intervalo [0, 1]
float rand_01() {
	return ((float)rand()) / RAND_MAX;
}

float* ler_ficheiro(char *nomeficheiro, int *n_moedas, float *valor_atingir) {
	FILE *file;
	float *moedas;
	int i;
	file = fopen(nomeficheiro, "r");
	if (!file)
	{
		printf("Erro no acesso ao ficheiro dos dados\n");
		exit(1);
	}
	fscanf(file, " %d", n_moedas);
	fscanf(file, " %f", valor_atingir);
	moedas = malloc(sizeof(float)*(*n_moedas));
	if (!moedas)
	{
		printf("Erro na alocacao de memoria\n");
		exit(1);
	}
	for (i = 0; i < *n_moedas; i++)
		fscanf(file, " %f", &moedas[i]);
	fclose(file);
	return moedas;
}

void mostra_ficheiro(float *moedas, int *n_moedas, float *valor_atingir) {
	int i;
	printf("\n\n\n\n\nDados ficheiro:");
	printf("\n - Numero de moedas: %d", *n_moedas);
	printf("\n - Valor a atingir: %.2f", *valor_atingir);
	printf("\n - Moedas: ");
	for (i = 0; i<*n_moedas; i++) {
		printf("%.2f ", moedas[i]);
	}
	//printf("\n");
}

int menu(char* nomeficheiro) {
	int op;
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
	do {
		printf("Menu:\nEscolha o conjunto de moedas para testar: ");
		printf("\n1 - moedas1.txt");
		printf("\n2 - moedas2.txt");
		printf("\n3 - moedas3.txt");
		printf("\n4 - moedas4.txt");
		printf("\n5 - moedas5.txt");
		printf("\n6 - moedas_defesa.txt");
		printf("\n9 - moedas_teste.txt");
		printf("\n0 - Voltar");
		printf("\nop: ");
		scanf("%d", &op);
	} while (op < 0 || op > 9);
	switch (op) {
	case 1:
		strcpy(nomeficheiro, "moedas1.txt");
		return 1;
	case 2:
		strcpy(nomeficheiro, "moedas2.txt");
		return 1;
	case 3:
		strcpy(nomeficheiro, "moedas3.txt");
		return 1;
	case 4:
		strcpy(nomeficheiro, "moedas4.txt");
		return 1;
	case 5:
		strcpy(nomeficheiro, "moedas5.txt");
		return 1;
	case 6:
		strcpy(nomeficheiro, "moedas_defesa.txt");
		return 1;
	case 9:
		strcpy(nomeficheiro, "moedas_teste.txt");
		return 1;
	case 0:
		return 0;
	}
}
