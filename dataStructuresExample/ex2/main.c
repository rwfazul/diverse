#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "matriz.h"


int main(int argc, char **argv){
	Esparsa e;
	Lista* l = lst_cria();

	printf("Digite o numero de linhas e de colunas da matriz: ");
	scanf("%d %d", &e.linhas, &e.colunas);

	//printf("Digite os valores da matriz: ");
	l = lst_preenche(e); //preenche com os elementos nao nulos da matriz
	e.prim = l;
	
	int op;
	float percent;
	do{
		printf("\nMatriz:\n\t"); 
		imprime_mat(e); //imprime matriz inteira (tabulada) pela lista
		printf("Lista: ");
		lst_imprime(e); //imprime apenas elementos da lista (nao nulos)

		printf("\n\t1 - Consultar elemento\n\t2 - Imprimir somatorio linha\n\t3 - Percentual nao nulos\n\t4 - Sair\n\t");
		printf("Digite a operacao: ");
		scanf("%d", &op);

		switch(op){
			case 1: if(!consulta_elemento(e))
						printf("\tLinha ou coluna invalida.\n");
					break;
			case 2:	if(!soma_linha(e))
						printf("\tLinha invalida.\n");
					break;
			case 3: percent = nao_nulos(e);
					printf("\nPercentual de elementos nao nulos da matriz: %.2f%%\n", percent);
					break;
			case 4: printf("Fim.\n");
				break;
			default: printf("Opcao invalida.\n");
		}
		
	}while(op != 4);

	lst_desaloca(l);

	return 0;
}	
