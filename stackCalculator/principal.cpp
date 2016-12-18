#include <iostream>
#include "Calculadora.hpp"

int main(int argc, char** argv)
{
    Calculadora<float> calc;
    float x;

    calc.operador('(');
    calc.operando(3.0);
    calc.operador('+');
    calc.operando(6.0);
    calc.operador(')');
    calc.operador('*');
    calc.operando(2.0);
    calc.operador('+');
    calc.operando(7.0);
    
    if(calc.fim() == false)
        std::cout << "ERRO: formula errada!" << std::endl;
    
    x = calc.resultado();
    std::cout << "(3+6)*2+7 = " << x << std::endl;
    calc.destroi();
    return 0;
}
