#include <iostream>
#include "hash.hpp"

using namespace std;
using namespace hashing;

namespace hashing {


TabelaHash* TabelaHash::CriaTabela(void) {
	TabelaHash* h = new TabelaHash;
	h->pos = new Posicao[TAM_TABELA];
	h->QtdElementos = 0;

	for (auto i = 0; i < TAM_TABELA; i++)
		h->pos[i].estado = false;

	return h;
}

void TabelaHash::InsereChaveTabela(TabelaHash* h, int valor, int indice) {
	indice = HASH_FUNCTION(indice);

	if (!h->pos[indice].estado){
		h->pos[indice].valor = valor;
		h->pos[indice].estado = true;
		h->QtdElementos += 1;
		cout << valor << " foi inserido na tabela Hash, posicao " << indice << "." << endl;

		return;
	}

	else{
		indice = LINEAR_PROBING(indice);
		InsereChaveTabela(h, valor, indice);
	}
}

bool TabelaHash::TabelaCheia(TabelaHash* h) {
	return (h->QtdElementos >= TAM_TABELA);
}

bool TabelaHash::BuscaChaveTabela(TabelaHash* h, int valor) {
	auto indice = HASH_FUNCTION(valor);

	if (h->pos[indice].estado && h->pos[indice].valor == valor) {
		cout << valor << " encontrado na tabela Hash, posicao " <<indice << "." << endl;
		return true;

	}

	auto i = HASH_FUNCTION(LINEAR_PROBING(indice));

	while (i != indice && h->pos[i].estado) {
		if (h->pos[i].valor == valor) {
			cout << valor << " encontrado na tabela Hash, posicao " << i << "." << endl;
			return true;
		}
		
		i = HASH_FUNCTION(LINEAR_PROBING(i)); 
	}


	return false;
}	

void TabelaHash::ImprimeTabela(TabelaHash* h) {
	cout << "\t   Hashing" << endl;	
	cout << " ";

	for (auto i = 0; i < TAM_TABELA; i++){ 
		if (h->pos[i].estado)
			cout << h->pos[i].valor << "  ";
		else
			cout << "*  "; 
	}

	cout << endl;
}

CadeiaElementos* CadeiaElementos::CriaCadeia(void) {
	CadeiaElementos* c = new CadeiaElementos;
  	c->listas = new Posicao*[TAM_TABELA];  

  	for (auto i = 0; i < TAM_TABELA; i++)
      	c->listas[i] = new Posicao[TAM_LISTA];  

    for (auto i = 0; i < TAM_TABELA; i++)
    	for (auto j = 0; j < TAM_LISTA; j++)
    		c->listas[i][j].estado = false;

    c->CadeiaAtiva = false;

    return c;
}

bool CadeiaElementos::InsereChaveCadeia(CadeiaElementos* c, int valor) {
	auto indice = HASH_FUNCTION(valor);

	for (auto i = 0; i < TAM_LISTA; i++) {
		if (!c->listas[indice][i].estado) {
			c->listas[indice][i].valor = valor;
			c->listas[indice][i].estado = true;
			c->CadeiaAtiva = true;
			cout << valor << " foi inserido na lista " << indice << ", posicao " << i << "." << endl;

			return true;
		}
	}

	return false;
}

bool CadeiaElementos::CadeiaAtivada(CadeiaElementos* c) {
	return (c->CadeiaAtiva);
}

bool CadeiaElementos::BuscaChaveCadeia(CadeiaElementos* c, int valor) {
	auto indice = HASH_FUNCTION(valor);

	for (auto i = 0; i < TAM_LISTA; i++){
		if (c->listas[indice][i].valor == valor){
			cout << valor << " encontrado na lista " << indice << ", posicao " << i << "." << endl;
			return true;
		}
	}
	
	return false;

}

void CadeiaElementos::ImprimeCadeia(CadeiaElementos* c) {
	cout << "\nCadeias " << endl;

	for (auto i = 0; i < TAM_TABELA; i++) {
		if(i < 10)
			cout << " c" << i << ": ";
		else
			cout << "c" << i << ": ";

		for (auto j = 0; j < TAM_LISTA; j++) {
			if (c->listas[i][j].estado)
				cout << c->listas[i][j].valor << "  ";
			else
				cout << "*  ";
		}
		cout << endl;
	}

	cout << endl;
}

};	// namespace Hash