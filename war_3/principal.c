// Sistema que simula o Jogo War

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>
#include <time.h>
#define MAX_NOME 30
#define MAX_COR 10

typedef struct
{
    char jogador[MAX_COR];
    int numero_missao;
    int tropasBatalha; // guarda o resultado das tropas da última batalha. Ex: perdeu 3 tropas então guarda -3
    int pontuacaoMissao;   // guarda a quantidade de Global_Jogador.tropasBatalha do jogador.
} Jogador;

Jogador Global_Jogador; // Armazena os dados do jogador.

typedef struct
{
    char nome[MAX_NOME];
    char cor[MAX_COR];
    int tropas;
} Territorios;

// --------------------------------------------------------------------------------------- Declaração das funções que serão usadas

void limparBuffer();
void mapaAtual(Territorios **vTerritorios, int *totalTerritorio);
void atacar(Territorios *atacante, Territorios *defensor);
void sortearMissao(char *missaoJogador, char missoes[][40], int totalMissoes);
void sortearJogador(int totalTerritorios, Territorios *mapa);
void liberarMemoria(char *texto, Territorios *mapa);
int  verificarMissao(char *missao, Territorios *mapa, int tamanho);
int  cadastrar(Territorios **vterritorio, int *totalTerritorio);

// --------------------------------------------------------------------------------------- Programa Principal

int main()
{
    Global_Jogador.numero_missao=-1;
    Global_Jogador.pontuacaoMissao=0;
    Territorios *mapa;    // Mapa principal
    int totalTerritorios; // Armazenará a quatidade de territórios cadastrados

    int quantidade_missoes = 5;
    // Definindo as missões
    char vetorMissoes[quantidade_missoes][40];
    strcpy(vetorMissoes[0], "Vencer 2 Batalhas seguidas");
    strcpy(vetorMissoes[1], "Eliminar TODOS os territorios");
    strcpy(vetorMissoes[2], "Conquistar 1 territorio");
    strcpy(vetorMissoes[3], "Invicto, Tres batalhas sem perder");
    strcpy(vetorMissoes[4], "Ganhar 3 Tropas");
      
    // Jogo começa aqui
    // Exibição inicial
    printf("\n\n==================================================\n      WAR ESTRUTURADO - CADASTRO INICIAL\n==================================================\n\n");
    cadastrar(&mapa, &totalTerritorios); // Cadastrando os territórios do jogo
    mapaAtual(&mapa, &totalTerritorios); // Exibindo todos os territórios
    sortearJogador(totalTerritorios, mapa); // sorteando qual sera a cor do exercito do jogador
    // Mostra qual sera a missao e o territorio que cumprirar a missao
    char *missao_jogador = (char *)malloc(200 * sizeof(char)); // Alocando memória para a string missão
    sortearMissao(missao_jogador, vetorMissoes, quantidade_missoes);            // Sorteando a missao
    // Loop principal do jogo começa aqui
    int encerra_loop = 0;
    while (1)
    {
        // Essa variavel guarda quantos territorios ainda tem tropas. Se ela for igual a 1 o jogo finaliza sozinho.
        int c = 0;
        char vencedor[MAX_NOME];
        // Verifica se os territorios possuem tropas para batalha, se apenas um possuir, o jogo finaliza.
        for (int i = 0; i < totalTerritorios; i++)
        {
            if (mapa[i].tropas > 0)
            {
                c++;
                strcpy(vencedor, mapa[i].nome);
            }
            if (totalTerritorios - 1 == i && c == 1)
            {
                if (verificarMissao(missao_jogador, mapa, totalTerritorios) == 1)
                {
                    printf("\n           VOCE CUMPRIU SUA MISSAO!\n--------------------------------------------------\n%-9s %+40s \n%-9s %+40s\n", "Missao:", missao_jogador, "Jogador:", Global_Jogador.jogador);
                    printf("%-9s %+40s\n--------------------------------------------------\n\n", "Situacao:", "Missao cumprida");
                }
                else
                {
                    printf("\n          SUA MISSAO NÃO FOI CUMPRIDA!\n--------------------------------------------------\n%-9s %+40s \n%-9s %+40s\n", "Missao:", missao_jogador, "Jogador:", Global_Jogador.jogador);
                    printf("%-9s %+40s\n--------------------------------------------------\n\n", "Situacao:", "Missao não cumprida");
                }
                printf("%s conquistou todos os outros territorios...\n\nO jogo acabou!", vencedor);
                encerra_loop = 1;
            }
        }

        if (encerra_loop == 1)
        {
            break;
        }

        if (verificarMissao(missao_jogador, mapa, totalTerritorios) == 1)
        {
            printf("\n           VOCE CUMPRIU SUA MISSAO!\n--------------------------------------------------\n%-9s %+40s \n%-9s %+40s\n", "Missao:", missao_jogador, "Jogador:", Global_Jogador.jogador);
            printf("%-9s %+40s\n--------------------------------------------------\n\n", "Situacao:", "Missao cumprida");
            printf("Sua missao foi cumprida. Qual sera seu proximo passo?\n\n1 - Receber uma nova missao\n0 - Encerrar o Jogo \n\nDigite sua uma das opcoes -> ");
            int opcao;
            scanf("%d", &opcao);
            limparBuffer();
            if (opcao == 1)
            {
                sortearMissao(missao_jogador, vetorMissoes, quantidade_missoes);
                printf("\n\n>>>>> Uma nova missao esta disponivel.\n\n");
                Global_Jogador.pontuacaoMissao = 0;
            }
            else if (opcao == 0)
            {
                encerra_loop = 1;
            }
        }

        if (encerra_loop == 1)
        {
            break;
        }

        printf("--- Sua missao (%s) ---\n\n%s ", Global_Jogador.jogador, missao_jogador);
        int acao = -1;
        printf("\n\n--- MENU DE ACOES --- \n\n1 - Atacar\n2 - Verificar missao\n0 - Sair\n\nDigite sua acao -> ");
        scanf("%d", &acao);
        limparBuffer();

        switch (acao)
        {
        // Siatuação 1
        case 1:
            // Iniciando fase de ataque
            printf("\n--- FASE DE ATAQUE ---\n\n");

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

            // Validando os territorios que o usuário escolheu para o ataque
            if (mapa[atacante - 1].tropas == 0)
            {
                printf("\n>>>>> %s foi eliminado! Escolha outro...\n\n", mapa[atacante - 1].nome);
            }
            else if (mapa[defensor - 1].tropas == 0)
            {
                printf("\n>>>>> %s foi eliminado! escolha outro...\n\n", mapa[defensor - 1].nome);
            }
            else if(strcmp(mapa[atacante-1].nome, mapa[defensor-1].nome)==0)
            {
                printf("\n>>>>> Nao e possivel atacar o proprio territorio! Escolha territorios diferentes! \n\n");
            }
            else
            {
                atacar(&mapa[atacante - 1], &mapa[defensor - 1]);
                mapaAtual(&mapa, &totalTerritorios);
            }
            break;
        // Situação 2
        case 2:
            printf("\n              DETALHES DA MISSAO\n--------------------------------------------------\n%-9s %+40s \n%-9s %+40s\n", "Missao:", missao_jogador, "Jogador:", Global_Jogador.jogador);
            if (verificarMissao(missao_jogador, mapa, totalTerritorios) == 1)
            {
                printf("%-9s %+40s\n--------------------------------------------------\n\n", "Situacao:", "Missao cumprida");
            }
            else
            {
                printf("%-9s %+40s\n--------------------------------------------------\n\n", "Situacao:", "Missao inconpleta");
            }

            mapaAtual(&mapa, &totalTerritorios);

            break;

        case 0:
            encerra_loop = 1;
            break;

        default:
            break;
        }

    }
    // Liberando memoria
    printf("\n\nEcerrando");
    for(int i=0; i<3;i++)
    {
        printf(".");
        Sleep(800);
    }
    liberarMemoria(missao_jogador, mapa);
}

// --------------------------------------------------------------------------------------- Limpa a entrada padrao

void limparBuffer()
{
    int c;
    while ((c = getchar()) != '\n' && c != EOF)
    {
    }

}

// --------------------------------------------------------------------------------------- Cadastra os territorios no mapa

int cadastrar(Territorios **vterritorio, int *totalTerritorio)
{ // Entrada de dados
    //printf("Vamos cadastrar quantos territorios? ");
    int quantidadeTerritorios=3;
    //scanf("%d", &quantidadeTerritorios);
    //limparBuffer();
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
    /*
    for (int i = 0; i < quantidadeTerritorios; i++)
    {
        printf("\n--- Cadastrando Territorio %d ---\n\n", i + 1);
        printf("Nome do Territorio: ");
        scanf(" %49[^\n]", (*vterritorio)[i].nome);
        limparBuffer();
        printf("Cor do Exercito (Ex: Azul, Verde, Vermelho...): ");
        scanf(" %49[^\n]", (*vterritorio)[i].cor);
        limparBuffer();

        printf("Quantas Tropas ");
        scanf("%d", &(*vterritorio)[i].tropas);
        limparBuffer();
    }*/
    // Contabiliza os territoios



// Apenas para testes <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<,,,,,,,,,,
        strcpy((*vterritorio)[0].nome, "China");
        strcpy((*vterritorio)[0].cor, "Vermelho");
        (*vterritorio)[0].tropas=1;

        strcpy((*vterritorio)[1].nome, "Brasil");
        strcpy((*vterritorio)[1].cor, "Verde");
        (*vterritorio)[1].tropas=1;

        strcpy((*vterritorio)[2].nome, "EUA");
        strcpy((*vterritorio)[2].cor, "Azul");
        (*vterritorio)[2].tropas=1;


    *totalTerritorio = quantidadeTerritorios;
    printf("\nForam cadastrados %d Territorios\n", quantidadeTerritorios);
    return 0;
}

// --------------------------------------------------------------------------------------- Implementa o ataque entre os territorios

void atacar(Territorios *atacante, Territorios *defensor)
{
    // Sorteia os numeros
    srand(time(NULL));
    int min = 1, max = 6;

    int ata = rand() % (max - min + 1) + min;
    int def = rand() % (max - min + 1) + min;

    ata=6; // temporario para teste <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    def=5;

    printf("\n--- RESULTADO DA BATALHA ---\n\n");
    printf("O atacante %s rolou o dado e tirou: %d\n", (*atacante).nome, ata);
    printf("O defensor %s rolou o dado e tirou: %d\n\n", (*defensor).nome, def);

    // Verifica quem ganhou ou se deu empate
    if (ata > def)
    {
        (*atacante).tropas += 1;
        (*defensor).tropas -= 1;

        if (strcmp((*atacante).cor, Global_Jogador.jogador) == 0)
        {
            Global_Jogador.tropasBatalha = 1;
        } // Armazenando o resultado da batalha
        else if (strcmp((*defensor).cor, Global_Jogador.jogador) == 0)
        {
            Global_Jogador.tropasBatalha = -1;
        } // Armazenando o resultado da batalha

        printf("VITORIA DO ATAQUE! O defensor perdeu uma tropa.\n\n");
        if ((*defensor).tropas == 0)
        {
            strcpy((*defensor).cor, (*atacante).cor);
            printf("CONQUISTA! O territorio %s foi dominado pelo Exercito %s!\n", (*defensor).nome, (*atacante).cor);
        }
    }
    else if (def > ata)
    {
        (*defensor).tropas = (*defensor).tropas + (*atacante).tropas / 2; // Se o defensor ganhar, fica com metade das tropas do atacante
        (*atacante).tropas = (*atacante).tropas-(*atacante).tropas / 2;   // Se o atacante perder, perde metade de suas tropas para o defensor

        if (strcmp((*defensor).cor, Global_Jogador.jogador) == 0)
        {
            Global_Jogador.tropasBatalha = (*atacante).tropas / 2;
        } // Armazenando o resultado da batalha
        else if (strcmp((*atacante).cor, Global_Jogador.jogador) == 0)
        {
            Global_Jogador.tropasBatalha = -((*atacante).tropas / 2);
        } // Armazenando o resultado da batalha

        printf("VITORIA DA DEFESA! O Atacante perdeu metade das tropas.\n\n");
        if ((*atacante).tropas == 0)
        {
            strcpy((*atacante).cor, (*defensor).cor);
            printf("CONQUISTA! O territorio %s foi dominado pelo Exercito %s!\n", (*atacante).nome, (*defensor).cor);
        }
    }
    else
    {
        printf("EMPATE!\n\n");
        if ((strcmp((*atacante).cor, Global_Jogador.jogador) == 0) || (strcmp((*defensor).cor, Global_Jogador.jogador) == 0))
        {
            Global_Jogador.tropasBatalha = -999;
        }
    }

    // Pausa
    limparBuffer();
    printf("Precione ENTER para continuar para o proximo turno... ");
    getchar();
}

// --------------------------------------------------------------------------------------- Exibe o mapa atual

void mapaAtual(Territorios **vTerritorios, int *totalTerritorio)
{
    printf("\n           MAPA DO MUNDO - ESTADO ATUAL\n==================================================\n\n");

    int tam = *totalTerritorio;
    for (int i = 0; i < tam; i++)
    { // Verifica se o territorio foi eliminado
        if ((*vTerritorios)[i].tropas > 0)
        {
            printf("  %d. %-10s (Exercito %-12sTropas: %d)\n", i + 1, (*vTerritorios)[i].nome, (*vTerritorios)[i].cor, (*vTerritorios)[i].tropas);
        }
        else
        {
            printf("  %d. %-10s (TERRITORIO ELIMINADO)\n", i + 1, (*vTerritorios)[i].nome);
        }
    }
    printf("\n==================================================\n\n");
}

// --------------------------------------------------------------------------------------- Atualiza a pontuação para cada missão

int verificarMissao(char *missao, Territorios *mapa, int tamanho)
{ 
    /*
        1 Vencer 2 Batalhas seguidas
        2 Eliminar todos os territorios
        3 Conquistar um territorio
        4 Invicto, Três batalhas sem perder
        5 Ganhar 3 Tropas
    */
   
    switch (Global_Jogador.numero_missao)
    {
    case 0: // Se vencer acumula vitórias seguidas, mas se perder uma vez a pontuação zera. A pontuação necessária é 2.
        if (Global_Jogador.tropasBatalha > 0)
        {
            Global_Jogador.pontuacaoMissao++;
        }
        else
            Global_Jogador.pontuacaoMissao = 0;

        if (Global_Jogador.pontuacaoMissao == 2)
            return 1;

        break;

    case 1: // Conta os territórios que estão sem tropas, se o número for igual ao total de terrtórios inimigos, pontua-se 1 ponto. A pontuação necessária é 1 ponto.
        int c = 0;

        for (int i = 0; i < tamanho; i++)
        {
            if (Global_Jogador.tropasBatalha > 0 && (mapa[i].tropas == 0))
            {
                c++;
            }
        }
        if (c == tamanho - 1)
        {
            Global_Jogador.pontuacaoMissao = 1;
        }

        if (Global_Jogador.pontuacaoMissao == 1)
            return 1;
        break;

    case 2: // Busca um território sem tropas, se encontrar e o jogador venceu a batalha, pontua-se 1 ponto. A pontuação necessária é 1 ponto.
        for (int i = 0; i < tamanho; i++)
        {
            if (Global_Jogador.tropasBatalha > 0 && (mapa[i].tropas == 0))
            {
                Global_Jogador.pontuacaoMissao = 1;
            }
        }

        if (Global_Jogador.pontuacaoMissao == 1)
            return 1;
        break;

    case 3: // Se não perder acumula Global_Jogador.tropasBatalha seguidos, mas se perder uma vez a pontuação zera. A pontuação necessária é 3.
        if (Global_Jogador.tropasBatalha > 0 || Global_Jogador.tropasBatalha == -999)
        {
            Global_Jogador.pontuacaoMissao++;
        }
        else
            Global_Jogador.pontuacaoMissao = 0;

        if (Global_Jogador.pontuacaoMissao == 2)
            return 1;
        break;

    case 4: // Cada batalha uma vitória aumenta a pontuação e cada derrota diminui a pontuação. A pontuação necessária é 3.

        if (Global_Jogador.tropasBatalha > 0)
        {
            Global_Jogador.pontuacaoMissao += Global_Jogador.tropasBatalha;
        }
        else
        {
            Global_Jogador.pontuacaoMissao -= Global_Jogador.tropasBatalha;
        }

        if (Global_Jogador.pontuacaoMissao == 3)
            return 1;
        break;

    default:
        return -1;
        break;
    }
    Global_Jogador.tropasBatalha=0;
}

// --------------------------------------------------------------------------------------- Sorteia qual vai ser a missao a ser cumprida pelo jogador que vai ser sorteado

void sortearMissao(char *missaoJogador, char missoes[][40], int totalMissoes)
{
    int aleatorio;
    while (1)
    {
        srand(time(NULL));
        int min = 0, max = totalMissoes - 1;
        int aleatorio = rand() % (max - min + 1) + min;
        if(aleatorio!=Global_Jogador.numero_missao)
        {
            break;
        }
    }
    aleatorio=3; // só para testes <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
    strcpy(missaoJogador, missoes[aleatorio]);
    Global_Jogador.numero_missao = aleatorio;
}

// --------------------------------------------------------------------------------------- Sorteia qual territorio vai ficar para o jogador

void sortearJogador(int totalTerritorios, Territorios *mapa)
{
    srand(time(NULL));
    int min = 0, max = totalTerritorios - 1;
    int aleatorio = rand() % (max - min + 1) + min;
    strcpy(Global_Jogador.jogador, mapa[aleatorio].cor);
}

// --------------------------------------------------------------------------------------- Liberando a memória que foi alocada

void liberarMemoria(char *texto, Territorios *mapa)
{
    free(texto);
    free(mapa);
    printf("\n\n       --- Memoria liberada! ---\n\n");
}
