// vetor.cpp
// Esse programa testa as TADs implementadas.
//
// The MIT License (MIT)
// 
// Copyright (c) 2016 JoÃ£o V. Lima, UFSM
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include <iostream>
#include <random>
#include <chrono>
#include <functional>

// Inclui definiÃ§Ãµes de TADs.
#include "vetor.hpp"

// define um ponto
struct Ponto {
    float x;
    float y;
};


void testa_vetor_inteiros(void)
{
	const int tamanho = 30; // vetor com 30
    tad::Vetor<int> vetor;   // vetor de inteiros
    
    auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    // gerador de nÃºmeros
    std::default_random_engine generator(seed);
    auto rand = std::bind(std::uniform_int_distribution<int>{0,100}, generator);

    std::cout << "Criando vetor..." << std::endl;
    vetor.cria( tamanho );

    // insere valores
	for(auto i= 0; i < tamanho; i++){
		/* cria um valor aleatÃ³rio */
        int valor = rand();
        vetor.insere( i, valor );
        std::cout << "inseriu " << valor << " no vetor (tamanho: " <<
            vetor.tamanho() << ")..." << std::endl;
	}
    // destroi vetor
    vetor.destroi();
}

void testa_vetor_pontos(void)
{
	const int tamanho = 30; // vetor com 30
    tad::Vetor<Ponto*> vetor; // vetor de ponteiros de Ponto
    
    auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    // gerador de nÃºmeros
    std::default_random_engine generator(seed);
    auto rand = std::bind(std::uniform_int_distribution<int>{0,100}, generator);

    std::cout << "Criando vetor..." << std::endl;
    vetor.cria( tamanho );

    // insere valores
	for(auto i= 0; i < tamanho; i++){
        Ponto* p = new Ponto;
        p->x = (1.0 * rand()) / 33.3;
        p->y = (1.0 * rand()) / 33.3;
        vetor.insere( i, p );
        std::cout << "i=" << i << " inseriu Ponto (" << p->x << ", " << p->y << ") no vetor (tamanho: " <<
            vetor.tamanho() << ") ..." << std::endl;
	}
	for(auto i= 0; i < tamanho; i++){
        Ponto* p = vetor.remove(0);
        std::cout << "i=" << i << " removeu Ponto (" << p->x << ", " << p->y << ") no vetor (tamanho: " <<
            vetor.tamanho() << ") ..." << std::endl;
        delete p;
    }
    // remove todos para liberar
    // destroi vetor
    vetor.destroi();
}

int main(int argc, char** argv)
{
    testa_vetor_inteiros();
    testa_vetor_pontos();
	return 0;
}