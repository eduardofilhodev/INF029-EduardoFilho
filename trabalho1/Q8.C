#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> 

char tabuleiro[3][3];

// Função para zerar o tabuleiro com espaços vazios
void inicializarTabuleiro() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            tabuleiro[i][j] = ' ';
        }
    }
}


void mostrarTabuleiro() {
    printf("\n  1 2 3\n");
    for (int i = 0; i < 3; i++) {
        // Imprime a letra da linha (A = 65 na tabela ASCII)
        printf("%c %c|%c|%c\n", 'A' + i, tabuleiro[i][0], tabuleiro[i][1], tabuleiro[i][2]);
        if (i < 2) printf("  -+-+-\n");
    }
    printf("\n");
}

// Verifica se alguém ganhou (Retorna 'X', '0' ou ' ' se ninguém ganhou)
char verificarVencedor() {
    // Verifica Linhas e Colunas
    for (int i = 0; i < 3; i++) {
        if (tabuleiro[i][0] == tabuleiro[i][1] && tabuleiro[i][1] == tabuleiro[i][2] && tabuleiro[i][0] != ' ')
            return tabuleiro[i][0];
        if (tabuleiro[0][i] == tabuleiro[1][i] && tabuleiro[1][i] == tabuleiro[2][i] && tabuleiro[0][i] != ' ')
            return tabuleiro[0][i];
    }
    // Verifica Diagonais
    if (tabuleiro[0][0] == tabuleiro[1][1] && tabuleiro[1][1] == tabuleiro[2][2] && tabuleiro[0][0] != ' ')
        return tabuleiro[0][0];
    if (tabuleiro[0][2] == tabuleiro[1][1] && tabuleiro[1][1] == tabuleiro[2][0] && tabuleiro[0][2] != ' ')
        return tabuleiro[0][2];
        
    return ' '; // Ninguém ganhou ainda
}

int main() {
    int jogadas = 0;
    int jogadorAtual = 1; // 1 para X, 2 para 0
    char marca;
    char entrada[5];
    int linha, coluna;
    char vencedor = ' ';

    inicializarTabuleiro();

    printf("=== JOGO DA VELHA ===\n");

    while (jogadas < 9 && vencedor == ' ') {
        mostrarTabuleiro();
        marca = (jogadorAtual == 1) ? 'X' : '0';

        printf("Jogador %d, informe sua jogada (ex: B2): ", jogadorAtual);
        scanf("%s", entrada);

        // Transformando o texto em índices (ex: 'B' - 'A' = 1)
        linha = toupper(entrada[0]) - 'A';
        coluna = entrada[1] - '1'; // '1' - '1' = 0, '2' - '1' = 1...

        // Validação da jogada
        if (linha >= 0 && linha < 3 && coluna >= 0 && coluna < 3 && tabuleiro[linha][coluna] == ' ') {
            tabuleiro[linha][coluna] = marca;
            jogadas++;
            vencedor = verificarVencedor();
            
            // Troca o turno
            jogadorAtual = (jogadorAtual == 1) ? 2 : 1; 
        } else {
            printf("\n[!] Jogada invalida! Tente novamente.\n");
        }
    }

    mostrarTabuleiro();

    if (vencedor != ' ') {
        // Como o turno troca no fim do loop, quem ganhou foi o turno anterior
        int quemGanhou = (jogadorAtual == 1) ? 2 : 1;
        printf(">>> Parabens! O Jogador %d venceu! <<<\n", quemGanhou);
    } else {
        printf(">>> Deu velha! Empate. <<<\n");
    }

    return 0;
}