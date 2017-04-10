#include <stdio.h>
#include <stdlib.h>
#include <time.h> //random

int main(){
    int jogUm, jogDois; //pontos dos jogadores
    int branco, vermelho; //dados
    int rodada;  // p/ exibir a rodada (1, 2 ou 3)
    char jogada, invalida, novamente; // 'Joga ou Passa', consistencia das opcoes, jogar novamente

    srand( (unsigned)time(NULL) ); //random

    do{
        jogUm=0, jogDois=0;
        rodada=1;
        printf("\t\tINICIO\n\t  Player 1: %d pontos\n\t  Player 2: %d pontos", jogUm, jogDois);
        for(rodada=1; rodada<=3; rodada++){
            do{
                invalida=0; //reset na segunda volta (se usario digitar op. invalida)
                printf("\n\nPlayer 1: Joga ('J') ou Passa ('P') ?   ");
                scanf(" %c", &jogada);
                switch(jogada){
                case 'J':
                case 'j':
                    branco=1+rand()%6;
                    jogUm=jogUm+branco;
                    vermelho=1+rand()%6;
                    if (vermelho==6)
                        jogUm=jogUm+(vermelho*2);
                    else
                        jogUm=jogUm+vermelho;
                    printf("\n  Dado branco: %d\tDado vermelho: %d", branco, vermelho); //exibe resultados de cada rodada de dados
                    break;
                case 'P':
                case 'p':
                    break;
                default:
                    printf("Opcao invalida. Jogue novamente.");
                    invalida=1;
                } //fim switch jogador 1
            }while(invalida==1); // ate usuario digitar op. valida

            do{
                invalida=0;
                printf("\n\nPlayer 2: Joga ('J') ou Passa ('P') ?   ");
                scanf(" %c", &jogada);
                switch(jogada){
                case 'J':
                case 'j':
                    branco=1+rand()%6;
                    jogDois=jogDois+branco;
                    vermelho=1+rand()%6;
                    if (vermelho==6)
                        jogDois=jogDois+(vermelho*2);
                    else
                        jogDois=jogDois+vermelho;
                    printf("\n  Dado branco: %d\tDado vermelho: %d\n\n", branco, vermelho);
                    break;
                case 'P':
                case 'p':
                    break;
                default:
                    printf("Opcao invalida. Jogue novamente.");
                    invalida=1;
                }//fim switch jogador 2
            }while(invalida==1);

            printf("\t\tRodada %d\n\t  Player 1: %d pontos\n\t  Player 2: %d pontos", rodada, jogUm, jogDois);//menu rodada
        } //fim 'for' das rodadas

        /*Verificação do ganhador*/
        if(jogUm<=21 && jogDois<=21){
            if (jogUm==jogDois)
                printf("\n\n\t  RESULTADO: EMPATE!");
            if (jogUm>jogDois)
                printf("\n\n\tRESULTADO: PLAYER 1 VENCEU!");
            else
                printf("\n\n\tRESULTADO: PLAYER 2 VENCEU!");
        }
        if (jogUm>21 && jogDois>21)
            printf("\n\n\t   RESULTADO: EMPATE!");
        if (jogUm>21 && jogDois<=21)
            printf("\n\n\tRESULTADO: PLAYER 2 VENCEU!");
        if (jogDois>21 && jogUm<=21)
            printf("\n\n\tRESULTADO: PLAYER 1 VENCEU!");

        do{
            invalida=0;
            printf("\n\n\nDESEJA JOGAR NOVAMENTE: SIM 'S' ou NAO 'N' ?     ");
            scanf(" %c", &novamente);
            printf("\n\n");
            switch(novamente){  //jogar novamente
            case 'S':
            case 's':
                novamente=1;
                break;
            case 'N':
            case 'n':
                novamente=0;
                break;
            default:
                printf("Opcao invalida.");
                invalida=1;
            }
        }while(invalida==1); // ate usario digitar op. valida (S ou N)

    }while(novamente==1); // ate usario digitar sim (jogar novamente)

    return 0;
}
