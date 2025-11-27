// Codigo principal

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NOME 30
#define MAX_COR 10

typedef struct
{
    char nome[MAX_NOME];
    char cor[MAX_COR];
    int tropas;
} Territorios;

void limparBuffer();
void mapaAtual(Territorios **vTerritorios, int *totalTerritorio);
void atacar(Territorios *atacante, Territorios *defensor);
int cadastrar(Territorios **vterritorio, int *totalTerritorio);

int main()
{
    Territorios *vetorTerritorios;
    int totalTerritorios;

    printf("========================================\n   WAR ESTRUTURADO - CADASTRO INICIAL\n========================================\n");

    cadastrar(&vetorTerritorios, &totalTerritorios);

    mapaAtual(&vetorTerritorios, &totalTerritorios);

    int encerra_loop = 0;

    // Loop principal do jogo
    while (1)
    {
        // Essa variavel guarda quantos territorios ainda tem tropas. Se ela for igual a 1 o jogo finaliza sozinho.
        int c = 0;

        char vencedor[MAX_NOME];

        for (int i = 0; i < totalTerritorios; i++)
        { // Verifica se os territorios possuem tropas para batalha, se apenas um possuir, o jogo finaliza.
            if (vetorTerritorios[i].tropas > 0)
            {
                c++;
                strcpy(vencedor, vetorTerritorios[i].nome);
            }

            if (totalTerritorios - 1 == i && c == 1)
            {
                printf("%s conquistou todos os outros territorio...\nO jogo acabou!", vencedor);
                encerra_loop = 1;
            }
        }

        if (encerra_loop == 1)
        {
            break;
        }

        printf("\n--- FASE DE ATAQUE ---\n");

        int atacante;
        printf("Escolha o territorio atacante( 1 a %d, ou 0 para sair): ", totalTerritorios);
        scanf("%d", &atacante);
        limparBuffer();

        if (atacante == 0)
        {
            break;
        }

        int defensor;
        printf("Escolha o territorio defensor (1 a %d): ", totalTerritorios);
        scanf("%d", &defensor);

        // Verifica se o territorio ainda ta no jogo
        if (vetorTerritorios[atacante - 1].tropas == 0)
        {
            printf("%s foi eliminado! Escolha outro...\n", vetorTerritorios[atacante - 1].nome);
        }
        else if (vetorTerritorios[defensor - 1].tropas == 0)
        {
            printf("%s foi eliminado! escolha outro...\n", vetorTerritorios[defensor - 1].nome);
        }
        else
        {
            atacar(&vetorTerritorios[atacante - 1], &vetorTerritorios[defensor - 1]);
            mapaAtual(&vetorTerritorios, &totalTerritorios);
        }
    }
    // Liberando memoria
    free(vetorTerritorios);
}

// Limpa a entrada padrao
void limparBuffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
    {
    }
}

// Exibe o mapa atual
void mapaAtual(Territorios **vTerritorios, int *totalTerritorio)
{
    printf("\n===========================================\n      MAPA DO MUNDO - ESTADO ATUAL\n===========================================\n\n");

    int tam = *totalTerritorio;
    for (int i = 0; i < tam; i++)
    { // Verifica se o territorio foi eliminado
        if ((*vTerritorios)[i].tropas > 0)
        {
            printf("%d. %-10s (Exercito %-12sTropas: %d)\n", i + 1, (*vTerritorios)[i].nome, (*vTerritorios)[i].cor, (*vTerritorios)[i].tropas);
        }
        else
        {
            printf("%d. %-10s (TERRITORIO ELIMINADO)\n", i + 1, (*vTerritorios)[i].nome);
        }
    }
    printf("\n==============================================\n");
}

int cadastrar(Territorios **vterritorio, int *totalTerritorio)
{ // Entrada de dados
    printf("Vamos cadastrar quantos territorios? ");
    int quantidadeTerritorios;
    scanf("%d", &quantidadeTerritorios);
    limparBuffer();
    // Alocacao de memoria
    *vterritorio = (Territorios *)calloc(quantidadeTerritorios, sizeof(Territorios));
    if (*vterritorio == NULL)
    {
        printf("Falha em "
               "Cadastrar"
               ". Alocacao falhou!\n");
        return 1;
    }
    // Entrada de dados; Prenche as struct
    for (int i = 0; i < quantidadeTerritorios; i++)
    {
        printf("\n--- Cadastrando Territorio %d ---\n", i + 1);
        printf("Nome do Territorio: ");
        scanf(" %49[^\n]", (*vterritorio)[i].nome);
        limparBuffer();
        printf("Cor do Exercito (Ex: Azul, Verde, Vermelho...): ");
        scanf(" %49[^\n]", (*vterritorio)[i].cor);
        limparBuffer();

        printf("Quantas Tropas ");
        scanf("%d", &(*vterritorio)[i].tropas);
        limparBuffer();
    }
    // Contabiliza os territoios
    *totalTerritorio = quantidadeTerritorios;
    printf("Foram cadastrados %d Territorios\n", quantidadeTerritorios);
    return 0;
}

void atacar(Territorios *atacante, Territorios *defensor)
{
    // Sorteia os numeros
    srand(time(NULL));
    int min = 1, max = 6;

    int ata = rand() % (max - min + 1) + min;
    int def = rand() % (max - min + 1) + min;

    printf("\n--- RESULTADO DA BATALHA ---\n");
    printf("O atacante %s rolou o dado e tirou: %d\n", (*atacante).nome, ata);
    printf("O defensor %s rolou o dado e tirou: %d\n", (*defensor).nome, def);

    // Verifica quem ganhou ou se deu empate
    if (ata > def)
    {
        (*atacante).tropas += 1;
        (*defensor).tropas -= 1;
        printf("VITORIA DO ATAQUE! O defensor perdeu uma tropa.\n");
        if ((*defensor).tropas == 0)
        {
            strcpy((*defensor).cor, (*atacante).cor);
            printf("CONQUISTA! O territorio %s foi dominado pelo Exercito %s!\n", (*defensor).nome, (*atacante).cor);
        }
    }
    else if (def > ata)
    {
        (*defensor).tropas += 1;
        (*atacante).tropas -= 1;
        printf("VITORIA DA DEFESA! O Atacante perdeu uma tropa.\n");
        if ((*atacante).tropas == 0)
        {
            strcpy((*atacante).cor, (*defensor).cor);
            printf("CONQUISTA! O territorio %s foi dominado pelo Exercito %s!\n", (*atacante).nome, (*defensor).cor);
        }
    }
    else
    {
        printf("EMPATE!\n");
    }

    // Pausa
    limparBuffer();
    printf("Precione ENTER para continuar para o proximo turno... ");
    getchar();
}