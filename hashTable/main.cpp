#include <iostream>
#include "hash.hpp"

using namespace std;
using namespace hashing;


int EscolhaMenu(void);

int main(int argc, char **argv) {
	int op;
	int v;

	TabelaHash* h = nullptr;
	h = h->CriaTabela();

	CadeiaElementos* c = nullptr;
	c = c->CriaCadeia();

	do {
		op = EscolhaMenu();

		switch(op) {
			case 1: cout << "Digite a chave: ";
					cin >> v;
					if (!h->TabelaCheia(h))
						h->InsereChaveTabela(h, v, v);
					else
						if (!c->InsereChaveCadeia(c, v))
							cout << "Cadeia cheia." << endl;
				break;
			case 2:	cout << "Digite a chave: ";
					cin >> v;	

					if (!h->BuscaChaveTabela(h, v))
						if (!c->BuscaChaveCadeia(c, v))
							cout << "Valor nao esta na tabela nem nas cadeias." << endl;
				break;
			case 3:	h->ImprimeTabela(h);
					if (c->CadeiaAtivada(c))
						c->ImprimeCadeia(c);	
					else
						cout << "\nNao ha cadeias de elemento ate o momento (Hash nao esta cheio)." << endl;
				break;
			case 4:	cout << "Fim." << endl;
				break;
			default: cout << "Opcao invalida. Digite novamente." << endl;

		}
		cout << endl;

	}while (op != 4);


	return 0;
}

int EscolhaMenu(void) {
	int op;

	cout << "\t--------------------" << endl;
	cout << "\tTabela Hash\n\t1 - Inserir\n\t2 - Buscar\n\t3 - Imprimir\n\t4 - Sair" << endl;
	cout << "\tEscolha uma opcao: ";
	cin >> op;
	cout << "\t--------------------\n" << endl;

	return op;
}
