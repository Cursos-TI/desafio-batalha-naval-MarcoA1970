#include <stdio.h>

#define TAMANHO_TABULEIRO 10
#define TAMANHO_NAVIO 3

int main() {
    // Declaração da matriz que representa o tabuleiro (10x10) .
    // Inicialmente, todas as posições recebem 0 (água).
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO] = {0};

    // Vetores que representam os navios (não têm valor, apenas tamanho).
    int navioHorizontal[TAMANHO_NAVIO];
    int navioVertical[TAMANHO_NAVIO];

    // Coordenadas iniciais escolhidas diretamente no código:
    int linhaHorizontal = 2, colunaHorizontal = 4; // Navio horizontal começando em (2,4)
    int linhaVertical = 5, colunaVertical = 7;     // Navio vertical começando em (5,7)

    // ===== Posicionamento do navio horizontal =====
    // O navio ocupa TAMANHO_NAVIO casas consecutivas na mesma linha
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        // Verificação de limite do tabuleiro
        if (colunaHorizontal + i < TAMANHO_TABULEIRO) {
            tabuleiro[linhaHorizontal][colunaHorizontal + i] = 3;
        }
    }

    // ===== Posicionamento do navio vertical =====
    // O navio ocupa TAMANHO_NAVIO casas consecutivas na mesma coluna
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        // Verificação de limite do tabuleiro
        if (linhaVertical + i < TAMANHO_TABULEIRO) {
            // Antes de posicionar, garante que não sobrepõe outro navio
            if (tabuleiro[linhaVertical + i][colunaVertical] == 0) {
                tabuleiro[linhaVertical + i][colunaVertical] = 3;
            }
        }
    }

    // ===== Exibição do tabuleiro =====
    printf("=== TABULEIRO DE BATALHA NAVAL ===\n\n");
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }

    return 0;
}