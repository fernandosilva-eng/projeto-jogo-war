#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "operacoes.h"

int main(){

    Territorios *vetorTerritorios;
    int totalTerritorios;

    printf("========================================\n   WAR ESTRUTURADO - CADASTRO INICIAL\n========================================\n");

    cadastrar(&vetorTerritorios, &totalTerritorios);

    mapaAtual(&vetorTerritorios, &totalTerritorios);
    
    limparBuffer();

    while(1)
    {
        printf("\n--- FASE DE ATAQUE ---\n");
    
        int atacante;
        printf("Escolha o territorio atacante( 1 a %d, ou 0 para sair): ", totalTerritorios);
        scanf("%d", &atacante);
        limparBuffer();

        if(atacante==0){break;}

        int defensor;
        printf("Escolha o territorio defensor (1 a %d): ", totalTerritorios);
        scanf("%d", &defensor);

        atacar(&vetorTerritorios[atacante-1], &vetorTerritorios[defensor-1]);

        mapaAtual(&vetorTerritorios, &totalTerritorios);
    }
    
    free(vetorTerritorios);
}