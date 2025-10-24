#ifndef OPERACOES_H
#define OPERACOES_H


#define MAX_NOME 30
#define MAX_COR 10


typedef  struct
{
    char nome[MAX_NOME];
    char cor[MAX_COR];
    int tropas;
} Territorios;



void limparBuffer();

void mapaAtual(Territorios **vTerritorios, int *totalTerritorio);

int cadastrar(Territorios **vterritorio, int *totalTerritorio);

void atacar(Territorios *atacante, Territorios *defensor);

#endif


