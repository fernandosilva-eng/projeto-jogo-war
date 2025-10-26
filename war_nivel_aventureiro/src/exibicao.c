// Esse codico cuida da exibicao 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/operacoes.h"

//Limpa a entrada padrao
void limparBuffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF){}
}

//Exibe o mapa atual
void mapaAtual(Territorios **vTerritorios, int *totalTerritorio)
{
    printf("\n===========================================\n      MAPA DO MUNDO - ESTADO ATUAL\n===========================================\n\n");
    
    int tam=*totalTerritorio;
    for(int i=0; i<tam; i++)
    {   //Verifica se o territorio foi eliminado
        if((*vTerritorios)[i].tropas>0)
        {
            printf("%d. %-10s (Exercito %-12sTropas: %d)\n", i+1, (*vTerritorios)[i].nome, (*vTerritorios)[i].cor, (*vTerritorios)[i].tropas);
        } else
        {
            printf("%d. %-10s (TERRITORIO ELIMINADO)\n", i+1, (*vTerritorios)[i].nome);
        }
    }
    printf("\n==============================================\n");
}