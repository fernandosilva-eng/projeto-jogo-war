#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "operacoes.h"

void atacar(Territorios *atacante, Territorios *defensor)
{
    srand(time(NULL));
    int min=1, max=6;

    int ata = rand() % (max - min + 1) + min;
    int def = rand() % (max - min + 1) + min;
    

    printf("\n--- RESULTADO DA BATALHA ---\n");
    printf("O atacante %s rolou o dado e tirou: %d\n", (*atacante).nome, ata);
    printf("O defensor %s rolou o dado e tirou: %d\n", (*defensor).nome, def);


    if(ata>def){
        (*atacante).tropas+=1;
        (*defensor).tropas-=1;
        printf("VITORIA DO ATAQUE! O defensor perdeu uma tropa.\n");
        if((*defensor).tropas==0){
            strcpy((*defensor).cor, (*atacante).cor);
            printf("CONQUISTA! O territorio %s foi dominado pelo Exercito %s!\n", (*defensor).nome, (*atacante).cor);
        }
    }
    else if(def>ata){
        (*defensor).tropas+=1;
        (*atacante).tropas-=1;
        printf("VITORIA DA DEFESA! O Atacante perdeu uma tropa.\n");
        if((*atacante).tropas==0){
            strcpy((*atacante).cor, (*defensor).cor);
            printf("CONQUISTA! O territorio %s foi dominado pelo Exercito %s!\n", (*atacante).nome, (*defensor).cor);
        }
    }
    else{printf("EMPATE!\n");}


    limparBuffer();
    printf("Precione ENTER para continuar para o proximo turno... ");
    getchar();
}

