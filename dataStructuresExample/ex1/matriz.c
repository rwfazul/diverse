#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "matriz.h"

Diagonal* aloca_vetor(int tam){
	Diagonal* m = (Diagonal*) malloc(sizeof(Diagonal));

	m->ordem = tam;
	m->v = (int*) malloc(m->ordem*sizeof(int)); //aloca vetor da struct Diagonal

	return m;
}


void preenche_vetor(Diagonal* m){
	srand( (unsigned)time(NULL) );

	int i, j;

	for(i = 0; i < m->ordem; i++){
		for(j = 0; j < m->ordem; j++){
			//scanf("%d", &m.v[i]); //para ler do usuario
			if(i == j){
				m->v[i] =  1 + rand() % 9;
			}
		}
	}

}

void imprime_matriz(Diagonal* m){
	int i, j;
	printf("Matriz de ordem %d\n\t", m->ordem);
	
	for(i = 0; i < m->ordem; i++){
		for(j = 0; j < m->ordem; j++){
			if(j != i)
				printf("%5d", 0); // para ficar tabulado
			else
				printf("%5d", m->v[i]);
		}
		printf("\n\t");
	}

	printf("\n");

}


bool busca_elemento(int l, int c, Diagonal* m){
	if(l >= m->ordem || c >= m->ordem || c < 0 || l < 0) //indices invalidos
		return false;

	//busca no vetor
	if(l == c) //diagonal p. indices iguais
		printf("\tValor: %d (Posicao no vetor: %d)\n\n", m->v[l], l);
	else
		printf("\tValor: 0  (Nao esta no vetor)\n\n");

	return true;
}
