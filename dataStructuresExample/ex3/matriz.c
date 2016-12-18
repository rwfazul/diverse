#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "matriz.h"

Lista* lst_cria(void){
	return NULL;
}

Lista* lst_preenche(Identidade id){
	srand( (unsigned)time(NULL) );

	Lista* p =  lst_cria();
	int i, j, valor;

	for(i = 0; i < id.ordem; i++){
		for(j = 0; j < id.ordem; j++){
				valor = rand () % 2;
				if(valor != 0)
					p = lst_insere(i, j, p, valor);
				else if(i == j)
					p = lst_insere(i, j, p, valor);

			/*scanf("%d", &valor); //para ler do usuario
			if(valor != 0){
				p = lst_insere(i, j, p, valor);
			else if(i == j)
				p = lst_insere(i, j, p, valor);
			}*/ 
		}
	}

	return p;
}

Lista* lst_insere (int i, int j, Lista* p, int valor){ //i = linha e j = coluna
	Lista* u = lst_busca_ultimo(p);

	Lista* novo = (Lista*) malloc(sizeof(Lista));

	novo->info = valor;
	novo->linha = i;
	novo->coluna = j;

	if(u == NULL) //lista vazia
		return novo;

	u->prox = novo;

	return p;
}

Lista* lst_busca_ultimo(Lista* p){
	Lista* u = p;
	Lista* ant = NULL;

	while(u != NULL){
		ant = u;
		u = u->prox;
	}

	return ant;
}

void imprime_mat(Identidade id){
	int i, j;
	Lista* p = id.prim;

	for(i = 0; i < id.ordem; i++){
		for(j = 0; j < id.ordem; j++){
			if(p != NULL && p->linha == i && p->coluna == j){
				printf("%5d ", p->info);
				p = p->prox;
			}
			else
				printf("%5d ", 0); //tabulacao
		}
		printf("\n\t");
	}
}

bool verifica_matriz(Identidade id){
	Lista* p = id.prim;

	while(p != NULL){
		if(p->linha != p->coluna)
			return false;
		else
			if(p->info != 1)
				return false;
		p = p->prox;
	}

	return true;
}

void aponta_erros(Identidade id){
	Lista* p = id.prim;

	printf("\nLinha Coluna   Elemento\n");

	while(p != NULL){
		if(p->linha != p->coluna)
			printf("  %d     %d\t  %d\t   Deveria ser 0\n", p->linha, p->coluna, p->info);
		else
			if(p->info != 1)
				printf("  %d     %d\t  %d\t   Deveria ser 1\n", p->linha, p->coluna, p->info);
		p = p->prox;
	}

	printf("\n");
}

void lst_desaloca(Lista* l){
	Lista* p = l;

	while(p != NULL){
		l = p->prox;
		free(p);
		p = l;
	}
}


