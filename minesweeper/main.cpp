#include <iostream>
#include <random>
#include <functional>

using namespace std;

struct Minas{
	char exibe; //o que esta sendo mostrado para o usuario
	int bombas_redor; //bombas ao redor de cada casa do campo
	bool aberta;
	bool bomba;
	bool bandeira;
};

Minas** inicia_jogo(int *N);
void coloca_bombas(Minas** matriz, int N); //chamada por inicia_jogo
void conta_bombas(Minas** matriz, int N); //chamada por inicia_jogo
int le_opcao(); //revelar, bandeira, novo jogo, terminar jogo
bool exibe_quadrado(Minas** matriz, int N);  
void coloca_bandeira(Minas** matriz, int N);
void le_jogada(Minas** matriz, int N, int *i, int *j); //le indices i e j (revelar e bandeira)
void abre_vazio(Minas** matriz, int N, int i, int j); //recursiva
void converte_exibe(Minas** matriz, int N, int i, int j); //bombas_redor para o exibe
void imprime_matriz(Minas** matriz, int N);
bool verifica_ganhou(Minas** matriz, int N);
void destroi_matriz(Minas** matriz, int N);


int main(){
	int N = 0, op;
	bool game_over = false, ganhou;
	char novamente;

	Minas** matriz = inicia_jogo(&N);

	while(!game_over){
		imprime_matriz(matriz, N);
		op = le_opcao();
		switch(op){
			case 1: game_over = exibe_quadrado(matriz, N);
					if(game_over){
						imprime_matriz(matriz, N);
						cout << "\t****VOCE PERDEU.****\n" << endl;
						cout <<"\tDeseja jogar novamente (S ou N)? ";
						cin >> novamente;
						if(novamente == 'S' || novamente == 's'){
							game_over = false;
							destroi_matriz(matriz, N);
							cout << "\n\t****NOVO JOGO INCIADO.****\n" << endl;
							matriz = inicia_jogo(&N);
						}
						else
							cout << "\n\t****VOCE TERMINOU O JOGO.****\n" << endl;
					}
					break;
			case 2: coloca_bandeira(matriz, N);
					break;
			case 3: destroi_matriz(matriz, N);
					cout << "\n\t****NOVO JOGO INCIADO.****\n" << endl;
					matriz = inicia_jogo(&N);
					break; 
			case 4: cout << "\n\t****VOCE TERMINOU O JOGO.****\n" << endl;
					game_over = true;
					break;
		}
		 
		ganhou = verifica_ganhou(matriz, N);
		if(ganhou){
			imprime_matriz(matriz, N);
			cout << "\n\t****PARABENS! VOCE GANHOU.****\n" << endl;
			cout <<"\tDeseja jogar novamente (S ou N)? ";
			cin >> novamente;
			if(novamente == 'S' || novamente == 's'){
					game_over = false;
					destroi_matriz(matriz, N);
					cout << "\n\t****NOVO JOGO INCIADO.****\n" << endl;
					matriz = inicia_jogo(&N);
			}
			else{
				game_over = true;
				cout << "\n\t****VOCE TERMINOU O JOGO.****\n" << endl;
			}
		}
	}

	destroi_matriz(matriz, N);
	return 0;
}

Minas** inicia_jogo(int *N){
	bool ok;
	do{
		cout << "Digite o tamanho da matriz: ";
		ok = true;
		cin >> *N;
		if(*N < 2){
			cout << "ERRO: Tamanho invalido."<< endl;
			ok = false;
		}
	}while(!ok);

	//aloca matriz
	Minas** matriz{nullptr};
  	matriz = new Minas*[*N];  

  	for(auto i = 0; i < *N; i++)
      matriz[i] = new Minas[*N];  

  	//inicia campos
   	for(auto i = 0; i < *N; i++){ 
   		for(auto j = 0; j < *N; j++){
    		matriz[i][j].exibe = '-';
    		matriz[i][j].bombas_redor = 0;
    		matriz[i][j].aberta = false;
    		matriz[i][j].bomba = false;
    		matriz[i][j].bandeira = false;
    	}
   	}  

 	coloca_bombas(matriz, *N);
	conta_bombas(matriz, *N);

 	return matriz;
}

void coloca_bombas(Minas** matriz, int N){
	int num_bombas, bombas_colocadas = 0, random;
	bool ok;
	do{
		cout << "Digite o numero de bombas: ";
		ok = true;
		cin >> num_bombas;
		if(num_bombas >= N*N){
			cout << "ERRO: Numero de bombas invalido."<< endl;
			ok = false;
		}
	}while(!ok);

	random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, 9);

	while(bombas_colocadas < num_bombas){
		for(auto i = 0; i < N; i++){
			for(auto j = 0; j < N && bombas_colocadas < num_bombas; j++){
				random = dis(gen);
				if(random == 1 && !matriz[i][j].bomba){ //so coloca bomba se rand de 0 a 9 for 1
 					matriz[i][j].bomba = true;
					bombas_colocadas++;
				} 
			}
		}
	}
	
}

void conta_bombas(Minas** matriz, int N){
	int num_bombas = 0;

	for(auto i = 0; i < N; i++){
		for(auto j = 0; j < N; j++){
			if (!matriz[i][j].bomba){
				if(i == 0 && j == 0){ //superior esquerdo
					if(matriz[i][1].bomba)
						num_bombas++;
					if(matriz[1][j].bomba)
						num_bombas++;
					if(matriz[1][1].bomba)
						num_bombas++;
				}
				else if(i == 0 && j == N-1){ // superior direito
					if(matriz[i][j-1].bomba)
						num_bombas++;
					if(matriz[1][j].bomba)
						num_bombas++;
					if(matriz[1][j-1].bomba)
						num_bombas++;
				} 
				else if(i == N-1 && j == 0){ // inferior esquerdo
					if(matriz[i-1][j].bomba)
						num_bombas++;
					if(matriz[i][j+1].bomba)
						num_bombas++;
					if(matriz[i-1][j+1].bomba)
						num_bombas++;
				}
				else if(i == N-1 && j == N-1){ // inferior direito
					if(matriz[i][j-1].bomba)
						num_bombas++;
					if(matriz[i-1][j].bomba)
						num_bombas++;
					if(matriz[i-1][j-1].bomba)
						num_bombas++;
				}
				else if(i == 0){ // linha cima
					if(matriz[i][j-1].bomba)
						num_bombas++;
					if(matriz[i][j+1].bomba)
						num_bombas++;
					if(matriz[i+1][j].bomba)
						num_bombas++;
					if(matriz[i+1][j-1].bomba)
						num_bombas++;
					if(matriz[i][j+1].bomba)
						num_bombas++;
				}
				else if(i == N-1){ // linha baixo
					if(matriz[i][j-1].bomba)
						num_bombas++;
					if(matriz[i][j+1].bomba)
						num_bombas++;
					if(matriz[i-1][j].bomba)
						num_bombas++;
					if(matriz[i-1][j-1].bomba)
						num_bombas++;
					if(matriz[i-1][j+1].bomba)
						num_bombas++;
				}
				else if(j == 0){ // coluna esquerda
					if(matriz[i-1][j].bomba)
						num_bombas++;
					if(matriz[i+1][j].bomba)
						num_bombas++;
					if(matriz[i][j+1].bomba)
						num_bombas++;
					if(matriz[i+1][j+1].bomba)
						num_bombas++;
					if(matriz[i-1][j+1].bomba)
						num_bombas++;
				}
				else if(j == N-1){ // coluna direita
					if(matriz[i+1][j].bomba)
						num_bombas++;
					if(matriz[i-1][j].bomba)
						num_bombas++;
					if(matriz[i][j-1].bomba)
						num_bombas++;
					if(matriz[i+1][j-1].bomba)
						num_bombas++;
					if(matriz[i-1][j-1].bomba)
						num_bombas++;
				}
				else if(i > 0 && j > 0){ //centro
					if(matriz[i][j-1].bomba)
						num_bombas++;
					if(matriz[i][j+1].bomba)
						num_bombas++;
					if(matriz[i-1][j].bomba)
						num_bombas++;
					if(matriz[i+1][j].bomba)
						num_bombas++;
					if(matriz[i-1][j-1].bomba)
						num_bombas++;
					if(matriz[i+1][j+1].bomba)
						num_bombas++;
					if(matriz[i-1][j+1].bomba)
						num_bombas++;
					if(matriz[i+1][j-1].bomba)
						num_bombas++;
				}	

				matriz[i][j].bombas_redor = num_bombas;
				num_bombas = 0;
			}
		}
	}
}


int le_opcao(){
	int op;
	bool ok;
	cout << "\t1 - Revelar um quadrado\n\t2 - Colocar uma bandeira" << endl;
	cout << "\t3 - Inicar um novo jogo\n\t4 - Terminar o jogo\n\tEscolha sua jogada: ";
	do{
		ok = true;
		cin >> op;
		if(op < 1 || op > 4){
			cout << "Opcao invalida. Escolha novamente: ";
			ok = false;
		}
	}while(!ok);

	return op;
}

bool exibe_quadrado(Minas** matriz, int N){
	int i, j;
	bool game_over = false;
	le_jogada(matriz, N, &i, &j);

	if(matriz[i][j].bomba){
		for(auto i = 0; i < N; i++){ //quando perde revela todas as bombas do mapa
			for(auto j = 0; j < N; j++){ 
				if(matriz[i][j].bomba)
					matriz[i][j].exibe = '*';
			}
		}
		game_over = true;
		return game_over;
	}

	else if(matriz[i][j].bombas_redor > 0) // se for numero apenas mostras ele
		converte_exibe(matriz, N, i, j);
	

	else if(matriz[i][j].bombas_redor == 0)  
		abre_vazio(matriz, N, i, j);
	

	return game_over;
}

void coloca_bandeira(Minas** matriz, int N){
	int i, j;
	cout <<"\tOpcao colocar bandeira: " << endl;
	le_jogada(matriz, N, &i, &j);
	matriz[i][j].exibe = '?';
}

void le_jogada(Minas** matriz, int N, int *i, int *j){
	bool ok;
	cout << "\tDigite a linha (i): ";
	do{
		do{
			ok = true;
			cin >> *i;
			if(*i < 0 || *i > N-1){
				cout << "Linha invalida. Digite novamente: ";
				ok = false;
			}
		}while(!ok);

		cout << "\tDigite a coluna (j): ";
		do{
			ok = true;
			cin >> *j;
			if(*j < 0 || *j > N-1){
				cout << "Coluna invalida. Digite novamente: ";
				ok = false;
			}
		}while(!ok);

		if(matriz[*i][*j].aberta){
			cout << "Essa casa ja esta aberta. Jogue novamente." << endl;
		 	ok = false;
		}

	}while(!ok);
}

void abre_vazio(Minas** matriz, int N, int i, int j){
	bool continua = true;

	if(i < 0 || i > N-1 || j < 0 || j > N-1){
		continua = false;
	}

	else if(matriz[i][j].aberta || matriz[i][j].bombas_redor > 0){
		converte_exibe(matriz, N, i, j);
		continua = false;
	}

	else if (continua){
		converte_exibe(matriz, N, i, j);
		//recursivas
		abre_vazio(matriz, N, i+1, j); //linhas
		abre_vazio(matriz, N, i-1, j);
		abre_vazio(matriz, N, i, j+1); //colunas
		abre_vazio(matriz, N, i, j-1);
		abre_vazio(matriz, N, i+1, j+1); //diagonais
		abre_vazio(matriz, N, i-1, j-1);
		abre_vazio(matriz, N, i+1, j-1);
		abre_vazio(matriz, N, i-1, j+1);

	}

	
}

void converte_exibe(Minas** matriz, int N, int i, int j){
			matriz[i][j].aberta = true;

			if(matriz[i][j].bombas_redor == 0)
				matriz[i][j].exibe = 'o';
			else if(matriz[i][j].bombas_redor == 1)
				matriz[i][j].exibe = '1';
			else if(matriz[i][j].bombas_redor == 2)
				matriz[i][j].exibe = '2';
			else if(matriz[i][j].bombas_redor == 3)
				matriz[i][j].exibe = '3';
			else if(matriz[i][j].bombas_redor == 4)
				matriz[i][j].exibe = '4';
			else if(matriz[i][j].bombas_redor == 5)	
				matriz[i][j].exibe = '5';
			else if(matriz[i][j].bombas_redor == 6)
				matriz[i][j].exibe = '6';
			else if(matriz[i][j].bombas_redor == 7)
				matriz[i][j].exibe = '7';
			else if(matriz[i][j].bombas_redor == 8)
				matriz[i][j].exibe = '8';
}

void imprime_matriz(Minas** matriz, int N){
	cout << "\n\t**** CAMPO MINADO ****" << endl;
	cout << "- = Fechada, o = Aberta, * = Bomba, ? = Bandeira" << endl;

	cout << "\t";
	for(auto i = 0; i < N; i++){ //tabulacao
		if(i < 10) //tabulacao para matrizes com + de 10 linhas
			cout << i << "  ";
		else
			cout << i << " ";
	}
	cout << "\n\t";
	for(auto i = 0; i < N; i++)
		cout << "---";

	cout << endl;
	for(auto i = 0; i < N; i++){
		if (i < 10)
			cout << "   " << i << " || ";
		else
			cout << "  " << i << " || ";
		for(auto j = 0; j < N; j++){
			cout << matriz[i][j].exibe << "  ";
		}
		cout << "|| " << i << endl;
	}

	cout <<"\t";
	for(auto i = 0; i < N; i++) //tabulacao 
		cout << "---";
	cout << "\n\t";
	for(auto i = 0; i < N; i++){
		if(i < 10)
			cout << i << "  ";
		else
			cout << i << " ";
	}	

	cout << "\n" << endl;

}

bool verifica_ganhou(Minas** matriz, int N){
	bool ganhou = true;

	for(auto i = 0; i < N; i++){
		for(auto j = 0; j < N; j++){ 
			if(!matriz[i][j].aberta && !matriz[i][j].bomba){
				ganhou = false;
				return ganhou;
			}
		}
	}

	return ganhou;
}

void destroi_matriz(Minas** matriz, int N){
	for(auto i = 0; i < N; i++)
    	delete[] matriz[i];
    delete[] matriz;
}