// Calculadora.hpp
// TAD que implementa uma calculadora
//
// The MIT License (MIT)
// 
// Copyright (c) 2016 João V. Lima, UFSM
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software withouxt restriction, including without limitation the rights
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

// ver http://en.cppreference.com/w/cpp/container/stack

#pragma once //inclui apenas uma vez

#include <stack>

template<typename T>
struct Calculadora {
    std::stack<T> operandos;    // números, basicamente
    std::stack<char> operadores; // operadores: +, -, /, *
    bool correta = true;


    // void cria(void){  }   // cria a calculadora (nao necessario)

    void destroi(void){ // destroi a calculadora, limpa as pilhas
        while(!operandos.empty()) //enquanto nao estiverem vazias
            operandos.pop();
        while(!operadores.empty())
            operadores.pop();
    }

    void operando(T op){    // insere um novo operando para o calculo
        operandos.push(op);
    }

    void operador(char op){
        switch(op){
            case '(': operadores.push(op);
                break;
            case ')': while(correta && !operandos.empty() && operadores.top() != '(') //se for fecha parenteses calcula tudo dentro
                         calcula();
                      if(!operadores.empty())
                         operadores.pop();
                break;

            case '/': // nao precisa se preocupar com precedencia com / ou *
            case '*': operadores.push(op);
                break;

            case '+':
            case '-': if(operandos.empty())
                         correta = false;
                      if(!operadores.empty() && correta)
                         precedencia();  // * e / tem precedencia sobre + e - 
                      operadores.push(op);
                break;
        }
    }

    void precedencia(void){ //verifica precendencia dos operadores (+ ou - ainda n foram inseridos)
        if(operadores.top() == '*' || operadores.top() == '/'){
            T num_a = operandos.top();
            operandos.pop();

            if(!operandos.empty()){
                T num_b = operandos.top();
                operandos.pop();

                //calcula expressao com precedencia
                if(operadores.top() == '*') 
                    operandos.push(num_b * num_a);
                else
                    operandos.push(num_b / num_a);

                operadores.pop(); //remove operador da expresao calculada (* ou /)

                /* recursiva para casos como     3 * 4 / 2 + 1 
                    pois resultado seria:        3 *   2   + 1 
                                (e deve-se verificar dnv, se nao resultado sera 9, pois ira somar 2 + 1 antes)

                */
                if(!operadores.empty()) 
                      precedencia();  // * e / tem precedencia sobre + e - 
            }
            else
                correta = false;

        }

        /*           para casos como:          2  - 4  + 6 
           sem verificar com  + e - faria:      2    -  10      = -8
 
        */
        else if(operadores.top() == '+' || operadores.top() == '-'){
 
            T num_a = operandos.top();
            operandos.pop();

            if(!operandos.empty()){
                T num_b = operandos.top();
                operandos.pop();

                //calcula expressao com precedencia
                if(operadores.top() == '+') 
                    operandos.push(num_b + num_a);
                else
                    operandos.push(num_b - num_a);

                operadores.pop(); //remove operador da expresao calculada (* ou /)

                if(!operadores.empty()) 
                      precedencia();  // * e / tem precedencia sobre + e - 
            }
            else
                correta = false;

        }
    }

    void calcula(void){ //qdo estiver tudo certo (sem precedencia e parenteses ) calcula expressoes
        T num_a = operandos.top();
        operandos.pop();

        if(!operandos.empty()){
            T num_b = operandos.top();
            operandos.pop();

            switch(operadores.top()){
                case '*':
                    operandos.push(num_b * num_a);
                    break;
                case '/':
                    operandos.push(num_b / num_a);
                    break;
                case '+':
                    operandos.push(num_b + num_a);
                    break;
                case '-':
                    operandos.push(num_b - num_a);
                    break;
            }
            operadores.pop();
        }
        else
            correta = false;
    }

    bool fim(void) {
        if(!correta)
            return false;

        while(!operadores.empty() && !operandos.empty()) //enquanto n tiver vazia chama funcao de calcular
            calcula();

        if(operandos.empty())
            return false;

        T resultado = operandos.top(); //salva resultado final e desempilha (para verificao)
        operandos.pop();

        if(!operadores.empty() || !operandos.empty()){ //se alguma das filas nao estiver vazia retorna erro
            correta = false;
            return false;  //se empilhar antes de retornar pode imprimir o resul errado
        }
        operandos.push(resultado); //nao encontrou erro, empilha resultado novamente

        return true;
    }

    T resultado(void) { //retorna resultado da expressao (topo da pila operandos)
        if(!operandos.empty() && correta)
            return operandos.top();
        
        return 0;
    }

};

