#include <stdio.h>
#include <stdlib.h>

#define TAM 3
char tabuleiro[TAM][TAM];
char player = 'X';
void limparTela() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}
void pausar() {
    printf("Pressione Enter para continuar...");
    while (getchar() != '\n'); 
}
void inicializarTabuleiro() {
    for (int i = 0; i < TAM; i++)
        for (int j = 0; j < TAM; j++)
            tabuleiro[i][j] = '1' + (i * TAM + j);
}
void exibirTabuleiro() {
    limparTela();
    printf("\n      1   2   3\n\n");
    for (int i = 0; i < TAM; i++) {
        printf(" %d    %c | %c | %c \n", i + 1, tabuleiro[i][0], tabuleiro[i][1], tabuleiro[i][2]);
        if (i < TAM - 1)
            printf("     ---|---|---\n");
    }
    printf("\n");
}
int verificarVitoria() {
    for (int i = 0; i < TAM; i++) {
        if (tabuleiro[i][0] == tabuleiro[i][1] && tabuleiro[i][1] == tabuleiro[i][2]) return 1;
        if (tabuleiro[0][i] == tabuleiro[1][i] && tabuleiro[1][i] == tabuleiro[2][i]) return 1;
    }
    if (tabuleiro[0][0] == tabuleiro[1][1] && tabuleiro[1][1] == tabuleiro[2][2]) return 1;
    if (tabuleiro[0][2] == tabuleiro[1][1] && tabuleiro[1][1] == tabuleiro[2][0]) return 1;
    return 0;
}
int verificarEmpate() {
    for (int i = 0; i < TAM; i++)
        for (int j = 0; j < TAM; j++)
            if (tabuleiro[i][j] != 'X' && tabuleiro[i][j] != 'O')
                return 0;
    return 1;
}
void instrucoes() {
    limparTela();
    printf("=== INSTRUCOES DO JOGO ===\n\n");
    printf("1. Dois jogadores alternam jogadas.\n");
    printf("2. Escolha uma posicao de 1 a 9 (uma por vez).\n");
    printf("3. Vence quem alinhar 3 simbolos em linha, coluna ou diagonal.\n");
    printf("4. Se todas as casas forem preenchidas sem vencedor, ocorre empate.\n\n");
    pausar();
}
void jogarTurno() {
    char escolha;
    int linha, coluna;
    int valido = 0;
    do {
        exibirTabuleiro();
        printf("Jogador %c, escolha uma posicao (1-9): ", player);
        escolha = getchar();
        while (getchar() != '\n'); 
        if (escolha < '1' || escolha > '9') {
            printf("Entrada invalida! Digite um numero de 1 a 9.\n");
            pausar();
            continue;
        }
        int pos = escolha - '1';
        linha = pos / TAM;
        coluna = pos % TAM;
        if (tabuleiro[linha][coluna] != 'X' && tabuleiro[linha][coluna] != 'O') {
            tabuleiro[linha][coluna] = player;
            valido = 1;
        } else {
            printf("Essa posicao ja foi ocupada. Escolha outra.\n");
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
        while (getchar() != '\n');
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
