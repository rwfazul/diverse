#define MIN_HEAP 1
#define MAX_HEAP 2
#define RAIZ(x) (x - 1) / 2	 
#define FILHO_ESQ(x) (2 * x) + 1
#define FILHO_DIR(x) (2 * x) + 2

typedef struct heap {
	int* prioridades;  
	int tam;   // tamanho maximo 
	int pos;   // proxima pos livre
}Heap;

Heap* heap_cria(int max);
bool heap_insere(Heap* h, int prioridade, int tipo);
int heap_remove(Heap* h, int tipo);
void corrige_acima(Heap* h, int pos, int tipo);
void corrige_abaixo(Heap* h, int tipo);
void troca(int* v, int x, int y);
bool heap_busca(Heap* h, int busca);
int posicao(Heap* h, int valor);
void heap_imprime(Heap* h);
bool vazio(Heap *h);
void heap_libera(Heap* h);
