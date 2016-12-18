#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "heap.h"

int menu(void);

int main(int argc, char **argv) {
	int tam, op, tipo, valor; 
	bool ok;
	novo:

	printf("Digite o tamanho da heap: ");
	scanf("%d", &tam);

	Heap* heap = heap_cria(tam);

	if (heap != NULL)
		printf("Heap de %d elementos criada com sucesso.\n\n", tam);
	else
		exit(1);

	do {
		printf("\t1 - Min Heap\n\t2 - Max heap\n\tEscolha: ");
		scanf("%d", &tipo);

		if (tipo != 1  && tipo != 2) {
			printf("\nOpcao invalida. Escolha novamente.\n\n");
			ok = false;
		}
		else
			ok = true;

	}while (!ok);

	printf("\n");

	do {
		op = menu();
		switch (op) {
			case 1:	printf("Prioridade a ser inserida: ");
					scanf("%d", &valor);

					if (!heap_insere(heap, valor, tipo))
						printf("Insercao impossivel. Heap cheio.\n");
				break;
			case 2: valor = heap_remove(heap, tipo);

					if (valor == -1)
						printf("Remocao impossivel. Heap vazio.\n");
					else
						printf("O elemento %d foi removido.\n", valor);
				break;
			case 3: printf("Digite o elemento para consulta: ");
					scanf("%d", &valor);

					if (heap_busca(heap, valor))
						printf("Elemento %d encontrado na posicao %d do vetor de prioridades.\n", valor, posicao(heap, valor));
					else
						printf("Elemento nao encontrado.\n");
				break;
			case 4: heap_imprime(heap);
				break;
			case 5: heap_libera(heap);
					goto novo;
				break;
			case 6: printf("Fim.\n");
				break;
			default: printf("Opcao invalida. Escolha novamente.\n");
		}
		printf("\n");

	}while (op != 6);

	heap_libera(heap);

	return 0;
}

int menu(void) {
	int op;
	printf("\t------------\n");
	printf("\tHEAP BINARIO\n\t1 - Inserir\n\t2 - Remover\n\t3 - Buscar\n");
	printf("\t4 - Imprimir\n\t5 - Novo heap\n\t6 - Sair\n\tEscolha: ");
	scanf("%d", &op);
	printf("\t------------\n\n");

	return op;
}

