#include <stdio.h>
#include <stdlib.h>


char tabuleiro[3][3];
char player = 'X';


void inicializarTabuleiro() {
    char pos = '1';
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            tabuleiro[i][j] = pos++;
}


void exibirTabuleiro() {
    limparTela();
    printf("\n      1   2   3\n\n");
    for (int i = 0; i < 3; i++) {
        printf(" %d    %c | %c | %c \n", i + 1, tabuleiro[i][0], tabuleiro[i][1], tabuleiro[i][2]);
        if (i < 2)
            printf("     ---|---|---\n");
    }
    printf("\n");
}


int linhasOuColunasIguais() {
    for (int i = 0; i < 3; i++) {
        if (tabuleiro[i][0] == tabuleiro[i][1] && tabuleiro[i][1] == tabuleiro[i][2]) return 1;
        if (tabuleiro[0][i] == tabuleiro[1][i] && tabuleiro[1][i] == tabuleiro[2][i]) return 1;
    }
    return 0;
}

int diagonaisIguais() {
    if (tabuleiro[0][0] == tabuleiro[1][1] && tabuleiro[1][1] == tabuleiro[2][2]) return 1;
    if (tabuleiro[0][2] == tabuleiro[1][1] && tabuleiro[1][1] == tabuleiro[2][0]) return 1;
    return 0;
}

int verificarVitoria() {
    return linhasOuColunasIguais() || diagonaisIguais();
}


int verificarEmpate() {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (tabuleiro[i][j] != 'X' && tabuleiro[i][j] != 'O')
                return 0;
    return 1;
}


void instrucoes() {
    limparTela(); 
    printf("=== INSTRUCOES DO JOGO ===\n\n");
    printf("1. Dois jogadores alternam jogadas.\n");
    printf("2. O jogador escolhe uma posicao de 1 a 9.\n");
    printf("3. Vence quem formar uma linha, coluna ou diagonal.\n");
    printf("4. Se todas as posicoes forem preenchidas e ninguem vencer, da empate.\n\n");
    pausar();
}


void jogarTurno() {
    char escolha;
    int linha, coluna;
    int valido = 0;

    do {
        exibirTabuleiro();
        printf("\n Jogador %c, escolha uma posicao (1-9): ", player);
        scanf(" %c", &escolha);

        for (linha = 0; linha < 3; linha++) {
            for (coluna = 0; coluna < 3; coluna++) {
                if (tabuleiro[linha][coluna] == escolha) {
                    tabuleiro[linha][coluna] = player;
                    valido = 1;
                    break;
                }
            }
            if (valido) break;
        }

        if (!valido) {
            printf("Posicao invalida ou casa ocupada. Escolha outra.\n");
            pausar();
        }

    } while (!valido);
}


void jogar() {
    player = 'X';
    inicializarTabuleiro();

    while (1) {
        jogarTurno();

        if (verificarVitoria()) {
            exibirTabuleiro();
            printf("Parabens! Jogador %c venceu!\n", player);
            break;
        }

        if (verificarEmpate()) {
            exibirTabuleiro();
            printf("Empate! Ninguem venceu.\n");
            break;
        }

        player = (player == 'X') ? 'O' : 'X';
    }

    printf("\nFim de jogo!\n");
    pausar();
}


void limparTela() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void pausar() {
    printf("Pressione Enter para continuar...");
    getchar();
    getchar();
}


int main() {
    int opcao;

    do {
        limparTela();
        printf("=== MENU PRINCIPAL ===\n");
        printf("1. Jogar\n");
        printf("2. Instrucoes\n");
        printf("3. Sair\n");
        printf("Escolha uma opcao: ");

        if (scanf("%d", &opcao) != 1) {
            while (getchar() != '\n'); 
            printf("Entrada invalida! Use apenas numeros.\n");
            pausar();
            continue;
        }

        switch (opcao) {
            case 1:
                jogar();
                break;
            case 2:
                instrucoes();
                break;
            case 3:
                printf("Saindo do jogo...\n");
                break;
            default:
                printf("Opcao invalida! Tente novamente.\n");
                pausar();
        }
    } while (opcao != 3);

    return 0;
}
