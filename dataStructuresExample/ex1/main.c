#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "matriz.h"

int main(int argc, char **argv){
	int tam, l, c;
	bool novamente = true;
	char op;

	printf("Digite a ordem da matriz: ");
	scanf("%d", &tam);

	Diagonal* m = aloca_vetor(tam); 
	preenche_vetor(m); //preenche com a diagonal principal da matriz

	printf("Matriz: ");
	imprime_matriz(m); //imprime matriz pelo vetor

	do{
		printf("Digite os indices (linha e coluna) para a busca: ");
		scanf("%d %d", &l, &c);

		if(!busca_elemento(l, c, m))
			printf("\tLinha ou coluna invalida.\n\n");

		printf("Deseja buscar outro elemento (s ou n)? ");
		scanf(" %c", &op);

		if(op == 'n' || op == 'N'){
			printf("\nFim.\n");
			novamente = false;
		}
	}while(novamente);

	free(m->v); //desaloca vetor
	free(m);
		
	return 0;
}
