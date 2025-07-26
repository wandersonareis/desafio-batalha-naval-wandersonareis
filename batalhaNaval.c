#include <stdio.h>

// Desafio Batalha Naval - MateCheck - Nível Mestre
// Este código implementa o sistema de Batalha Naval com 4 navios e habilidades especiais.
// Funcionalidades: tabuleiro 10x10, posicionamento de 4 navios (2 retos + 2 diagonais) + habilidades

// Constantes para identificação dos elementos
#define AGUA 0               // Representa água no tabuleiro
#define NAVIO1 1             // Navio 1 - Horizontal
#define NAVIO2 2             // Navio 2 - Vertical
#define NAVIO3 3             // Navio 3 - Diagonal principal
#define NAVIO4 4             // Navio 4 - Diagonal secundária
#define AREA_HABILIDADE 5    // Área afetada pela habilidade especial
#define TAMANHO_NAVIO 3      // Tamanho fixo dos navios
#define TAMANHO_HABILIDADE 5 // Tamanho das matrizes de habilidade (5x5)

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

// Função para criar a matriz de habilidade Cone
// O cone tem o ponto no topo e se expande para baixo
void criarHabilidadeCone(int matriz[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE])
{
    int linha, coluna;

    // Inicializar matriz com zeros
    for (linha = 0; linha < TAMANHO_HABILIDADE; linha++)
    {
        for (coluna = 0; coluna < TAMANHO_HABILIDADE; coluna++)
        {
            matriz[linha][coluna] = 0;
        }
    }

    // Criar formato de cone usando condicionais
    for (linha = 0; linha < TAMANHO_HABILIDADE; linha++)
    {
        for (coluna = 0; coluna < TAMANHO_HABILIDADE; coluna++)
        {
            // Centro da matriz é na posição [2][2]
            int centro = TAMANHO_HABILIDADE / 2;
            int distanciaCentro = coluna - centro;

            // Se a distância do centro for menor ou igual ao número da linha
            if (distanciaCentro >= -linha && distanciaCentro <= linha)
            {
                matriz[linha][coluna] = 1;
            }
        }
    }
}

// Função para criar a matriz de habilidade Cruz
// A cruz tem o centro no meio e se estende nas 4 direções
void criarHabilidadeCruz(int matriz[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE])
{
    int linha, coluna;

    // Inicializar matriz com zeros
    for (linha = 0; linha < TAMANHO_HABILIDADE; linha++)
    {
        for (coluna = 0; coluna < TAMANHO_HABILIDADE; coluna++)
        {
            matriz[linha][coluna] = 0;
        }
    }

    // Criar formato de cruz usando condicionais
    int centro = TAMANHO_HABILIDADE / 2;
    for (linha = 0; linha < TAMANHO_HABILIDADE; linha++)
    {
        for (coluna = 0; coluna < TAMANHO_HABILIDADE; coluna++)
        {
            // Se está na linha central ou coluna central
            if (linha == centro || coluna == centro)
            {
                matriz[linha][coluna] = 1;
            }
        }
    }
}

// Função para criar a matriz de habilidade Octaedro (formato losango)
// O octaedro tem formato de losango com centro no meio
void criarHabilidadeOctaedro(int matriz[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE])
{
    int linha, coluna;

    // Inicializar matriz com zeros
    for (linha = 0; linha < TAMANHO_HABILIDADE; linha++)
    {
        for (coluna = 0; coluna < TAMANHO_HABILIDADE; coluna++)
        {
            matriz[linha][coluna] = 0;
        }
    }

    // Criar formato de losango usando condicionais
    int centro = TAMANHO_HABILIDADE / 2;
    for (linha = 0; linha < TAMANHO_HABILIDADE; linha++)
    {
        for (coluna = 0; coluna < TAMANHO_HABILIDADE; coluna++)
        {
            // Calcular distância Manhattan do centro
            int distanciaLinha = (linha > centro) ? linha - centro : centro - linha;
            int distanciaColuna = (coluna > centro) ? coluna - centro : centro - coluna;

            // Se a soma das distâncias for menor ou igual ao raio
            if (distanciaLinha + distanciaColuna <= centro)
            {
                matriz[linha][coluna] = 1;
            }
        }
    }
}

// Função para aplicar habilidade no tabuleiro
// Sobrepõe a matriz de habilidade no tabuleiro a partir do ponto de origem
void aplicarHabilidade(int tabuleiro[10][10], int habilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE],
                       int linhaOrigem, int colunaOrigem, char nomeHabilidade[])
{
    int i, j;
    int centro = TAMANHO_HABILIDADE / 2;

    printf("Aplicando habilidade %s na posição (%d, %d)...\n", nomeHabilidade, linhaOrigem, colunaOrigem);

    // Aplicar a habilidade no tabuleiro
    for (i = 0; i < TAMANHO_HABILIDADE; i++)
    {
        for (j = 0; j < TAMANHO_HABILIDADE; j++)
        {
            // Calcular posição no tabuleiro
            int linhaTab = linhaOrigem - centro + i;
            int colunaTab = colunaOrigem - centro + j;

            // Verificar se está dentro dos limites do tabuleiro
            if (linhaTab >= 0 && linhaTab < 10 && colunaTab >= 0 && colunaTab < 10)
            {
                // Se a habilidade afeta esta posição
                if (habilidade[i][j] == 1)
                {
                    // Só marca como área de habilidade se for água
                    if (tabuleiro[linhaTab][colunaTab] == AGUA)
                    {
                        tabuleiro[linhaTab][colunaTab] = AREA_HABILIDADE;
                    }
                }
            }
        }
    }
    printf("Habilidade %s aplicada!\n\n", nomeHabilidade);
}

// Função para exibir uma matriz de habilidade (para demonstração)
void exibirMatrizHabilidade(int matriz[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE], char nome[])
{
    int i, j;

    printf("Matriz de habilidade %s (%dx%d):\n", nome, TAMANHO_HABILIDADE, TAMANHO_HABILIDADE);
    for (i = 0; i < TAMANHO_HABILIDADE; i++)
    {
        printf("  ");
        for (j = 0; j < TAMANHO_HABILIDADE; j++)
        {
            printf(" %d ", matriz[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int main()
{
    // Declaração da matriz que representa o tabuleiro 10x10
    int tabuleiro[10][10];

    // Declaração das matrizes de habilidades
    int habilidadeCone[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];
    int habilidadeCruz[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];
    int habilidadeOctaedro[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];

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

    // Coordenadas das habilidades (definidas no código)
    int linhaCone = 7, colunaCone = 2;         // Posição da habilidade Cone
    int linhaCruz = 3, colunaCruz = 7;         // Posição da habilidade Cruz
    int linhaOctaedro = 8, colunaOctaedro = 6; // Posição da habilidade Octaedro

    // Variáveis auxiliares para loops
    int linha, coluna;

    printf("BATALHA NAVAL - NÍVEL MESTRE\n");
    printf("Habilidades Especiais: Cone, Cruz e Octaedro\n\n");

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

    // Etapa 3: Criar as matrizes de habilidades
    printf("Criando matrizes de habilidades especiais...\n");
    criarHabilidadeCone(habilidadeCone);
    criarHabilidadeCruz(habilidadeCruz);
    criarHabilidadeOctaedro(habilidadeOctaedro);
    printf("Matrizes de habilidades criadas!\n\n");

    // Exibir as matrizes de habilidades para demonstração
    exibirMatrizHabilidade(habilidadeCone, "Cone");
    exibirMatrizHabilidade(habilidadeCruz, "Cruz");
    exibirMatrizHabilidade(habilidadeOctaedro, "Octaedro");

    // Etapa 4: Aplicar habilidades no tabuleiro
    printf("Aplicando habilidades especiais no tabuleiro...\n\n");
    aplicarHabilidade(tabuleiro, habilidadeCone, linhaCone, colunaCone, "Cone");
    aplicarHabilidade(tabuleiro, habilidadeCruz, linhaCruz, colunaCruz, "Cruz");
    aplicarHabilidade(tabuleiro, habilidadeOctaedro, linhaOctaedro, colunaOctaedro, "Octaedro");

    // Etapa 5: Exibir o tabuleiro final
    printf("TABULEIRO FINAL COM HABILIDADES\n");
    printf("Legenda: 0 = Água, 1-4 = Navios, 5 = Área de Habilidade\n\n");

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
    printf("- Navio 4: Diagonal secundária (posições 6,4 até 8,2)\n\n");

    printf("Resumo das habilidades aplicadas:\n");
    printf("- Habilidade Cone: centro na posição (%d, %d)\n", linhaCone, colunaCone);
    printf("- Habilidade Cruz: centro na posição (%d, %d)\n", linhaCruz, colunaCruz);
    printf("- Habilidade Octaedro: centro na posição (%d, %d)\n", linhaOctaedro, colunaOctaedro);

    return 0;
}
