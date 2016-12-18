typedef struct diagonal{
	int ordem; //ordem da matriz
	int* v; //vetor com os valores da diagonal p. da matriz
}Diagonal;

Diagonal* aloca_vetor(int tam);
void preenche_vetor (Diagonal* m);
void imprime_matriz(Diagonal* m);
bool busca_elemento(int l, int c, Diagonal* m);
