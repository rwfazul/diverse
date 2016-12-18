#define MAX_NOMEDIR 		50	
#define MAX_NOMETXT			50
#define MAX_TAMPALAVRA		50	
#define MAX_STRING			256
#define MAX_BUFFER			256

typedef struct diretorio{
	char nome_dir[MAX_NOMEDIR];
	struct arquivo* arquivos;
	int qtd_txts;
	int existeCaminho;
} Diretorio;

Diretorio* cria_diretorio(void);
void mapeia_diretorio(Diretorio* d);
int filter(const struct dirent* entry);
void diretorio_desaloca(Diretorio* d);

typedef struct arquivo {
	char nome_txt[MAX_NOMETXT];
	int buscas_encontradas;
	struct busca* buscas;
	struct arquivo* prox;
} Arquivo;

Arquivo* cria_arquivo(void);
Arquivo* insere_arquivo(Arquivo* a, char* nome);
void limpa_arquivos(Arquivo* a);
void arquivo_desaloca(Arquivo* a);

typedef struct busca {
	char palavra[MAX_TAMPALAVRA];
	struct busca* prox;
} Busca;

Busca* cria_busca(void);
Busca* insere_busca(Busca* b, char* palavra);
void busca_desaloca(Busca* b);
void procura_palavras(Diretorio* d, Busca* b);
void compara_busca(Busca* b, char* str, Arquivo* txt);
void imprime_resultados(Diretorio* d, Busca* b, int qtd);
