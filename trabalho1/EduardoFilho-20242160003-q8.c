#include <stdio.h>
#include <ctype.h>

int main() {
    char tabuleiro[3][3] = {
        {' ', ' ', ' '},
        {' ', ' ', ' '},
        {' ', ' ', ' '}
    };
    
    int jogador = 1; // 1 = X, 2 = O
    int jogadas = 0;
    char linha_char;
    int coluna;
    int ganhou = 0;
    
    printf("JOGO DA VELHA\n\n");
    
    while (jogadas < 9 && !ganhou) {
       
        printf("|   | 1 | 2 | 3 |\n");
        printf("|---|---|---|---|\n");
        printf("| A | %c | %c | %c |\n", tabuleiro[0][0], tabuleiro[0][1], tabuleiro[0][2]);
        printf("| B | %c | %c | %c |\n", tabuleiro[1][0], tabuleiro[1][1], tabuleiro[1][2]);
        printf("| C | %c | %c | %c |\n", tabuleiro[2][0], tabuleiro[2][1], tabuleiro[2][2]);
        
        // Pedir jogada
        printf("\nJogador %d, informe sua jogada (ex: A1): ", jogador);
        scanf(" %c%d", &linha_char, &coluna);
        
       
        int linha;
        switch (toupper(linha_char)) {
            case 'A': linha = 0; break;
            case 'B': linha = 1; break;
            case 'C': linha = 2; break;
            default: linha = -1; break;
        }
        
        
        if (linha < 0 || linha > 2 || coluna < 1 || coluna > 3) {
            printf("Jogada invalida! Use A-C para linha e 1-3 para coluna.\n\n");
            continue;
        }
        
        
        coluna = coluna - 1;
        
        
        if (tabuleiro[linha][coluna] != ' ') {
            printf("Posicao ja ocupada! Escolha outra.\n\n");
            continue;
        }
        
      
        if (jogador == 1) {
            tabuleiro[linha][coluna] = 'X';
        } else {
            tabuleiro[linha][coluna] = 'O';
        }
        
        jogadas++;
        
      
        for (int i = 0; i < 3; i++) {
            if (tabuleiro[i][0] != ' ' && 
                tabuleiro[i][0] == tabuleiro[i][1] && 
                tabuleiro[i][1] == tabuleiro[i][2]) {
                ganhou = 1;
            }
        }
        
       
        for (int j = 0; j < 3; j++) {
            if (tabuleiro[0][j] != ' ' && 
                tabuleiro[0][j] == tabuleiro[1][j] && 
                tabuleiro[1][j] == tabuleiro[2][j]) {
                ganhou = 1;
            }
        }
        
       
        if (tabuleiro[0][0] != ' ' && 
            tabuleiro[0][0] == tabuleiro[1][1] && 
            tabuleiro[1][1] == tabuleiro[2][2]) {
            ganhou = 1;
        }
        
        if (tabuleiro[0][2] != ' ' && 
            tabuleiro[0][2] == tabuleiro[1][1] && 
            tabuleiro[1][1] == tabuleiro[2][0]) {
            ganhou = 1;
        }
        
        
        if (!ganhou) {
            jogador = (jogador == 1) ? 2 : 1;
        }
        
        printf("\n");
    }
    
  
    printf("|   | 1 | 2 | 3 |\n");
    printf("|---|---|---|---|\n");
    printf("| A | %c | %c | %c |\n", tabuleiro[0][0], tabuleiro[0][1], tabuleiro[0][2]);
    printf("| B | %c | %c | %c |\n", tabuleiro[1][0], tabuleiro[1][1], tabuleiro[1][2]);
    printf("| C | %c | %c | %c |\n", tabuleiro[2][0], tabuleiro[2][1], tabuleiro[2][2]);
    
   
    if (ganhou) {
        printf("\nParabens! Jogador %d venceu!\n", jogador);
    } else {
        printf("\nEmpate! Nao houve vencedor.\n");
    }
    
    return 0;
}