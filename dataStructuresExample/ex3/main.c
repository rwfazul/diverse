#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "matriz.h"

int main(int argc, char **argv){
	Lista* l = lst_cria();
	Identidade id;

	printf("Digite a ordem da matriz: ");
	scanf("%d", &id.ordem);

	l = lst_preenche(id);
	id.prim = l;

	printf("Matriz:\n\t");
	imprime_mat(id);

	if(verifica_matriz(id))
		printf("Eh uma Matriz indentidade.\n\n");
	else{
		printf("Nao eh uma Matriz indentidade:\n");
		aponta_erros(id);
	}

	lst_desaloca(l);

	return 0;
}

