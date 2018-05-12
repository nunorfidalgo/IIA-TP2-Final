#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "algoritmos.h"
#include "funcoes.h"
#include "utils.h"

#define DEFAULT_RUNS 25 
#define ITERATIONS 50 
#define POPINICIAL 10

int trepa_colinas(int sol[], float *moedas, int n_moedas, int num_iter, float valor_atingir)
{
	int i, *nova_sol, custo, custo_viz;
	nova_sol = malloc(sizeof(int)*n_moedas);
	/*for (i = 0; i > n_moedas; i++) {
	nova_sol[i] = 0;*/
	if (nova_sol == NULL)
	{
		printf("Erro na alocacao de memoria");
		exit(1);
	}
	custo = calcula_fit(sol, n_moedas);
	for (i = 0; i<num_iter; i++)
	{
	//	gera_vizinho(sol, nova_sol, n_moedas);
		gera_sol_inicial(nova_sol, moedas, n_moedas, valor_atingir); //neste problema funciona de gera vizinho
		reparaSol(nova_sol, moedas, n_moedas, valor_atingir); 
		custo_viz = calcula_fit(nova_sol, n_moedas);
		if (custo_viz < custo) // mudar em < e <=
		{
			custo = custo_viz;
			substitui(sol, nova_sol, n_moedas);
		}
	}
	free(nova_sol);
	return custo;
}

void trepaCollinas() {
	char nomeficheiro[30];
	int n_moedas, k, best_ite, custo = 0, best_custo = 9999, *sol, *best, *otima, mbf = 0;
	float *moedas, valor_atingir;
	
	while (1) {
		best_ite = 0;
		best_custo = 9999;
		if(!menu(nomeficheiro))
			return;
		// Preenche vector de moedas
		moedas = ler_ficheiro(nomeficheiro, &n_moedas, &valor_atingir);
		mostra_ficheiro(moedas, &n_moedas, &valor_atingir);
		sol = malloc(sizeof(int)*n_moedas);
		best = malloc(sizeof(int)*n_moedas);
		otima = malloc(sizeof(int)*n_moedas);
		if (sol == NULL || best == NULL || otima == NULL)
		{
			printf("Erro na alocacao de memoria");
			exit(1);
		}
		mbf = 0;
		for (k = 0; k < DEFAULT_RUNS; k++)
		{
			//printf("\nRepeticao %d: ", k);
			// Gerar solucao inicial
			gera_sol_inicial(sol, moedas, n_moedas, valor_atingir);
			//	mostra_sol_inicial(sol, n_moedas);
			//	printf("  total= %f\n", somaSol(sol, moedas, n_moedas));
			reparaSol(sol, moedas, n_moedas, valor_atingir);
			// Trepa colinas
			custo = trepa_colinas(sol, moedas, n_moedas, ITERATIONS, valor_atingir);
			//	escreve_sol(sol, n_moedas); printf("custo: %d\n", custo); getchar();
			//printf("\nCusto final: %d", custo);
			mbf += custo;
			if (custo < best_custo) // perguntar ao prof se aqui também tem que se > e ou >=???????????????????????
			{
				best_ite = k;
				best_custo = custo;
				substitui(best, sol, n_moedas);
			}
			//printf("\n");
		}
		// Escreve eresultados globais
		printf("\n");
		printf("\nMBF: %.2f\n", (float)mbf / k);
		printf("\nMelhor solucao encontrada foi na repeticao: %d\n", best_ite);
		escreve_sol(best, n_moedas);
		printf("\t\tCusto: %d\n", best_custo);
		solOtima(otima, moedas, n_moedas, valor_atingir);
		escreve_solotima(otima, n_moedas);
		printf("\t\tCusto: %d\n", calcula_fit(otima, n_moedas));
		printf("\n\n<<Prima enter para continuar>>");
		getchar();getchar();
		free(sol);
		free(otima);
		free(best);
		printf("\n");
	}
}

void genetico() {
	char nomeficheiro[30];
	int n_moedas, k, best_ite, custo = 0, *sol, *best, *otima, mbf = 0, *pop[POPINICIAL], *pais[POPINICIAL];
	float *moedas, valor_atingir;
	init_rand();
	while (1) {
		best_ite = 0;
		if (!menu(nomeficheiro))
			return;
		// Preenche vector de moedas
		moedas = ler_ficheiro(nomeficheiro, &n_moedas, &valor_atingir);
		mostra_ficheiro(moedas, &n_moedas, &valor_atingir);
		best = malloc(sizeof(int)*n_moedas);
		otima = malloc(sizeof(int)*n_moedas);
		if (best == NULL || otima == NULL)
		{
			printf("Erro na alocacao de memoria");
			exit(1);
		}
		mbf = 0;
		iniciaBest(best, n_moedas);
		for (k = 0; k < DEFAULT_RUNS; k++){
			// Gerar populacao inicial
			//geraPop(pop, moedas, n_moedas, valor_atingir, POPINICIAL);
			for (int i = 0; i < POPINICIAL; i++) {
				pop[i] = malloc(sizeof(int)*n_moedas);
				if (pop[i] == NULL)
				{
					printf("Erro na alocacao de memoria");
					exit(1);
				}
				gera_sol_inicial(pop[i], moedas, n_moedas, valor_atingir);
				reparaSol(pop[i], moedas, n_moedas, valor_atingir);
			}

			getBest(pop, POPINICIAL, n_moedas, best, moedas, valor_atingir);
			
			for(int j=0; j<ITERATIONS; j++){
				//Selecao
				torneio(pop, moedas, n_moedas, valor_atingir, POPINICIAL, pais); 
				// Aplica os operadores genéticos aos pais (os descendentes ficam armazenados na estrutura pop)
				recombinacao_dois_pontos_corte(pop, moedas, n_moedas, valor_atingir, POPINICIAL, pais); 
				mutacao(pop, moedas, n_moedas, valor_atingir, POPINICIAL); 
				// Actualiza a melhor solução encontrada
				getBest(pop, POPINICIAL, n_moedas, best, moedas, valor_atingir);
				reparaSol(best, moedas, n_moedas, valor_atingir);
			}
			custo= calcula_fit(best, n_moedas); 
			mbf += custo;
			printf("\n%d", k); 
		}
		// Escreve eresultados globais
		printf("\n\n");
		printf("\nMBF: %.2f\n", (float)mbf / k);
		escreve_sol(best, n_moedas);
		printf("\t\tCusto: %d\n", calcula_fit(best, n_moedas));
		solOtima(otima, moedas, n_moedas, valor_atingir);
		escreve_solotima(otima, n_moedas);
		printf("\t\tCusto: %d\n", calcula_fit(otima, n_moedas));
		printf("\n\n<<Prima enter para continuar>>");
		getchar();getchar();
		free(otima);
		free(best);
		printf("\n");
	}
}

void misto() {
	char nomeficheiro[30];
	int n_moedas, k, best_ite, custo = 0, *sol, *best, *otima, mbf = 0, *pop[POPINICIAL], *pais[POPINICIAL];
	float *moedas, valor_atingir;
	init_rand();
	while (1) {
		best_ite = 0;
		if (!menu(nomeficheiro))
			return;
		// Preenche vector de moedas
		moedas = ler_ficheiro(nomeficheiro, &n_moedas, &valor_atingir);
		mostra_ficheiro(moedas, &n_moedas, &valor_atingir);
		best = malloc(sizeof(int)*n_moedas);
		otima = malloc(sizeof(int)*n_moedas);
		if (best == NULL || otima == NULL)
		{
			printf("Erro na alocacao de memoria");
			exit(1);
		}
		mbf = 0;
		iniciaBest(best, n_moedas);
		for (k = 0; k < DEFAULT_RUNS; k++) {
			// Gerar populacao inicial
			//geraPop(pop, moedas, n_moedas, valor_atingir, POPINICIAL);
			for (int i = 0; i < POPINICIAL; i++) {
				pop[i] = malloc(sizeof(int)*n_moedas);
				if (pop[i] == NULL)
				{
					printf("Erro na alocacao de memoria");
					exit(1);
				}
				gera_sol_inicial(pop[i], moedas, n_moedas, valor_atingir);
				reparaSol(pop[i], moedas, n_moedas, valor_atingir);
			}

			getBest(pop, POPINICIAL, n_moedas, best, moedas, valor_atingir);

			for (int j = 0; j<ITERATIONS; j++) {
				//Selecao
				torneio(pop, moedas, n_moedas, valor_atingir, POPINICIAL, pais);
				// Aplica os operadores genéticos aos pais (os descendentes ficam armazenados na estrutura pop)
				recombinacao_dois_pontos_corte(pop, moedas, n_moedas, valor_atingir, POPINICIAL, pais);
				mutacao(pop, moedas, n_moedas, valor_atingir, POPINICIAL);
				// Actualiza a melhor solução encontrada
				getBest(pop, POPINICIAL, n_moedas, best, moedas, valor_atingir);
				reparaSol(best, moedas, n_moedas, valor_atingir);
			}
			custo = calcula_fit(best, n_moedas);
			mbf += custo;
			printf("\n%d", k);
		}
		//o genetico foi usado para criar a solucao inicial do trepa colinas
		custo = trepa_colinas(best, moedas, n_moedas, ITERATIONS, valor_atingir);
		// Escreve eresultados globais
		printf("\n\n");
		printf("\nMBF: %.2f\n", (float)mbf / k);
		escreve_sol(best, n_moedas);
		printf("\t\tCusto: %d\n", calcula_fit(best, n_moedas));
		solOtima(otima, moedas, n_moedas, valor_atingir);
		escreve_solotima(otima, n_moedas);
		printf("\t\tCusto: %d\n", calcula_fit(otima, n_moedas));
		printf("\n\n<<Prima enter para continuar>>");
		getchar();getchar();
		free(otima);
		free(best);
		printf("\n");
	}
}