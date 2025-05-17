#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PIECES 3
#define TAM_TABULEIRO 8

typedef struct {
    char nome[10];
    int tipo;    // 0: Bispo, 1: Torre, 2: Rainha
    int limite;  // limite máximo de casas
    int dx, dy;  // direção fixa de movimento
    int x, y;    // posição inicial
} Peca;

// Verifica se está dentro do tabuleiro
int dentro_tabuleiro(int x, int y) {
    return x >= 0 && x < TAM_TABULEIRO && y >= 0 && y < TAM_TABULEIRO;
}

// Imprime a direção
void imprimir_direcao(int dx, int dy) {
    if (dx == 1 && dy == 1) printf("direita,cima\n");
    else if (dx == 1 && dy == 0) printf("direita\n");
    else if (dx == -1 && dy == 0) printf("esquerda\n");
    else printf("direção desconhecida\n");
}

// Simula o movimento da peça
int mover_peca(Peca peca, int casas) {
    if (casas < 1 || casas > peca.limite) {
        printf("Movimento inválido. A peça %s pode se mover até %d casas.\n", peca.nome, peca.limite);
        return 0;
    }

    int x = peca.x;
    int y = peca.y;

    for (int i = 0; i < casas; i++) {
        x += peca.dx;
        y += peca.dy;

        if (!dentro_tabuleiro(x, y)) {
            printf("Movimento sai do tabuleiro após %d casas.\n", i + 1);
            return 0;
        }
    }

    imprimir_direcao(peca.dx, peca.dy);
    printf("Movimento de %d casas válido para a peça %s.\n", casas, peca.nome);
    return 1;
}

int main() {
    // Cada peça tem direção, limite, e posição inicial adequada ao movimento
    Peca pecas[MAX_PIECES] = {
        {"Bispo", 0, 5, 1, 1, 0, 0},    // 5 casas diagonal direita-cima, começa em (0,0)
        {"Torre", 1, 5, 1, 0, 0, 0},    // 5 casas para a direita, começa em (0,0)
        {"Rainha", 2, 8, -1, 0, 7, 0}   // 8 casas para a esquerda, começa em (7,0)
    };

    int tipo, casas;

    printf("Escolha a peça (0: Bispo, 1: Torre, 2: Rainha): ");
    scanf("%d", &tipo);

    while (tipo < 0 || tipo >= MAX_PIECES) {
        printf("Tipo inválido. Escolha entre 0 e 2: ");
        scanf("%d", &tipo);
    }

    Peca peca = pecas[tipo];

    do {
        printf("Quantas casas deseja mover a peça %s? (1 até %d): ", peca.nome, peca.limite);
        scanf("%d", &casas);

        if (!mover_peca(peca, casas)) {
            printf("Movimento inválido para a peça %s.\n", peca.nome);
        }

        char continuar;
        printf("Deseja testar outro movimento? (s/n): ");
        scanf(" %c", &continuar);
        if (continuar != 's' && continuar != 'S') break;

    } while (1);

    return 0;
}
