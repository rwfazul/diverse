#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "heap.h"

Heap* heap_cria(int max) {
	Heap* h = (Heap*) malloc(sizeof(Heap));
	h->tam = max;
	h->pos = 0;
	h->prioridades = (int*) malloc(max * sizeof(int));

	return h;
} 

bool heap_insere(Heap* h, int prioridade, int tipo) {
	if (h->pos < h->tam) { // tem lugar no vetor
		h->prioridades[h->pos] = prioridade;

		corrige_acima(h, h->pos, tipo);

		h->pos++;
	} 
	else 
		return false;

	return true;

}

int heap_remove(Heap* h, int tipo) {
	if (h->pos < 1) // nao tem elementos
		return -1;

	int topo = h->prioridades[0];
 	h->prioridades[0] = h->prioridades[h->pos-1];
 	h->pos--;

 	corrige_abaixo(h, tipo);

	return topo;
}

void corrige_acima(Heap* h, int pos, int tipo) { 
	while (pos > 0) {
		int raiz = RAIZ(pos);

		if (tipo == MIN_HEAP) { 
			if (h->prioridades[pos] < h->prioridades[raiz])
				troca(h->prioridades, pos, raiz);
			else
				break;
		}
		else if (tipo == MAX_HEAP) { 
			if (h->prioridades[pos] > h->prioridades[raiz])
				troca(h->prioridades, pos, raiz);
			else
				break;
		}

		pos = raiz;
	}
}

void corrige_abaixo(Heap* h, int tipo) {
	int raiz = 0;

	while (FILHO_ESQ(raiz) < h->pos) {
		int filho_esq = FILHO_ESQ(raiz);
		int filho_dir = FILHO_DIR(raiz);	
		int filho;

		if (filho_dir >= h->pos)
			filho_dir = filho_esq;

		if (tipo == MIN_HEAP) { 
			if (h->prioridades[filho_esq] < h->prioridades[filho_dir])
				filho = filho_esq;
			else
				filho = filho_dir;

			if (h->prioridades[raiz] > h->prioridades[filho])
				troca(h->prioridades, raiz, filho);
			else
				break;
		}
		else if (tipo == MAX_HEAP) {  
			if (h->prioridades[filho_esq] > h->prioridades[filho_dir])
				filho = filho_esq;
			else
				filho = filho_dir;

			if (h->prioridades[raiz] < h->prioridades[filho])
				troca(h->prioridades, raiz, filho);
			else
				break;
		}

		raiz = filho;
	}
}

void troca(int* v, int x, int y) {
	int aux = v[x];
	v[x] = v[y];
	v[y] = aux;
}

bool heap_busca(Heap* h, int busca) {
	int i;

	for (i = 0; i < h->pos; i++) 
		if (h->prioridades[i] == busca)
			return true;

	return false;
}

int posicao(Heap* h, int valor){
	int i;

	for (i = 0; i < h->pos; i++)
		if (h->prioridades[i] == valor)
			return i;

	return -1;
}

void heap_imprime(Heap* h) {
	if (vazio(h)) {
		printf("Heap vazio.\n");
		return;
	}

	printf("Vetor de prioridades:\n");

	int i, filho;
	for (i = 0; i < h->pos; i++) {
		printf("Raiz: %d\t", h->prioridades[i]);

		filho = FILHO_ESQ(i);
		if (filho < h->pos)
			printf("  FilhoEsq: %d\t", h->prioridades[filho]);

		filho = FILHO_DIR(i);
		if (filho < h->pos)
			printf("  FilhoDir: %d", h->prioridades[filho]);

		printf("\n");
	}

	printf("\n");
}

bool vazio(Heap *h) {
	return (!h->pos);
}

void heap_libera(Heap* h) {
	free (h->prioridades);
	free (h);
}
