#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define TAMANHO_TABULEIRO 10
#define TAMANHO_NAVIO 3

// Função para verificar se um navio pode ser colocado sem sair dos limites e sem sobreposição
int podeColocar(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO],
                int linhaInicial, int colunaInicial, char tipo) {
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        int linha = linhaInicial;
        int coluna = colunaInicial;

        if (tipo == 'H') {          // Horizontal →
            coluna += i;
        } else if (tipo == 'V') {   // Vertical ↓
            linha += i;
        } else if (tipo == 'D') {   // Diagonal principal ↘
            linha += i;
            coluna += i;
        } else if (tipo == 'A') {   // Diagonal secundária ↙
            linha += i;
            coluna -= i;
        }

        // Verifica se está dentro do tabuleiro
        if (linha < 0 || linha >= TAMANHO_TABULEIRO ||
            coluna < 0 || coluna >= TAMANHO_TABULEIRO) {
            return 0; // Não pode
        }

        // Verifica se já existe um navio
        if (tabuleiro[linha][coluna] != 0) {
            return 0; // Não pode
        }
    }
    return 1; // Pode colocar
}

// Função para efetivamente posicionar o navio (já validado)
void posicionarNavio(int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO],
                     int linhaInicial, int colunaInicial, char tipo) {
    for (int i = 0; i < TAMANHO_NAVIO; i++) {
        int linha = linhaInicial;
        int coluna = colunaInicial;

        if (tipo == 'H') {
            coluna += i;
        } else if (tipo == 'V') {
            linha += i;
        } else if (tipo == 'D') {
            linha += i;
            coluna += i;
        } else if (tipo == 'A') {
            linha += i;
            coluna -= i;
        }

        tabuleiro[linha][coluna] = 3;
    }
}

int main() {
    int tabuleiro[TAMANHO_TABULEIRO][TAMANHO_TABULEIRO] = {0};

    // Semente para sorteios
    srand(time(NULL));

    // Lista de navios (4 tipos fixos)
    char tipos[4] = {'H', 'V', 'D', 'A'};

    // Garantir 4 navios posicionados
    for (int k = 0; k < 4; k++) {
        int colocado = 0;
        while (!colocado) {
            // Sorteia posição inicial
            int linha = rand() % TAMANHO_TABULEIRO;
            int coluna = rand() % TAMANHO_TABULEIRO;

            // Testa se pode colocar
            if (podeColocar(tabuleiro, linha, coluna, tipos[k])) {
                posicionarNavio(tabuleiro, linha, coluna, tipos[k]);
                colocado = 1; // Sai do while
            }
        }
    }

    // Exibir tabuleiro
    printf("=== TABULEIRO DE BATALHA NAVAL ===\n\n");
    for (int i = 0; i < TAMANHO_TABULEIRO; i++) {
        for (int j = 0; j < TAMANHO_TABULEIRO; j++) {
            printf("%d ", tabuleiro[i][j]);
        }
        printf("\n");
    }

    return 0;
}