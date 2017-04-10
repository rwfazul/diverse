#include <stdio.h>
#include <stdlib.h>
#include <time.h> //random

int main(){
    int jogUm, comp; //pontos dos jogadores
    int branco, vermelho, comeca; //dados, quem começa jogando
    int rodada, computador_jog;;  // p/ exibir a rodada (1, 2 ou 3)); jogada do computador
    char jogada, invalida, novamente; // 'Joga ou Passa'; consistencia das opcoes; jogar novamente

    srand( (unsigned)time(NULL) ); //random valor dado e jogada computador

    do{
        jogUm=0, comp=0;
        rodada=1;

        printf("\t\tINICIO\n\t  Player 1: %d pontos\n\t  Computador: %d pontos", jogUm, comp);
        for(rodada=1; rodada<=3; rodada++){
                /*Jogador*/
            do{
                player:
                invalida=0; //reset na segunda volta (se usario digitar op. invalida)
                printf("\n\nDeseja Jogar ('J') ou Passar ('P') ?   ");
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
                      printf("  Dado branco: %d\tDado vermelho: %d", branco, vermelho); //exibe resultados de cada rodada de dados
                      break;
                  case 'P':
                  case 'p':
                      break;
                  default:
                      printf("Opcao invalida. Jogue novamente.");
                      invalida=1;
                } //fim switch jogador
            }while(invalida==1); // ate usuario digitar op. valida

                 /*Computador*/

             //random jogada do computador (0 ou 1)
                computador_jog=rand()%2;
                if(computador_jog)
                    jogada='j';
                else
                    jogada='p';

             //condições para melhorar as jogadas aleatorias

             if (jogUm>21 || comp==21)
                 jogada='p';

             else if (comp<12)
                 jogada='j';

             if (jogUm==21 && comp<21)
                 jogada='j';

             if(jogUm>comp && jogUm<=21){
                 if (rodada==3)
                   jogada='j';
             }
             if(comp>=jogUm && comp>15){
                 if(rodada<3)
                    jogada='p';
             }

                switch(jogada){
                  case 'j':
                      printf("\n\n  COMPUTADOR JOGA OS DADOS:");
                      branco=1+rand()%6;
                      comp=comp+branco;
                      vermelho=1+rand()%6;
                      if (vermelho==6)
                          comp=comp+(vermelho*2);
                      else
                          comp=comp+vermelho;
                      printf("\n  Dado branco: %d\tDado vermelho: %d\n\n", branco, vermelho);
                      break;
                  case 'p':
                      printf("\n\n  COMPUTADOR PASSA A VEZ.\n\n");
                      break;
                }
                    //fim pc

            printf("\t\tRodada %d\n\t  Player 1: %d pontos\n\t  Computador: %d pontos", rodada, jogUm, comp);//menu rodada

        } //fim 'for' das rodadas

        /*Verificação do ganhador*/
        if(jogUm<=21 && comp<=21){
            if (jogUm==comp)
                printf("\n\n\t  RESULTADO: EMPATE!");
            if (jogUm>comp)
                printf("\n\n\tRESULTADO: VOCE VENCEU!");
            else
                printf("\n\n\tRESULTADO: COMPUTADOR VENCEU!");
        }
        if (jogUm>21 && comp>21)
            printf("\n\n\t   RESULTADO: EMPATE!");
        if (jogUm>21 && comp<=21)
            printf("\n\n\tRESULTADO: COMPUTADOR VENCEU!");
        if (comp>21 && jogUm<=21)
            printf("\n\n\tRESULTADO: VOCE VENCEU!");

       /*Jogar novamente*/
        do{
            invalida=0;
            printf("\n\n\nDESEJA JOGAR NOVAMENTE: SIM 'S' ou NAO 'N' ?     ");
            scanf(" %c", &novamente);
            printf("\n\n");
            switch(novamente){
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
        }while(invalida==1); // ate usario digitar op. valida

    }while(novamente==1); // ate usario digitar sim (jogar novamente)

    return 0;
}
