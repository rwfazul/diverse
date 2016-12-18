#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include "matriz.h"

Lista* lst_cria(void){
	return NULL;
}


Lista* lst_preenche(Esparsa e){
	srand( (unsigned)time(NULL) );

	Lista* p =  lst_cria();
	int i, j, valor;

	for(i = 0; i < e.linhas; i++){
		for(j = 0; j < e.colunas; j++){
			if(rand() % 4 == 2){ //so poem valor nao nulo se rand for 2 (matriz esparsa tem mais 0)
				valor = 1 + rand() % 9;
				p = lst_insere(i, j, p, valor);
			}

			/*scanf("%d", &valor); //para ler do usuario
			if(valor != 0){
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

void imprime_mat(Esparsa e){
	int i, j;
	Lista* p = e.prim;

	for(i = 0; i < e.linhas; i++){
		for(j = 0; j < e.colunas; j++){
			if(p != NULL && p->linha == i  && p->coluna == j){
				printf("%5d ", p->info);
				p = p->prox;
			}
			else
				printf("%5d ", 0); //tabulacao
		}
		printf("\n\t");
	}
}

void lst_imprime(Esparsa e){
	Lista* p;

	for(p = e.prim; p != NULL; p = p->prox)
		printf("%d ", p->info);

	printf("\n");
}

bool consulta_elemento(Esparsa e){
	int linha, coluna;
	printf("\nDigite os indices do elemento (linha e a coluna): ");
	scanf("%d %d", &linha, &coluna);

	if(linha < 0 || coluna < 0 || linha >= e.linhas || coluna >= e.colunas)
		return false;

	Lista* p = e.prim;
	while(p != NULL){
		if(p->linha == linha && p->coluna == coluna){
			printf("\tElemento buscado eh: %d (esta na lista)\n", p->info);
			return true;
		}
		p = p->prox;
	}

	printf("\tElemento buscado eh: 0 (nao esta na lista)\n");

	return true;
}

bool soma_linha(Esparsa e){
	int linha, soma = 0;
	printf("\nDigite a linha: ");
	scanf("%d", &linha);

	if(linha < 0 || linha >= e.linhas)
		return false;

	Lista* p = e.prim;
	while (p != NULL){
		if(p->linha == linha)
			soma += p->info;
		else if(p->linha > linha)
			break;
		p = p->prox;
	}

	printf("A soma da linha %d da matriz eh: %d.\n", linha, soma);

	return true;
}

float nao_nulos(Esparsa e){
	int n_nulos = 0;
	float percent;
	Lista* p = e.prim;

	while(p != NULL){
		n_nulos++;	
		p = p->prox;	
	}

	percent = (float) (100 * n_nulos) / (e.linhas * e.colunas);

	return percent;
}

void lst_desaloca(Lista* l){
	Lista* p = l;

	while(p != NULL){
		l = p->prox;
		free(p);
		p = l;
	}
}