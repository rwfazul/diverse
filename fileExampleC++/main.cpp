/* 
 * File: main.cpp
 * Author: Rhauani Fazul
 *
 */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;


//Estruturas
struct Aluno{
    int matricula;
    string nome;
};

struct Notas{
    int matricula;
    float nota1, nota2;
};


//Protótipos
vector<Aluno> preenche_nomes();
vector<Notas> preenche_notas();
bool procura_nome(vector<Aluno>& alunos, vector<Notas>& notas, string busca); 
void imprime_resultados(vector<Aluno>& alunos, vector<Notas>& notas, int mat_buscada);


int main(int argc, char **argv){
    string busca;
 
    for(auto i = 1; i < argc; i++){  //para funcionar com nomes completos
    	if (i > 1)
    		busca = busca + " ";
    	busca = busca + argv[i];
    }

    vector<Aluno> alunos = preenche_nomes();
    vector<Notas> notas = preenche_notas();

    bool achou = procura_nome(alunos, notas, busca);
    
    if(!achou)
        cout << "Nome nao encontrado" << endl;

    return 0;
}

vector<Aluno> preenche_nomes(){
	vector<Aluno> alunos;
    int matricula;
    string nome;
    
    ifstream insere{"alunos.txt"};
    
    if(!insere.is_open())
        throw runtime_error{"ERRO na leitura do arquivo alunos.txt"};
        
    while(insere >> matricula){
        getline(insere, nome);
        alunos.push_back( Aluno{matricula, nome} );
    }
  
    insere.close();  
 
    return alunos;
}

vector<Notas> preenche_notas(){
    int matricula;
    float nota1, nota2;
    vector<Notas> notas;

    ifstream insere{"notas.txt"};
   
    if(!insere.is_open())
       throw runtime_error{"ERRO na leitura do arquivo alunos.txt"};
        
    while(insere >> matricula){
        insere >> nota1 >> nota2;
        notas.push_back( Notas{matricula, nota1, nota2});
    }
      
    insere.close();

    return notas;
}

bool procura_nome(vector<Aluno>& alunos, vector<Notas>& notas, string busca){ 
	// Passagem por referencia (&) usada para evitar copia do vetor (sendo q funcao nao altera valores)
    int i, j, mat_buscada;
    int tam_nome, tam_busca = busca.size(); 
    bool achou = false;
    
    for(Aluno& v: alunos){
        tam_nome = v.nome.size();
        
        for(i = 0, j = 0; i < tam_nome; i++){ //verifica se busca esta contida no nome 
            if(busca[j] == v.nome[i]){    
                j++;
                if(tam_busca == j){
                    mat_buscada = v.matricula;
                    imprime_resultados(alunos, notas, mat_buscada); //envia matricula correspondente ao nome encontrado
                    achou = true;
                    break;
                }
            }else{
                j = 0;  
            }
        } 
    }
    
    return achou;
}

void imprime_resultados(vector<Aluno>& alunos, vector<Notas>& notas, int mat_buscada){
    float  media;

    for(Notas& v: notas){
        if(mat_buscada == v.matricula){
            media = (v.nota1 + v.nota2) / 2;
            cout << media << "  ";
        }           
    }
       
    for(Aluno& v: alunos){
        if(mat_buscada == v.matricula ){
            cout << v.nome << endl;
        }       
    }
}