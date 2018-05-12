// IIA-TP2-Final.cpp : Defines the entry point for the console application.
//

#include <stdio.h>
#include <stdlib.h>
#include "algoritmos.h"
#include "funcoes.h"
#include "utils.h"

/* 
# Adicionar as seguintes opções em propriedades do projecto -> Configuration Properties->C/C++-> Preprocessor-> Preprocessor Definitions -> <Edit>
_CONSOLE
_CRT_SECURE_NO_WARNINGS

# Se der erro no accesso aos ficheiros copiar para a directoria do .exe

*/

void main(void) {
	int op;
	init_rand();
	while(1){
		printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
		do {
			printf("Menu:\nEscolha o o algoritmo a usar: ");
			printf("\n1 - Trepa colinas");
			printf("\n2 - Genetico");
			printf("\n3 - Misto");
			printf("\n0 - Sair");
			printf("\nop: ");
			scanf("%d", &op);
		}while(op < 0 || op > 3);
		switch(op){
			case 1: trepaCollinas(); break;
			case 2: genetico(); break;
			case 3: misto(); break;
			case 0: exit(1);
		}
	}
}
