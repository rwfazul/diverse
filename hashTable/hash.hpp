#pragma once

namespace hashing {

#define TAM_TABELA 11
#define TAM_LISTA 4
#define PLUS 2
#define LINEAR_PROBING(x) x + PLUS
#define HASH_FUNCTION(x) x % TAM_TABELA	

struct Posicao {
	bool estado;
	int valor;
}; // struct Posicao

struct TabelaHash {
	Posicao* pos;
	int QtdElementos;

	TabelaHash* CriaTabela(void);
	void InsereChaveTabela(TabelaHash* h, int valor, int indice);
	bool TabelaCheia(TabelaHash* h);
	bool BuscaChaveTabela(TabelaHash *h, int valor);
	void ImprimeTabela(TabelaHash* h);
	
}; // struct TabelaHash

struct CadeiaElementos {
	Posicao** listas;
	bool CadeiaAtiva;

	CadeiaElementos* CriaCadeia(void);
	bool InsereChaveCadeia(CadeiaElementos* c, int valor);
	bool CadeiaAtivada(CadeiaElementos* c);
	bool BuscaChaveCadeia(CadeiaElementos* c, int valor);
	void ImprimeCadeia(CadeiaElementos* c);

}; // struct CadeiaElemento

};	// namespace Hash