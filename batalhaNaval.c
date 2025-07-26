#include <stdio.h>

// Desafio Batalha Naval - MateCheck - Nível Novato
// Este código implementa o sistema básico de Batalha Naval.
// Funcionalidades: tabuleiro 10x10, posicionamento de 2 navios (horizontal e vertical)

int main() {
    // Declaração da matriz que representa o tabuleiro 10x10
    int tabuleiro[10][10];

    // Declaração dos vetores que representam os navios (tamanho 3)
    int navioHorizontal[3] = {3, 3, 3}; // Navio horizontal com valor 3
    int navioVertical[3] = {3, 3, 3};   // Navio vertical com valor 3

    // Coordenadas dos navios (definidas no código)
    int linhaNavioHorizontal = 2;  // Linha onde o navio horizontal será colocado
    int colunaNavioHorizontal = 1; // Coluna onde o navio horizontal começará
    int linhaNavioVertical = 5;    // Linha onde o navio vertical começará
    int colunaNavioVertical = 7;   // Coluna onde o navio vertical será colocado

    // Variáveis auxiliares para loops
    int linha, coluna, i;

    printf("BATALHA NAVAL\n\n");

    // Etapa 1: Inicializar o tabuleiro com água (valor 0)
    printf("Inicializando tabuleiro 10x10...\n");
    for (linha = 0; linha < 10; linha++)
    {
        for (coluna = 0; coluna < 10; coluna++)
        {
            tabuleiro[linha][coluna] = 0; // 0 representa água
        }
    }
    printf("Tabuleiro inicializado!\n\n");

    // Etapa 2: Posicionar navio horizontal
    printf("Posicionando navio horizontal (tamanho 3)...\n");

    // Verificar se o navio horizontal cabe no tabuleiro
    if (colunaNavioHorizontal + 3 <= 10)
    {
        // Colocar o navio horizontal no tabuleiro
        for (i = 0; i < 3; i++)
        {
            tabuleiro[linhaNavioHorizontal][colunaNavioHorizontal + i] = navioHorizontal[i];
        }

        // Mostrar as coordenadas do navio horizontal
        printf("Navio horizontal posicionado nas coordenadas:\n");
        for (i = 0; i < 3; i++)
        {
            printf("  Parte %d: linha %d, coluna %d\n",
                   i + 1, linhaNavioHorizontal, colunaNavioHorizontal + i);
        }
    }
    else
    {
        printf("Erro: Navio horizontal não cabe no tabuleiro!\n");
    }
    printf("\n");

    // Etapa 3: Posicionar navio vertical
    printf("Posicionando navio vertical (tamanho 3)...\n");

    // Verificar se o navio vertical cabe no tabuleiro
    if (linhaNavioVertical + 3 <= 10)
    {
        // Verificar se não há sobreposição
        int temSobreposicao = 0;
        for (i = 0; i < 3; i++)
        {
            if (tabuleiro[linhaNavioVertical + i][colunaNavioVertical] != 0)
            {
                temSobreposicao = 1;
                break;
            }
        }

        if (temSobreposicao == 0)
        {
            // Colocar o navio vertical no tabuleiro
            for (i = 0; i < 3; i++)
            {
                tabuleiro[linhaNavioVertical + i][colunaNavioVertical] = navioVertical[i];
            }

            // Mostrar as coordenadas do navio vertical
            printf("Navio vertical posicionado nas coordenadas:\n");
            for (i = 0; i < 3; i++)
            {
                printf("  Parte %d: linha %d, coluna %d\n",
                       i + 1, linhaNavioVertical + i, colunaNavioVertical);
            }
        }
        else
        {
            printf("Erro: Há sobreposição com outro navio!\n");
        }
    }
    else
    {
        printf("Erro: Navio vertical não cabe no tabuleiro!\n");
    }
    printf("\n");

    // Etapa 4: Exibir o tabuleiro final
    printf("TABULEIRO FINAL\n");
    printf("Legenda: 0 = Água, 3 = Navio\n\n");

    // Mostrar números das colunas
    printf("   ");
    for (coluna = 0; coluna < 10; coluna++)
    {
        printf(" %d ", coluna);
    }
    printf("\n");

    // Mostrar o tabuleiro linha por linha
    for (linha = 0; linha < 10; linha++)
    {
        printf("%d  ", linha); // Número da linha

        for (coluna = 0; coluna < 10; coluna++)
        {
            printf(" %d ", tabuleiro[linha][coluna]);
        }
        printf("\n");
    }
    return 0;
}
