typedef struct dados_matriz{ //facilita na passagem dos tamanhos
	int l; //linhas
	int c; //colunas
	int d; //dimensao
}Dados;

float*** aloca_matriz(Dados tam);
void preenche_matriz(Dados tam, float*** mat);
void coloca_todas_dimensoes(Dados tam, float*** mat, int i);
void imprime_matriz(Dados tam, float*** mat);
float relatorio_um(Dados tam, float*** mat);
float relatorio_dois(Dados tam, float*** mat);
int relatorio_tres(Dados tam, float*** mat);
int relatorio_quatro(Dados tam, float*** mat);
int relatorio_cinco(Dados tam, float*** mat);
void desaloca_matriz(Dados tam, float*** mat);