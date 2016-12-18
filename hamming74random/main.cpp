#include <iostream>
#include <random>
#include <chrono>
#include <functional>
#include "matriz.hpp"

using namespace std;

#define gl 7
#define gc 4
#define hl 3
#define hc 7
#define rl 4
#define rc 7

int main(int argv, char** argc){	
	int G[gl][gc] = { {1, 1, 0, 1 }, //matriz geradora
			       	  {1, 0, 1, 1 },
		   	   		  {1, 0, 0, 0 },
		  	    	  {0, 1, 1, 1 },
			  		  {0, 1, 0, 0 },
			  		  {0, 0, 1, 0 },
			   		  {0, 0, 0, 1 } };

	int H[hl][hc] = { {1, 0, 1, 0, 1, 0, 1 }, //matriz de paridade
					  {0, 1, 1, 0, 0, 1, 1 },
					  {0, 0, 0, 1, 1, 1, 1 } };

	int R[rl][rc] = { {0, 0, 1, 0, 0, 0, 0 }, //matriz de descodificacao
					  {0, 0, 0, 0, 1, 0, 0 },			
					  {0, 0, 0, 0, 0, 1, 0 }, 
					  {0, 0, 0, 0, 0, 0, 1 } };

	int *p = aloca_vetor(gc); //codework original (lido do usuario)
	cout << "Digite os 4 bits: ";
	for(auto i = 0; i < gc; i++)
		cin >> p[i];


	int* r = multiplica_Gp(G, p); // r = x
	injecao_erros(r);
	int* z = multiplica_Hr(H, r);


	if(verifica_z(z)){ //se todo vetor z for 0 nao ha erros
		cout << "\nNao houve erros na trasmissao. ";
		cout << "Descodificando msg: " << endl;
	}else{
		cout << "\nHouve erros na trasmissao. ";
		cout << "Trantando erros e descodificando msg: " << endl;
		trata_erros(H, r, z);
	}

	int *pr = multiplica_Rr(R, r); //descodificacao

	cout << "\nMensagem enviada: ";
	for(auto i = 0; i < rl; i++)
		printf("%d ", pr[i]);

	cout << endl;


	//desalocar td

	cout << endl;

	return 0;
}