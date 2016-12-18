#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "matriz.h"

/*representacao

	dimensao
								colunas
						aluno disc1 disc2 disc3 ...
						  0		1	  2		3
						-----------------------
					0|	cod   nota   nota
			linhas	1|	cod   nota 	 ...
					2|	cod   nota			
					3|	cod   nota


					demais dimensoes idem (muda notas)

							qt_disciplinas = numero_colunas - 1;

						**os indices sao convertidos na hora da busca 
						ex: pesquisa por semestre 0 ira exibir msg de sem. invalido 
								mat[..][..][0] (semestre 0) equivale a pesquisa por sem. 1
*/


float*** aloca_matriz(Dados tam){
	float ***mat;
	int i, j;
	
	mat = (float***) malloc(tam.l * sizeof(float**));

	for(i = 0; i < tam.l; i++)
		mat[i] = (float**) malloc(tam.c * sizeof(float*));

	for(i = 0; i < tam.l; i++)
		for(j = 0; j < tam.c; j++)
			mat[i][j] = (float*) malloc(tam.d * sizeof(float));

	return mat;
}

void preenche_matriz(Dados tam, float*** mat){
	int i, j, k;;
	float nota_d;

	for(k = 0; k < tam.d; k++){
		printf("\nSEMESTRE %d\n", k+1);
		for(i = 0; i < tam.l; i++){
			if(k == 0) //apenas pede o cod na dimensao 0
				coloca_todas_dimensoes(tam, mat, i);
			printf("\tNotas aluno %d (cod %0.f):\n", i+1, mat[i][0][k]);
			for(j = 1; j < tam.c; j++){
				printf("\t\tDisciplina %d: ", j);
				scanf("%f", &mat[i][j][k]); 
			}
		}
		printf("\n");
	}

}

void coloca_todas_dimensoes(Dados tam, float*** mat, int i){
 	int k;
 	float cod_aluno;

 	printf("Digite o cod do aluno num %d: ", i+1);
	scanf("%f", &cod_aluno);
 	//coloca cod do aluno em todas as linhas (coluna 0) de todas as dimensoes
	for(k = 0; k < tam.d; k++){
			mat[i][0][k] = cod_aluno;
	}
	
}

void imprime_matriz(Dados tam, float*** mat){
	int i, j, k, t; //t para imprimir a tabulacao dos nomes das disciplinas

	for(k = 0; k < tam.d; k++){
		printf("SEMESTRE %d\n", k+1);
		printf("Aluno\t");
		for(t = 1; t < tam.c; t++)
			printf("Disc %d\t", t);
		printf("\n");

		for(i = 0; i < tam.l; i++){
			for(j = 0; j < tam.c; j++){
				if(j != 0){ //notas{
					if(mat[i][j][k] != -1)
						printf("%.2f\t", mat[i][j][k]);
					else 
						printf(" -\t");
				}
				else 
					printf("%.0f\t", mat[i][j][k]); //imprime cod sem ,
			}
			printf("\n");
		}
		printf("\n");
	}


}

/*R1) a média de notas de um dado aluno informado pelo usuário (considere apenas as disciplinas cursadas por
aquele aluno)*/
float relatorio_um(Dados tam, float*** mat){
	int sem, disc_cursadas = 0, i, j;
	float cod, media = 0;
	bool achou = false;

	printf("Informe o semestre: ");
	scanf("%d", &sem);
	sem--;

	if(sem < 0 || sem >= tam.d){
		printf("\nSemestre invalido.");
		return -1;
	}

	printf("Informe o cod do aluno: ");
	scanf("%f", &cod);

	for(i = 0; i < tam.l && !achou; i++){
		if(cod == mat[i][0][sem]){
			for(j = 1; j < tam.c; j++){
				if(mat[i][j][sem] != -1){ //-1 = disciplina nao cursada
					media += mat[i][j][sem];
					disc_cursadas++;
				}	
			}
			achou = true;
		}
	}

	if(!achou){
		printf("\nAluno nao encontrado.");
		return -1;
	}

	if(!disc_cursadas){
		printf("\nO aluno nao cursou nenhuma disciplina.");
		return -1;
	}


	return (float) media/disc_cursadas;

}

/*R2) a média de notas de uma dada disciplina num dado semestre, informados pelo usuário (considere apenas
notas válidas)*/
float relatorio_dois(Dados tam, float*** mat){
	int sem, disc, qt_notas = 0, i;
	float media = 0;

	printf("Informe o semestre: ");
	scanf("%d", &sem);
	sem--;

	if(sem < 0 || sem >= tam.d){
		printf("\nSemestre invalido.");
		return -1;
	}

	printf("Infome a disciplina: ");
	scanf("%d", &disc);

	if(disc <= 0 || disc >= tam.c){
		printf("\nDisciplina invalida.");
		return -1;
	}

	for(i = 0; i < tam.l; i++){
		if(mat[i][disc][sem] != -1){
			media += mat[i][disc][sem];
			qt_notas++;
		}
	}

	if(!qt_notas){
		printf("\nNenhum aluno cursou essa disciplina no semestre.");
		return -1;
	}

	return (float) media/qt_notas;
}

/*R3) a qtidade de alunos que foram aprovados numa dada disciplina num certo semestre, informados pelo
usuário (nota>=5)*/
int relatorio_tres(Dados tam, float*** mat){
	int sem, disc, qt_alunos = 0, i;

	printf("Informe o semestre: ");
	scanf("%d", &sem);
	sem--;

	if(sem < 0 || sem >= tam.d){
		printf("\nSemestre invalido.");
		return -1;
	}

	printf("Infome a disciplina: ");
	scanf("%d", &disc);

	if(disc <= 0 || disc >= tam.c){
		printf("\nDisciplina invalida.");
		return -1;
	}

	for(i = 0; i < tam.l; i++){
		if(mat[i][disc][sem] >= 5)
			qt_alunos++;
	}
	
	return qt_alunos;
}

//R4) a disciplina que mais tem reprovações num dado semestre informado pelo usuário
int relatorio_quatro(Dados tam, float*** mat){
	int disc, sem, mais_repro, i, j;
	disc = tam.c -1;		
	int reprovados[disc]; //vetor com reprovacoes de cada disc. (1 coluna a menos por causa do cod) 

	printf("Informe o semestre: ");
	scanf("%d", &sem);
	sem--;

	if(sem < 0 || sem >= tam.d){
		printf("\nSemestre invalido.");
		return -1;
	}
 
	for(i = 0; i < disc; i++)  //inicia vet
		reprovados[i] = 0;

	for(j = 1; j < tam.c; j++){
		for(i = 0; i < tam.l; i++){
			if(mat[i][j][sem] < 5 && mat[i][j][sem] != -1){
				reprovados[j-1]++;
			}
		}
	}

	mais_repro = reprovados[0];

	for(i = 0; i < disc; i++){
		if(reprovados[i] > mais_repro)
			mais_repro = reprovados[i];
	}		

	if(!mais_repro){
		printf("\tA disciplina nao teve reprovacao no semestre.");
		return -1;
	}
	
	printf("\n\tDisciplinas(s) com mais reprovacoes: ");
	for(i = 0; i < disc; i++){ //caso tenha empate no numero de repro
		if(reprovados[i] == mais_repro)
			printf("Disciplina %d   ", i+1);
	}

	return 0;
}

//R5) o semestre em que os alunos mais tem reprovações
int relatorio_cinco(Dados tam, float*** mat){
	int i, j, k, repro = 0, mais_repro;
	int vet[tam.d];


	for(i = 0; i < tam.d; i++) //incia vet
		vet[i] = 0;


	for(k = 0; k < tam.d; k++){
		for(i = 0; i < tam.l; i++){
			for(j = 1; j < tam.c; j++){
				if(mat[i][j][k] != -1 && mat[i][j][k] < 5)
					repro++;
			}
		}

		vet[k] = repro;
		repro = 0;
	}

	mais_repro = vet[0];

	for(i = 0; i < tam.d; i++){
		if(vet[i] > mais_repro)
			mais_repro = vet[i];
	}		

	if(!mais_repro){
		printf("\tNenhum semestre teve reprovacoes.");
		return -1;
	}

	printf("\n\tSemestre(s) com mais reprovacoes: ");
	for(i = 0; i < tam.d; i++){ //caso tenha empate no numero de repro
		if(vet[i] == mais_repro)
			printf("Semestre %d   ", i+1);
	}

	return 0;
}

void desaloca_matriz(Dados tam, float*** mat){
	int i, j;

	for(i = 0; i < tam.l; i++)
		for(j = 0; j < tam.c; j++)
			free(mat[i][j]);

	for(i = 0; i < tam.l; i++)
		free(mat[i]);

	free(mat);
}
