#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_NOME 30
#define TAM_COR 10
#define QUANT_TERR 5

struct Territorio
{
    char nome[TAM_NOME];
    char cor[TAM_COR];
    int tropas;
};

void limparBuffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
    {
    }
}

int main()
{

    struct Territorio terras[QUANT_TERR];

    printf("\n\n=========================================================\n\n");
    printf("Vamos cadastrar os %d Territorios iniciais do nosso mundo.\n", QUANT_TERR);

    for (int i = 0; i < QUANT_TERR; i++)
    {
        printf("\n--- Cadastrando Territorio %d ---\n\n", i + 1);
        printf("Nome do Territorio: ");
        fgets(terras[i].nome, TAM_NOME, stdin);
        printf("Cor do Exercito (Ex: Azul, Verde, Vermelho...): ");
        fgets(terras[i].cor, TAM_COR, stdin);

        terras[i].nome[strcspn(terras[i].nome, "\n")] = '\0';
        terras[i].cor[strcspn(terras[i].cor, "\n")] = '\0';

        printf("Quantida de Tropas: ");
        scanf("%d", &terras[i].tropas);
        limparBuffer();
    }

    printf("\n\nCadastro concluido com sucesso!\n\n");
    printf("========================================\n      Mapa do Mundo - Estado Atual\n========================================\n\n");
    for (int i = 0; i < QUANT_TERR; i++)
    {
        printf("TERRITORIO %d:\n", i + 1);
        printf("  -Nome: %s\n", terras[i].nome);
        printf("  -Dominado por: Exercito %s\n", terras[i].cor);
        printf("  -Tropas: %d\n", terras[i].tropas);
    }
}
