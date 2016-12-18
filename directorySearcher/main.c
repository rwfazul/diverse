#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include "arquivoUtil.h"

void msgUso();
Busca* le_palavras(int* qtd);
int buscar_novamente();

int main(int argc, char const *argv[]) {
	int* qtd;
	msgUso();

	Diretorio* d = cria_diretorio();

	if (argc > 1) {
		strcpy(d->nome_dir, argv[1]);
		d->existeCaminho = 1;
	} else
		strcpy(d->nome_dir, "."); // diretorio atual

	mapeia_diretorio(d); 

	do {
		Busca* b = le_palavras(qtd);
		procura_palavras(d, b);
		imprime_resultados(d, b, *qtd); 
		limpa_arquivos(d->arquivos);
		busca_desaloca(b);
	} while (buscar_novamente() == 1);

	diretorio_desaloca(d);

	return 0;
}

void msgUso() {
	printf("\n\t\t\t*** Uso ***\na) Executar no mesmo diretorio onde os .txt se encontram.");
	printf("\nb) Utilizar caminho absoluto do diretorio como argumento padrao (argv).");
	printf("\n\t\t\t****    ****\n\n");
}

Busca* le_palavras(int* qtd) {
	Busca* b = cria_busca();
	printf("\n\t\t\t------  POD  ------\n\n");
	printf("A seguir digite cada palavra para busca, para finalizar digite \"0\"\n\n");
	char palavra[MAX_TAMPALAVRA];
	int i = 0;
	do {
		printf("Palavra %d: ", i + 1);
		scanf("%s", palavra);
		if (strcmp (palavra, "0") == 0)
			break;
		b = insere_busca(b, palavra);
		i++;
	} while(1);

	*qtd = i;

	return b;
}

#define LimparBuffer while(getchar()!='\n');
int buscar_novamente() {
	int op, invalida;
	do {
		printf("\n-----------------------------------\n");
		printf("Deseja realizar mais uma busca?\n\t1 - Sim\n\t2 - Nao\n\tEscolha: ");
		scanf("%d", &op);
		LimparBuffer;
		invalida = (op != 1 && op != 2) ? 1 : 0;
		printf ("-----------------------------------\n");
		if (invalida)
			printf("\nOpcao invalida. Escolha novamente.\n");
	} while (invalida);

	return op;
}
