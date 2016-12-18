###############################################################################
# Makefile para compilacao
###############################################################################
# define o compilador C++
CXX = g++
# define flags do compilador
CXXFLAGS = -Wall -g -std=c++11
# define flags do ligador
LDFLAGS = -lm

# define uma variavel com o nome do programa
PROG = principal

###############################################################################
# comeca aqui os alvos de compilacao
# cada alvo e formado de:
# alvo: dep1 dep2 
# 
# onde alvo e o arquivo gerado, e dep1 e dep2 sao dependencias para gerar o alvo.

# o primeiro alvo e o padrao.
all: principal

# descreve o objeto principal.o, compilado de forma implicita
principal.o: principal.cpp Calculadora.hpp

# programa principal, compilado de forma implicita
principal: principal.o 
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)
	

# comando para limpar arquivos, digite
# $ make clean 
clean:
	rm -f *.o $(PROG)
