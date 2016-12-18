#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "matriz.h"


int main(int argc, char **argv){
	float ***mat, relatorio_f;
	int relatorio_i;
	Dados tam;

	printf("Digite o numero de alunos, disciplinas e semestres: ");
	scanf("%d %d %d", &tam.l, &tam.c, &tam.d); //linha, coluna, dimensao
	tam.c +=1; //primeira coluna eh cod alunos

	mat = aloca_matriz(tam);
	preenche_matriz(tam, mat);

	imprime_matriz(tam, mat);

	int op;
	do{
		printf("\n\t1 - Relatorio 1\n\t2 - Relatorio 2\n\t3 - Relatorio 3\n\t4 - Relatorio 4\n\t5 - Relatorio 5\n\t6 - Sair\n\t");
		printf("Escolha a opcao: ");
		scanf("%d", &op);
		printf("\n");
		switch(op){
			case 1: relatorio_f = relatorio_um(tam, mat);
					if(relatorio_f != -1)
						printf("\n\tMedia do aluno: %.2f", relatorio_f);
					break;
			case 2:	relatorio_f = relatorio_dois(tam, mat);
					if(relatorio_f != -1)
						printf("\n\tMedia da disciplina: %.2f", relatorio_f);
					break;
			case 3:	relatorio_i = relatorio_tres(tam, mat);
					if(relatorio_i != -1)
						printf("\n\tAlunos aprovados: %d", relatorio_i);
					break;
			case 4: relatorio_i = relatorio_quatro(tam, mat); //impreme na funcao (causo tenha empate)
					break;
			case 5:	relatorio_i = relatorio_cinco(tam, mat);
					break;
			case 6:	printf("Fim.\n");
					break;
			default: printf("\tOpcao invalida.");

		}
		printf("\n");

	}while(op != 6);

	desaloca_matriz(tam, mat);

	return 0;
}
