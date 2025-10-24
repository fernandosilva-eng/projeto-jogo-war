// Esse código cuida de operações refentes ao cadastro

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "operacoes.h"



int cadastrar(Territorios **vterritorio, int *totalTerritorio)
{
    printf("Vamos cadastrar quantos territorios? ");
    int quantidadeTerritorios;
    scanf("%d", &quantidadeTerritorios);
    limparBuffer();

    *vterritorio = (Territorios *) calloc(quantidadeTerritorios, sizeof(Territorios));
    if(*vterritorio == NULL)
    {
        printf("Falha em ""Cadastrar"". Alocacao falhou!\n");
        return 1;
    }

    for(int i=0; i<quantidadeTerritorios; i++){
        printf("\n--- Cadastrando Territorio %d ---\n", i + 1);
        printf("Nome do Territorio: ");
        scanf(" %49[^\n]",(*vterritorio)[i].nome);
        limparBuffer();
        printf("Cor do Exercito (Ex: Azul, Verde, Vermelho...): ");
        scanf(" %49[^\n]",(*vterritorio)[i].cor);
        limparBuffer();


        printf("Quantas Tropas ");
        scanf("%d", &(*vterritorio)[i].tropas);
        limparBuffer();
    }   

    *totalTerritorio = quantidadeTerritorios;
    printf("Foram cadastrados %d Territorios\n", quantidadeTerritorios);
    return 0;
}






