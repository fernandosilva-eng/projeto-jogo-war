// Esse código cuida de operações refentes ao cadastro

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/operacoes.h"



int cadastrar(Territorios **vterritorio, int *totalTerritorio)
{   //Entrada de dados
    printf("Vamos cadastrar quantos territorios? ");
    int quantidadeTerritorios;
    scanf("%d", &quantidadeTerritorios);
    limparBuffer();
    //Alocacao de memoria
    *vterritorio = (Territorios *) calloc(quantidadeTerritorios, sizeof(Territorios));
    if(*vterritorio == NULL)
    {
        printf("Falha em ""Cadastrar"". Alocacao falhou!\n");
        return 1;
    }
    //Entrada de dados; Prenche as struct
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
    //Contabiliza os territoios
    *totalTerritorio = quantidadeTerritorios;
    printf("Foram cadastrados %d Territorios\n", quantidadeTerritorios);
    return 0;
}






