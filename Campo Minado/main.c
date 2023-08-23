#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <unistd.h>
#include <string.h>

typedef struct{
    int vizinhos;
    int bomba;
    int aberto;
} Mapa;

void inicializa_mapa(Mapa **mapa, int tamanho_mapa);
void printa_bombas(Mapa **mapa, int tamanho_mapa);
void printa_mapa(Mapa **mapa, int tamanho_mapa);
void libera_memoria_mapa(Mapa **mapa, int tamanho_mapa);
int seleciona_menu();
void randomize_bombs(Mapa **mapa, int tamanho_mapa, int num_bombs);
void inicializa_vizinhos(Mapa **mapa, int tamanho_mapa);
int coordenada_valida(int tamanho_mapa, int i, int j);
int conta_vizinhos(Mapa **mapa, int tamanho_mapa, int i, int j);
void inicializa_jogo(Mapa **mapa, int tamanho_mapa, int numero_bombas);
void abrir_celula(Mapa **mapa, int tamanho_mapa, int linha, int coluna);
void jogada(int tamanho_mapa, Mapa **mapa);
int ganhou(Mapa **mapa, int tamanho_mapa);

void inicializa_mapa(Mapa **mapa, int tamanho_mapa)
{
    // percorre a matriz
    for (int i = 0; i < tamanho_mapa; i++)
    {
        for (int j = 0; j < tamanho_mapa; j++)
        {
            mapa[i][j].vizinhos = 0;
            mapa[i][j].aberto = 0;
            mapa[i][j].bomba = 0;
        }
    }
}

void printa_mapa(Mapa **mapa, int tamanho_mapa)
{
    printf("    ");
    for (int i = 0; i < tamanho_mapa; i++)
    {
        if (i>=10)
        {
            printf("%d  ", i);
        } else{
            printf("%d   ", i);
        }
        
        
    }
    printf("\n");
    
    // percorre a matriz
    for (int i = 0; i < tamanho_mapa; i++)
    {
        if (i>=10)
        {
            printf("%d ", i);
        } else{
            printf("%d  ", i);
        }
        
        
        for (int j = 0; j < tamanho_mapa; j++)
        {
            if (mapa[i][j].aberto)
            {
                if (mapa[i][j].bomba) {
                    printf(" * ");
                }
                else {
                    printf("|%d| ", mapa[i][j].vizinhos);
                }
                
            } else{
                printf("| | ");
            }
            
        }
        printf("\n");
    }
}

void printa_bombas(Mapa **mapa, int tamanho_mapa)
{
    // percorre a matriz
    for (int i = 0; i < tamanho_mapa; i++)
    {
        for (int j = 0; j < tamanho_mapa; j++)
        {
            printf("%d ", mapa[i][j].bomba);
        }
        printf("\n");
    }
}

void libera_memoria_mapa(Mapa **mapa, int tamanho_mapa)
{
    // libera a memória da matriz
    for (int i = 0; i < tamanho_mapa; i++)
        free(mapa[i]);
    free(mapa);
}

int seleciona_menu()
{
    int opcao;
    while (true)
    {
        printf("Digite a opcao desejada: \n");
        printf("1: Jogar \n");
        printf("2: Inteligencia artificial \n");
        printf("3: Sair\n");
        scanf("%d", &opcao);
        switch (opcao)
        {
        case 1:
            return 1;
            break;

        case 2:
            return 2;
            break;

        case 3:
            return 3;
            break;

        default:
            break;
        }
    }
}

void randomize_bombs(Mapa **mapa, int tamanho_mapa, int num_bombs)
{
    while (num_bombs > 0)
    {
        int i = rand() % tamanho_mapa;
        int j = rand() % tamanho_mapa;
        if (mapa[i][j].bomba == 1)
        {
            continue;
        }
        else
        {
            mapa[i][j].bomba = 1;
            num_bombs--;
        }
    }
}

void inicializa_vizinhos(Mapa **mapa, int tamanho_mapa)
{
    // percorre a matriz
    for (int i = 0; i < tamanho_mapa; i++)
    {
        for (int j = 0; j < tamanho_mapa; j++)
        {
            mapa[i][j].vizinhos = conta_vizinhos(mapa, tamanho_mapa, i, j);
        }
    }
}

int coordenada_valida(int tamanho_mapa, int i, int j)
{
    if (i >= 0 && i < tamanho_mapa && j >= 0 && j < tamanho_mapa)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

int conta_vizinhos(Mapa **mapa, int tamanho_mapa, int i, int j)
{
    int quantidade = 0;

    if(coordenada_valida(tamanho_mapa, i-1, j) && mapa[i-1][j].bomba)
        quantidade++;

    if(coordenada_valida(tamanho_mapa, i+1, j) && mapa[i+1][j].bomba)
        quantidade++;

    if(coordenada_valida(tamanho_mapa, i, j+1) && mapa[i][j+1].bomba)
        quantidade++;

    if(coordenada_valida(tamanho_mapa, i, j-1) && mapa[i][j-1].bomba)
        quantidade++;    

    return quantidade;
}

void inicializa_jogo(Mapa **mapa, int tamanho_mapa, int numero_bombas){
    inicializa_mapa(mapa, tamanho_mapa);
    randomize_bombs(mapa, tamanho_mapa, numero_bombas);
    inicializa_vizinhos(mapa, tamanho_mapa);
}

void abrir_celula(Mapa **mapa, int tamanho_mapa, int linha, int coluna){
    if (coordenada_valida(tamanho_mapa, linha, coluna) == 1 && mapa[linha][coluna].aberto == 0)
    {
        mapa[linha][coluna].aberto = 1;
        if (mapa[linha][coluna].vizinhos == 0)
        {
            abrir_celula(mapa, tamanho_mapa, linha-1, coluna);
            abrir_celula(mapa, tamanho_mapa, linha+1, coluna);
            abrir_celula(mapa, tamanho_mapa, linha, coluna-1);
            abrir_celula(mapa, tamanho_mapa, linha, coluna+1);
        }
    }
}

void jogada(int tamanho_mapa, Mapa **mapa){
    int linha, coluna;
    do
    {
        printa_mapa(mapa, tamanho_mapa);
        printf("\n");
        do
        {
            printf("Digite as coordenadas de linha e coluna: ");
            scanf("%d%d", &linha, &coluna);
            if (coordenada_valida(tamanho_mapa, linha, coluna) == 0)
            {
                printf("Coordenada inválida!!\n");
            }
            
        } while (coordenada_valida(tamanho_mapa, linha, coluna) == 0 || mapa[linha][coluna].aberto == 1);

        abrir_celula(mapa, tamanho_mapa, linha, coluna);

    } while (ganhou(mapa, tamanho_mapa) != 0 && mapa[linha][coluna].bomba == 0);

    if (mapa[linha][coluna].bomba == 1)
    {
        printf("Que pena, vc perdeu!\n");
    } else {
        printf("Parabens, vc ganhou!\n");
    }
    
}

int ganhou(Mapa **mapa, int tamanho_mapa){
    int quantidade = 0;
    // percorre a matriz
    for (int i = 0; i < tamanho_mapa; i++)
    {
        for (int j = 0; j < tamanho_mapa; j++)
        {
            if (mapa[i][j].aberto == 0 && mapa[i][j].bomba == 0)
            {
                quantidade++;
            }
            
        }
    }
    return quantidade;
}


int main(int argc, char const *argv[])
{
    srand(time(NULL));
    printf("\nCAMPO MINADO\n");
    int numero_bombas, tamanho_mapa;
    int jogar_novamente=0;
    int menu = 0;

    while (true)
    {
        if (jogar_novamente == 1)
        {
            menu = 1;
            jogar_novamente = 0;
        } 
        else
        {
            menu = seleciona_menu();
        }
        
        if (menu == 3)
        {
        printf("\nsaindo...");
        exit(1);
        }

        if (menu == 2)
        {
        // 1 tiro - atira aleatoriamente
        // analisa matriz
        }

        if (menu == 1)
        {
            printf("\nDigite o tamanho do mapa (recomendado de 6 a 12): ");
            scanf("%d", &tamanho_mapa);
            printf("\nDigite o numero de bombas: ");
            scanf("%d", &numero_bombas);

            Mapa **mapa;
            // aloca um vetor de tamanho_mapa ponteiros para linhas
            mapa = malloc(tamanho_mapa * sizeof(Mapa *));
            // aloca cada uma das linhas (vetores de tamanho_mapa inteiros)
            for (int i = 0; i < tamanho_mapa; i++)
                mapa[i] = malloc(tamanho_mapa * sizeof(Mapa));

            inicializa_jogo(mapa, tamanho_mapa, numero_bombas);
            
            jogada(tamanho_mapa, mapa);

            printf("Gostaria de jogar novamente? (sim ou nao): ");
            char *jogar = "sim";
            char resposta[3];
            scanf("%s", resposta);
            char *p2 = resposta;
            if (strcmp(jogar, p2) == 0)
            {
                printf("jogar novamente!\n");
                jogar_novamente = 1;

            } else {
                printf("saindo do jogo...\n");
            }
            libera_memoria_mapa(mapa, tamanho_mapa);
        }

    }

    return 0;
}
