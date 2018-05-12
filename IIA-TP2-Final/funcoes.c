#include <stdio.h>
#include "funcoes.h"
#include "utils.h"
#include <math.h>

#define RECOMBINACAOPROB 0.5
#define MUTACAOPROB 0.5


void gera_sol_inicial(int *sol, float moedas[], int n_moedas, float valor_atingir) {
	for(int i=0; i<n_moedas; i++)
		sol[i]= random_l_h(0, (int)ceil(valor_atingir)/moedas[i]);


}

void reparaSol(int sol[], float moedas[], int n_moedas, float valor_atingir) {
	//se a solucao for inferior ao valor a atingir
	for (int i = n_moedas - 1; somaSol(sol, moedas, n_moedas)<valor_atingir && i>0; i--)
		while (1)
			if (somaSol(sol, moedas, n_moedas) + moedas[i] <= valor_atingir)
				sol[i]++;
			else
				break;

	//se a solucao exceder o valor a atingir
	for (int i = n_moedas - 1; somaSol(sol, moedas, n_moedas)>valor_atingir && i>0; i--)
		while (sol[i]>0) 
			if (somaSol(sol, moedas, n_moedas) - moedas[i] + 0.0009 >= valor_atingir) 
				sol[i]--;
			else 
				break;

	// casos especiais
/*	if (ceilf(somaSol(sol, moedas, n_moedas)*100)/100 != valor_atingir)
		solOtima(sol, moedas, n_moedas, valor_atingir); */
		
	//ou atribuir um valor muito alto para penalizar
	if (ceilf(somaSol(sol, moedas, n_moedas) * 100) / 100 != valor_atingir)
		for(int i= 0; i<n_moedas; i++)
			sol[i]= 9999;
}

void geraPop(int **pop, float moedas[],  int n_moedas, float valor_atingir, int popdim) {
	for (int i = 0; i < popdim; i++) {
		pop[i] = malloc(sizeof(int)*n_moedas);
		if (pop[i] == NULL)
		{
			printf("Erro na alocacao de memoria");
			exit(1);
		}
		gera_sol_inicial(pop[i], moedas, n_moedas, valor_atingir);
		reparaSol(pop[i], moedas, n_moedas, valor_atingir);
	}
}

void torneio(int **pop, float moedas[], int n_moedas, float valor_atingir, int popdim, int **pais)
{
	int i, x1, x2;

	// Realiza popdim torneios
	for (i = 0; i<popdim;i++)
	{
		x1 = random_l_h(0, popdim - 1);
		do
			x2 = random_l_h(0, popdim - 1);
		while (x1 == x2);
		if (calcula_fit(pop[x1], n_moedas) < calcula_fit(pop[x2], n_moedas)){
			pais[i] = pop[x1];
			reparaSol(pais[i], moedas, n_moedas, valor_atingir);
		}
		else{
			pais[i] = pop[x2];
			reparaSol(pais[i], moedas, n_moedas, valor_atingir);
		}
	//	printf("recombinacao "); escreve_sol(pais[i], n_moedas); printf("custo: %d\n", calcula_fit(pais[i], n_moedas));
	}
}

void recombinacao_dois_pontos_corte(int **pop, float moedas[], int n_moedas, float valor_atingir, int popdim, int **pais){
	int i, j, point1, point2;

	for (i = 0; i<popdim; i += 2)
	{
		if (rand_01() < RECOMBINACAOPROB)
		{
			point1 = random_l_h(0, n_moedas - 2);
			point2 = random_l_h(point1 + 1, n_moedas - 1);
			for (j = 0; j<point1; j++)
			{
				pop[i][j] = pais[i][j];
				pop[i + 1][j] = pais[i + 1][j];
			}
			for (j = point1; j<point2; j++)
			{
				pop[i][j] = pais[i + 1][j];
				pop[i + 1][j] = pais[i][j];
			}
			for (j = point2; j<n_moedas; j++)
			{
				pop[i][j] = pais[i][j];
				pop[i + 1][j] = pais[i + 1][j];
			}
		}
		else
		{
			pop[i] = pais[i];
			pop[i + 1] = pais[i + 1];
		}
		reparaSol(pop[i], moedas, n_moedas, valor_atingir);
		//printf("recombinacao "); escreve_sol(pop[i], n_moedas); printf("custo: %d\n", calcula_fit(pop[i], n_moedas));
	}
}

void mutacao(int **pop, float moedas[], int n_moedas, float valor_atingir, int popdim) {	//mutacao por troca
	int i, pos1, pos2, aux;

	for (i = 0; i<popdim; i++)
		if (rand_01() < MUTACAOPROB)
		{
			pos1 = random_l_h(0, n_moedas - 1);
			pos2 = random_l_h(0, n_moedas - 1);
			aux = pop[i][pos1];
			pop[i][pos1] = pop[i][pos2];
			pop[i][pos2] = aux;
			reparaSol(pop[i], moedas, n_moedas, valor_atingir);
		//	printf("mutacao "); escreve_sol(pop[i], n_moedas); printf("custo: %d\n", calcula_fit(pop[i], n_moedas));
		}
}

void solOtima(int *sol, float moedas[], int n_moedas, float valor_atingir) {
	for (int i = 0; i<n_moedas; i++)
		sol[i] = 0;

	for (int i = n_moedas-1; somaSol(sol, moedas, n_moedas)<valor_atingir; i--) 
		while(1)
			if(somaSol(sol, moedas, n_moedas) + moedas[i] <= valor_atingir)
				sol[i]++;
			else
				break;
			
	return sol;
}

void getBest(int **pop, int popdim, int n_moedas, int *best, float moedas[], float valor_atingir){
	for (int i = 0; i<popdim; i++)
		if (calcula_fit(pop[i], n_moedas) < calcula_fit(best, n_moedas)){
			for(int j=0; j<n_moedas; j++)
				best[j] = pop[i][j];
		}
	
}

void iniciaBest(int *best, int n_moedas) {
	for(int i=0; i<n_moedas; i++)
		best[i]= 9999;
}

float somaSol(int *sol, float moedas[], int n_moedas) {
	float soma=0;
	for(int i=0; i<n_moedas; i++)
		soma+= (float)(sol[i])*moedas[i];
	return soma;
}

void mostra_sol_inicial(int *sol, int n_moedas) {
	int i;
	printf("\nSolucao inicial: ");
	for (i = 0; i<n_moedas; i++)
		printf("%d ", sol[i]);
}

int calcula_fit(int * sol, int n_moedas) {
	int i, total = 0;
	for (i = 0; i < n_moedas; i++)
		total += sol[i];
	//printf("-> Custo fit: %d", total);
	return total;
}

void gera_vizinho(int sol[], int nova_sol[], int n_moedas) { // mudar de forma a ficar mais parecido com o problema, sem ter tantos randoms
	int i, p1, p2;
	for (i = 0; i<n_moedas; i++)
		nova_sol[i] = sol[i];

	// ter em atenção os valores negativos!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	for (i = 0; i < n_moedas; i++) {
		if (rand_01() < 0.2) {
			nova_sol[i] += 1;
		}
		else {
			nova_sol[i] -= 1;
		}
	}
}

void mostra_vizinho(int *sol, int n_moedas) {
	int i;
	printf("\nSolucao vizinha: ");
	for (i = 0; i<n_moedas; i++)
		printf("%d ", sol[i]);
}

void escreve_sol(int *sol, int n_moedas) {
	int i;
	printf("\nSolucao: ");
	for (i = 0; i<n_moedas; i++)
		printf("%d ", sol[i]);
	//printf("\n");
}

void escreve_solotima(int *sol, int n_moedas) {
	int i;
	printf("\nSolucao Otima: ");
	for (i = 0; i<n_moedas; i++)
		printf("%d ", sol[i]);
	//printf("\n");
}

void substitui(int best[], int sol[], int n_moedas) {
	int i;
	for (i = 0; i<n_moedas; i++)
		best[i] = sol[i];
}