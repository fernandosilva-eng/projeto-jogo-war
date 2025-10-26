//Codigo principal

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/operacoes.h"

int main()
{
    Territorios *vetorTerritorios;
    int totalTerritorios;

    printf("========================================\n   WAR ESTRUTURADO - CADASTRO INICIAL\n========================================\n");

    cadastrar(&vetorTerritorios, &totalTerritorios);

    mapaAtual(&vetorTerritorios, &totalTerritorios);
    

    int encerra_loop=0;

    //Loop principal do jogo
    while(1)
    {
        //Essa variavel guarda quantos territorios ainda tem tropas. Se ela for igual a 1 o jogo finaliza sozinho.
        int c=0;

        char vencedor[MAX_NOME];
        
        for (int i = 0; i < totalTerritorios; i++)
        { // Verifica se os territorios possuem tropas para batalha, se apenas um possuir, o jogo finaliza.
            if (vetorTerritorios[i].tropas > 0) {c++; strcpy(vencedor, vetorTerritorios[i].nome);}
            
            if (totalTerritorios - 1 == i && c == 1)
            {
                printf("%s conquistou todos os outros territorio...\nO jogo acabou!", vencedor);
                encerra_loop = 1;
            }
        }

        if(encerra_loop==1) {break;}

        printf("\n--- FASE DE ATAQUE ---\n");
    
        int atacante;
        printf("Escolha o territorio atacante( 1 a %d, ou 0 para sair): ", totalTerritorios);
        scanf("%d", &atacante);
        limparBuffer();

        if(atacante==0) {break;}

        int defensor;
        printf("Escolha o territorio defensor (1 a %d): ", totalTerritorios);
        scanf("%d", &defensor);

        //Verifica se o territorio ainda ta no jogo
        if(vetorTerritorios[atacante-1].tropas==0)
        {
            printf("%s foi eliminado! Escolha outro...\n", vetorTerritorios[atacante-1].nome);
        }
        else if(vetorTerritorios[defensor-1].tropas==0)
        {
            printf("%s foi eliminado! escolha outro...\n", vetorTerritorios[defensor-1].nome);
        }
        else
        {
            atacar(&vetorTerritorios[atacante-1], &vetorTerritorios[defensor-1]);
            mapaAtual(&vetorTerritorios, &totalTerritorios);
        }
    }
    //Liberando memoria
    free(vetorTerritorios);
}