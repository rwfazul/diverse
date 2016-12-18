typedef struct lista {
	int linha; 
	int coluna; 
	int info;
	struct lista* prox; 
}Lista;

typedef struct esparsa{
	int linhas; 
	int colunas;
	struct lista* prim;
}Esparsa;

Lista* lst_cria(void);
Lista* lst_preenche(Esparsa e);
Lista* lst_insere (int i, int j, Lista* p, int valor); //chamada pela lst_preenche
Lista* lst_busca_ultimo(Lista* l);
void imprime_mat(Esparsa e);
void lst_imprime(Esparsa e);
bool consulta_elemento(Esparsa e);
bool soma_linha(Esparsa e);
float nao_nulos(Esparsa e);
void lst_desaloca(Lista* l);