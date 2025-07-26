#include <stdio.h>

// Desafio Batalha Naval - MateCheck - Nível Aventureiro
// Este código implementa o sistema de Batalha Naval com 4 navios.
// Funcionalidades: tabuleiro 10x10, posicionamento de 4 navios (2 retos + 2 diagonais)

// Constantes para identificação dos navios
#define AGUA 0          // Representa água no tabuleiro
#define NAVIO1 1        // Navio 1 - Horizontal
#define NAVIO2 2        // Navio 2 - Vertical
#define NAVIO3 3        // Navio 3 - Diagonal principal
#define NAVIO4 4        // Navio 4 - Diagonal secundária
#define TAMANHO_NAVIO 3 // Tamanho fixo dos navios

// Função para posicionar navios no tabuleiro
// Parâmetros:
// - tabuleiro: matriz 10x10 do jogo
// - valorNavio: valor do navio (NAVIO1, NAVIO2, etc.) - usado para identificação e posicionamento
// - tipoNavio: texto descritivo do tipo do navio (ex: "horizontal", "vertical")
// - linhaInicial: linha inicial do navio
// - colunaInicial: coluna inicial do navio
// - direcaoLinha: direção do crescimento na linha (0=não muda, 1=aumenta, -1=diminui)
// - direcaoColuna: direção do crescimento na coluna (0=não muda, 1=aumenta, -1=diminui)
// Retorna: 1 se sucesso, 0 se erro
int posicionarNavio(int tabuleiro[10][10], int valorNavio, char tipoNavio[],
                    int linhaInicial, int colunaInicial,
                    int direcaoLinha, int direcaoColuna)
{
    int i;

    printf("Posicionando navio %d (%s - tamanho %d)...\n", valorNavio, tipoNavio, TAMANHO_NAVIO);

    // Verificar se o navio cabe no tabuleiro
    int linhaFinal = linhaInicial + (direcaoLinha * (TAMANHO_NAVIO - 1));
    int colunaFinal = colunaInicial + (direcaoColuna * (TAMANHO_NAVIO - 1));

    if (linhaFinal < 0 || linhaFinal >= 10 || colunaFinal < 0 || colunaFinal >= 10)
    {
        printf("Erro: Navio %d não cabe no tabuleiro!\n", valorNavio);
        return 0;
    }

    // Verificar se não há sobreposição
    int temSobreposicao = 0;
    for (i = 0; i < TAMANHO_NAVIO; i++)
    {
        int linha = linhaInicial + (direcaoLinha * i);
        int coluna = colunaInicial + (direcaoColuna * i);

        if (tabuleiro[linha][coluna] != AGUA)
        {
            temSobreposicao = 1;
            break;
        }
    }

    if (temSobreposicao == 1)
    {
        printf("Erro: Navio %d tem sobreposição com outro navio!\n", valorNavio);
        return 0;
    }

    // Posicionar o navio no tabuleiro
    for (i = 0; i < TAMANHO_NAVIO; i++)
    {
        int linha = linhaInicial + (direcaoLinha * i);
        int coluna = colunaInicial + (direcaoColuna * i);
        tabuleiro[linha][coluna] = valorNavio;
    }

    // Mostrar as coordenadas do navio posicionado
    printf("Navio %d posicionado nas coordenadas:\n", valorNavio);
    for (i = 0; i < TAMANHO_NAVIO; i++)
    {
        int linha = linhaInicial + (direcaoLinha * i);
        int coluna = colunaInicial + (direcaoColuna * i);
        printf("  Parte %d: linha %d, coluna %d\n", i + 1, linha, coluna);
    }
    printf("\n");

    return 1; // Sucesso
}

int main()
{
    // Declaração da matriz que representa o tabuleiro 10x10
    int tabuleiro[10][10];

    // Coordenadas dos navios (definidas no código)
    // Navio 1 - Horizontal
    int linhaNavio1 = 1;
    int colunaNavio1 = 2;

    // Navio 2 - Vertical
    int linhaNavio2 = 5;
    int colunaNavio2 = 8;

    // Navio 3 - Diagonal principal (linha e coluna aumentam juntas)
    int linhaNavio3 = 2;
    int colunaNavio3 = 5;

    // Navio 4 - Diagonal secundária (linha aumenta, coluna diminui)
    int linhaNavio4 = 6;
    int colunaNavio4 = 4;

    // Variáveis auxiliares para loops
    int linha, coluna;

    printf("BATALHA NAVAL - Nível Aventureiro\n\n");

    // Etapa 1: Inicializar o tabuleiro com água (valor 0)
    printf("Inicializando tabuleiro 10x10...\n");
    for (linha = 0; linha < 10; linha++)
    {
        for (coluna = 0; coluna < 10; coluna++)
        {
            tabuleiro[linha][coluna] = AGUA; // Inicializa com água
        }
    }
    printf("Tabuleiro inicializado!\n\n");

    // Etapa 2: Posicionar todos os navios usando a função

    // Navio 1 - Horizontal (direção: linha não muda=0, coluna aumenta=1)
    if (!posicionarNavio(tabuleiro, NAVIO1, "horizontal", linhaNavio1, colunaNavio1, 0, 1))
    {
        printf("Falha ao posicionar navio %d!\n", NAVIO1);
        return 1;
    }

    // Navio 2 - Vertical (direção: linha aumenta=1, coluna não muda=0)
    if (!posicionarNavio(tabuleiro, NAVIO2, "vertical", linhaNavio2, colunaNavio2, 1, 0))
    {
        printf("Falha ao posicionar navio %d!\n", NAVIO2);
        return 1;
    }

    // Navio 3 - Diagonal principal (direção: linha aumenta=1, coluna aumenta=1)
    if (!posicionarNavio(tabuleiro, NAVIO3, "diagonal principal", linhaNavio3, colunaNavio3, 1, 1))
    {
        printf("Falha ao posicionar navio %d!\n", NAVIO3);
        return 1;
    }

    // Navio 4 - Diagonal secundária (direção: linha aumenta=1, coluna diminui=-1)
    if (!posicionarNavio(tabuleiro, NAVIO4, "diagonal secundária", linhaNavio4, colunaNavio4, 1, -1))
    {
        printf("Falha ao posicionar navio %d!\n", NAVIO4);
        return 1;
    }

    // Etapa 3: Exibir o tabuleiro final
    printf("TABULEIRO FINAL\n");
    printf("Legenda: 0 = Água, 1-4 = Navios\n\n");

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

    printf("\nResumo dos navios posicionados:\n");
    printf("- Navio 1: Horizontal (linha 1, colunas 2-4)\n");
    printf("- Navio 2: Vertical (coluna 8, linhas 5-7)\n");
    printf("- Navio 3: Diagonal principal (posições 2,5 até 4,7)\n");
    printf("- Navio 4: Diagonal secundária (posições 6,4 até 8,2)\n");

    return 0;
}
