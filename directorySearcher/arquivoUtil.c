#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include "arquivoUtil.h"

Diretorio* cria_diretorio(void) {
	Diretorio* d = (Diretorio*) malloc(sizeof(Diretorio));
	d->arquivos = cria_arquivo();
	d->qtd_txts = 0;
	d->existeCaminho = 0;

	return d;
}

Arquivo* cria_arquivo(void) {
	return NULL;
}

Arquivo* insere_arquivo(Arquivo* a, char* nome) {
	Arquivo* novo = (Arquivo*) malloc(sizeof(Arquivo));
	novo->buscas_encontradas = 0;
	strcpy(novo->nome_txt, nome);
	novo->buscas = cria_busca();
	novo->prox = a;

	return novo;
}

void limpa_arquivos(Arquivo* a) {
	Arquivo* p = a;

	while(p != NULL){
		busca_desaloca(p->buscas);
		p->buscas = NULL;
		p->buscas_encontradas = 0;
		p = p->prox;
	}
}

void arquivo_desaloca(Arquivo* a) {
	Arquivo* p = a;

	while(p != NULL){
		busca_desaloca(p->buscas);
		a = p->prox;
		free(p);
		p = a;
	}
}

void mapeia_diretorio(Diretorio* d) {
	struct dirent **nameList; // varia de sistema pra sistema, mas tamanho e nome sempre tem
	// alphasort -> alphabet sort (quick sort alfabetico)
	int n = scandir(d->nome_dir, &nameList, filter, alphasort);
	d->qtd_txts = n;

	if (n < 0) {
		perror("Scandir"); // msg padrao sistema : + " "
		exit(1);
	}
	else if (n == 0) {
		printf("Nenhum arquivo .txt no diretorio atual.\n\n");
		exit(1);
	} else {
		int count = 0;
		while (n--) {
			d->arquivos = insere_arquivo(d->arquivos, nameList[n]->d_name);
			free (nameList[n]);
			count++;
		}
		free (nameList);
	}	
}

int filter(const struct dirent* entry) { 
	return strstr(entry->d_name, ".txt"); // apenas arquivos que tiverem .txt no nome 
}


void diretorio_desaloca(Diretorio* d) {
	arquivo_desaloca(d->arquivos);
	free(d);
}

Busca* cria_busca(void) {
	return NULL;
}

Busca* insere_busca(Busca* b, char* palavra) {
	Busca* novo = (Busca*) malloc(sizeof(Busca));
	strcpy(novo->palavra, palavra);
	novo->prox = b;

	return novo;
}

void busca_desaloca(Busca* b) {
	Busca* p = b;

	while(p != NULL){
		b = p->prox;
		free(p);
		p = b;
	}
}

void procura_palavras(Diretorio* d, Busca* b) {
	char str[MAX_STRING], buffer[MAX_BUFFER];
	// delimitadores nao sao considerados no parsing (auotomato de tokens)
	// por exemplo para deixar apenas palavras em um arquivo .c
	// char delimitadores[] = {" \n\t<>\"();[],"}; etc
	char delimitadores[] = {" \n"};
	char *aux;
	int i;
	Arquivo* a;

	FILE *arq;
	for (a = d->arquivos; a != NULL; a = a->prox) {
		char caminho[100];

		if (d->existeCaminho) {
			strcpy(caminho, d->nome_dir);
			if (d->nome_dir[(strlen(d->nome_dir)-1)] != '/') 
				strcat(caminho, "/");
			strcat(caminho, a->nome_txt);
			arq = fopen(caminho, "r");
		} else
			arq = fopen(a->nome_txt, "r");

		if (arq == NULL) {
			printf("Arquivo nao encontrado.\n\n");
			exit(1);
		}

		while (fgets(buffer, MAX_BUFFER, arq) != NULL) {
			// strtok = funcao destruidora (vai destuir string buffer), por causa que remove delimitadores
			// tb mantem o estado (msm chamando com NULL ainda tem a antiga str (static)) : outros ex: random
			aux = strtok(buffer, delimitadores);
			if (aux != NULL) 
				strncpy(str, aux, MAX_STRING);
			do { 
				compara_busca(b, str, a); 
				aux = strtok(NULL, delimitadores);
				if (aux != NULL)
					strncpy(str, aux, MAX_STRING);
			} while(aux != NULL); // mais de uma palavra na msm linha
		}
		fclose(arq);
	}
}

void compara_busca(Busca* b, char* str, Arquivo* txt) {
	Busca* p;

	for (p = b; p != NULL; p = p->prox) {
		if (strcmp(p->palavra, str) == 0) {
			txt->buscas = insere_busca(txt->buscas, p->palavra);
			txt->buscas_encontradas = txt->buscas_encontradas + 1;
		}
	}
}

void imprime_resultados(Diretorio* d, Busca* b, int qtd) {
	Arquivo* a;

	for (a = d->arquivos; a != NULL; a = a->prox) {
		printf("\n\t\t-----------------------------------\n");
		printf("\tArquivo \"%s\": ", a->nome_txt);
		int qtd_palavras = a->buscas_encontradas;
		printf("contem %d das palavras buscadas.", qtd_palavras);
		if (qtd_palavras == qtd)
			printf("\n\t(arquivo contem TODAS as palavras buscadas)");
		else if (qtd_palavras == 0)
			printf("\n\t(arquivo nao contem nenhuma das palavras buscadas)");
		printf("\n");
		Busca* buscas;
		for (buscas = a->buscas; buscas != NULL; buscas = buscas->prox) {
			printf("%s", buscas->palavra);
			if (buscas->prox != NULL)
				printf(", ");
			else
				printf(".");
		}
		printf("\n");
	}
} 
