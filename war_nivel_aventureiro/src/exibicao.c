#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "operacoes.h"


void limparBuffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF){}
}


void mapaAtual(Territorios **vTerritorios, int *totalTerritorio)
{
    printf("\n========================================\n      MAPA DO MUNDO - ESTADO ATUAL\n========================================\n\n");
    
    int tam=*totalTerritorio;
    for(int i=0; i<tam; i++){
        printf("%d. %s (Exercito %s, Tropas: %d)\n", i+1, (*vTerritorios)[i].nome, (*vTerritorios)[i].cor, (*vTerritorios)[i].tropas);
    }
}