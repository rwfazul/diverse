#include <iostream>
#include <cmath>
#include <random>
#include <chrono>
#include <functional>

#pragma once

using namespace std;

#define gl 7
#define gc 4
#define hl 3
#define hc 7
#define rl 4
#define rc 7

int* aloca_vetor(const int tam_vet){
	int* vet{nullptr};
  	vet = new int[tam_vet];  

	return vet;
}

int* multiplica_Gp(int G[][gc], int* p){
	int* x = aloca_vetor(gl);

	//faz G*p
	for(auto i = 0; i < gl; i++){
		x[i] = 0;
		for(auto j = 0; j < gc; j++)
			x[i] += G[i][j] * p[j];
	}

	//x = mod 2 no vetor resultante de G*p
	for(auto i = 0; i < gl; i++)
		x[i] = x[i] % 2;

	return x;
}

int* multiplica_Hr(int H[][hc], int* r){
	int* z = aloca_vetor(hl);

	//faz H*r
	for(auto i = 0; i < hl; i++){
		z[i] = 0;
		for(auto j = 0; j < hc; j++)
			z[i] += H[i][j] * r[j];
	}

	//z = mod 2 no vetor resultante de H*p
	for(auto i = 0; i < hl; i++)
		z[i] = z[i] % 2;

	return z;
}

int* multiplica_Rr(int R[rl][rc], int* r){
	int* pr = aloca_vetor(rl);

	//faz R*z
	for(auto i = 0; i < rl; i++){
		pr[i] = 0;
		for(auto j = 0; j < rc; j++)
			pr[i] += R[i][j] * r[j];
	}

	return pr;
}

void injecao_erros(int* r){ 
	//random 2 4 5 6 
	random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, 2); // de 0 a 2 erros

    int bit1, bit2, random = dis(gen);

    if(random > 0){
    	if(random == 1){
    		uniform_int_distribution<> dis(0, 1);
    		bit1 = dis(gen);

   		 	if(!bit1)
   		 		bit1 = 1;
   			else 
    			bit1 = 4;

   		 	if(r[bit1]) //inverte bit
    	 		r[bit1] = 0;
    		else
    		 	r[bit1] = 1;
    	}   
    	if(random == 2){ //dois bits mudados
   			bit2 = 4;

    		if(r[bit2]) //inverte bit
    			r[bit2] = 0;
          	else
    			r[bit2] = 1;

   			uniform_int_distribution<> dis(0, 3);
   			bit2 = dis(gen);

   			if(bit2 == 1)
   				bit2 = 5;

   			if(r[bit2]) //inverte bit
    	 		r[bit2] = 0;
    		else
    		 	r[bit2] = 1;
    	} 
    }
}

bool verifica_z(int* z){
	for(auto i = 0; i < hl; i++)
		if(z[i] != 0)
			return false;

	return true;
}

void trata_erros(int H[hl][hc], int* r, int* z){
	int decimal = 0;

	for(auto i = 0; i < hl; i++){
		decimal += z[i] * pow(2,(hl-i-1)); //converte para decimal
	}

	if(r[decimal-1])
		r[decimal-1] = 0;
	else
		r[decimal-1] = 1;

	z = multiplica_Hr(H, r);

	if(!verifica_z(z))
		trata_erros(H, r, z);//recurssao p/ caso tenha + de 1 erro
}