typedef struct lista {
	int linha; 
	int coluna; 
	int info;
	struct lista* prox; 
}Lista;

typedef struct identidade{
	int ordem;
	struct lista* prim;
}Identidade;


Lista* lst_cria(void);
Lista* lst_preenche(Identidade id);
Lista* lst_insere (int i, int j, Lista* p, int valor); //chamada pela lst_preenche
Lista* lst_busca_ultimo(Lista* l);
void imprime_mat(Identidade id);
bool verifica_matriz(Identidade id);
void aponta_erros(Identidade id);
void lst_desaloca(Lista* l);

