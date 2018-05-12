#pragma once

void gera_sol_inicial(int *sol, float moedas[], int n_moedas, float valor_atingir);
void mostra_sol_inicial(int *sol, int v);
void reparaSol(int sol[], float moedas[], int n_moedas, float valor_atingir);
int calcula_fit(int *sol, int n_moedas);
void solOtima(int *sol, float moedas[], int n_moedas, float valor_atingir);
float somaSol(int *sol, float moedas[], int n_moedas);
void gera_vizinho(int sol[], int nova_sol[], int n_moedas);
void mostra_vizinho(int *sol, int n_moedas);
void geraPop(int **pop, float moedas[], int n_moedas, float valor_atingir, int popdim);
void torneio(int **pop, float moedas[], int n_moedas, float valor_atingir, int popdim, int **pais);
void escreve_sol(int *sol, int n_moedas);
void escreve_solotima(int *sol, int n_moedas);
void substitui(int best[], int sol[], int n_moedas);
void iniciaBest(int *best, int n_moedas);
void recombinacao_dois_pontos_corte(int **pop, float moedas[], int n_moedas, float valor_atingir, int popdim, int **pais);
void mutacao(int **pop, float moedas[], int n_moedas, float valor_atingir, int popdim);
void getBest(int **pop, int popdim, int n_moedas, int *best, float moedas[], float valor_atingir);