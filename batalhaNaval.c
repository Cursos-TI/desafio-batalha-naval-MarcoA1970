#include <stdio.h>

#define TAMANHO_TABULEIRO 10
#define TAMANHO_NAVIO 3
#define TAMANHO_HABILIDADE 5   // tamanho fixo das matrizes de habilidade (5x5)

// ========================= Funções de Navio =========================

// Verifica se é possível colocar o navio sem sobreposição ou sair do tabuleiro
int podeColocar(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO],
                int linhaInicial, int colunaInicial, char tipo) {
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        int linha = linhaInicial;
        int coluna = colunaInicial;

        if (tipo == 'H') coluna += i;          // horizontal →
        else if (tipo == 'V') linha += i;      // vertical ↓
        else if (tipo == 'D') { linha += i; coluna += i; } // diagonal principal ↘
        else if (tipo == 'A') { linha += i; coluna -= i; } // diagonal secundária ↙

        if (linha < 0 || linha >= TAMANHO_TABULEIRO ||
            coluna < 0 || coluna >= TAMANHO_TABULEIRO)
            return 0; // fora do tabuleiro

        if (tabuleiro[linha][coluna] != 0)
            return 0; // sobreposição
    }
    return 1;
}

// Coloca o navio (já validado)
void posicionarNavio(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO],
                     int linhaInicial, int colunaInicial, char tipo) {
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        int linha = linhaInicial;
        int coluna = colunaInicial;

        if (tipo == 'H') coluna += i;
        else if (tipo == 'V') linha += i;
        else if (tipo == 'D') { linha += i; coluna += i; }
        else if (tipo == 'A') { linha += i; coluna -= i; }

        tabuleiro[linha][coluna] = 3; // 3 = navio
    }
}

// ========================= Funções de Habilidade =========================

// Constrói matriz Cone (forma triangular, expandindo para baixo)
void construirCone(int habilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]) {
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            if (j >= (TAMANHO_HABILIDADE/2 - i) && j <= (TAMANHO_HABILIDADE/2 + i))
                habilidade[i][j] = 1; // dentro do cone
            else
                habilidade[i][j] = 0;
        }
    }
}

// Constrói matriz Cruz (linha + coluna centrais)
void construirCruz(int habilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]) {
    int centro = TAMANHO_HABILIDADE / 2;
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            if (i == centro || j == centro)
                habilidade[i][j] = 1;
            else
                habilidade[i][j] = 0;
        }
    }
}

// Constrói matriz Octaedro (losango)
void construirOctaedro(int habilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE]) {
    int centro = TAMANHO_HABILIDADE / 2;
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            if (abs(i - centro) + abs(j - centro) <= centro)
                habilidade[i][j] = 1; // dentro do octaedro
            else
                habilidade[i][j] = 0;
        }
    }
}

// Sobrepõe a matriz de habilidade no tabuleiro
void aplicarHabilidade(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO],
                       int habilidade[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE],
                       int origemLinha, int origemColuna) {
    int centro = TAMANHO_HABILIDADE / 2;
    for (int i = 0; i < TAMANHO_HABILIDADE; i++) {
        for (int j = 0; j < TAMANHO_HABILIDADE; j++) {
            if (habilidade[i][j] == 1) {
                int linhaTab = origemLinha + (i - centro);
                int colTab   = origemColuna + (j - centro);
                // valida limites
                if (linhaTab >= 0 && linhaTab < TAMANHO_TABULEIRO &&
                    colTab >= 0 && colTab < TAMANHO_TABULEIRO) {
                    if (tabuleiro[linhaTab][colTab] == 0)
                        tabuleiro[linhaTab][colTab] = 5; // 5 = habilidade
                }
            }
        }
    }
}

// ========================= Programa Principal =========================

int main() {
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO] = {0};

    // Colocar 4 navios fixos
    if (podeColocar(tabuleiro, 2, 1, 'H')) posicionarNavio(tabuleiro, 2, 1, 'H');
    if (podeColocar(tabuleiro, 5, 7, 'V')) posicionarNavio(tabuleiro, 5, 7, 'V');
    if (podeColocar(tabuleiro, 0, 0, 'D')) posicionarNavio(tabuleiro, 0, 0, 'D');
    if (podeColocar(tabuleiro, 0, 9, 'A')) posicionarNavio(tabuleiro, 0, 9, 'A');

    // Matrizes de habilidades
    int cone[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];
    int cruz[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];
    int octaedro[TAMANHO_HABILIDADE][TAMANHO_HABILIDADE];

    construirCone(cone);
    construirCruz(cruz);
    construirOctaedro(octaedro);

    // Aplicar habilidades no tabuleiro (pontos de origem fixos)
    aplicarHabilidade(tabuleiro, cone, 4, 4);       // cone centrado em (4,4)
    aplicarHabilidade(tabuleiro, cruz, 7, 2);       // cruz centrada em (7,2)
    aplicarHabilidade(tabuleiro, octaedro, 6, 6);   // octaedro centrado em (6,6)

    // Exibir tabuleiro
    printf("=== TABULEIRO FINAL DE BATALHA NAVAL ===\n\n");
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            if (tabuleiro[i][j] == 0) printf("~ ");   // água
            else if (tabuleiro[i][j] == 3) printf("N "); // navio
            else if (tabuleiro[i][j] == 5) printf("* "); // habilidade
        }
        printf("\n");
    }

    return 0;
}