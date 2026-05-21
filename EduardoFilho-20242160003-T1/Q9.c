#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

#define TOTAL_NAVIOS 5

int tamanhos_navios[TOTAL_NAVIOS] = {4, 3, 1, 1, 1};

void limparTela() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

int main() {
    char tabuleiro_jogador1[10][10];
    char tabuleiro_jogador2[10][10];
    char tabuleiro_oponente1[10][10];
    char tabuleiro_oponente2[10][10];
    
    int jogador_atual = 1;
    int game_over = 0;
    
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            tabuleiro_jogador1[i][j] = ' ';
            tabuleiro_jogador2[i][j] = ' ';
            tabuleiro_oponente1[i][j] = ' ';
            tabuleiro_oponente2[i][j] = ' ';
        }
    }
    
    printf("=== BATALHA NAVAL ===\n\n");
    
    printf("JOGADOR 1 - Posicione seus navios:\n");
    for (int navio = 0; navio < TOTAL_NAVIOS; navio++) {
        int tamanho = tamanhos_navios[navio];
        int linha, coluna;
        char direcao, linha_char;
        int posicao_valida = 0;
        
        printf("\nNavio %d (tamanho %d):\n", navio + 1, tamanho);
        
        while (!posicao_valida) {
            printf("Seu tabuleiro:\n");
            printf("   A B C D E F G H I J\n");
            for (int i = 0; i < 10; i++) {
                printf("%2d ", i + 1);
                for (int j = 0; j < 10; j++) {
                    if (tabuleiro_jogador1[i][j] == 'N') {
                        printf("[N]");
                    } else {
                        printf("[ ]");
                    }
                }
                printf("\n");
            }
            
            printf("Digite a posicao (ex: A5) e direcao (H para horizontal, V para vertical): ");
            scanf(" %c%d %c", &linha_char, &linha, &direcao);
            
            coluna = toupper(linha_char) - 'A';
            linha = linha - 1;
            
            if (linha < 0 || linha > 9 || coluna < 0 || coluna > 9) {
                printf("Posicao invalida! Use A-J para coluna e 1-10 para linha.\n");
                continue;
            }
            
            direcao = toupper(direcao);
            if (direcao != 'H' && direcao != 'V') {
                printf("Direcao invalida! Use H para horizontal ou V para vertical.\n");
                continue;
            }
            
            posicao_valida = 1;
            if (direcao == 'H') {
                if (coluna + tamanho > 10) {
                    printf("Navio nao cabe na horizontal a partir desta posicao!\n");
                    posicao_valida = 0;
                    continue;
                }
            } else {
                if (linha + tamanho > 10) {
                    printf("Navio nao cabe na vertical a partir desta posicao!\n");
                    posicao_valida = 0;
                    continue;
                }
            }
            
            if (direcao == 'H') {
                for (int j = coluna; j < coluna + tamanho; j++) {
                    if (tabuleiro_jogador1[linha][j] == 'N') {
                        printf("Posicao sobrepoe outro navio!\n");
                        posicao_valida = 0;
                        break;
                    }
                }
            } else {
                for (int i = linha; i < linha + tamanho; i++) {
                    if (tabuleiro_jogador1[i][coluna] == 'N') {
                        printf("Posicao sobrepoe outro navio!\n");
                        posicao_valida = 0;
                        break;
                    }
                }
            }
            
            if (posicao_valida) {
                if (direcao == 'H') {
                    for (int j = coluna; j < coluna + tamanho; j++) {
                        tabuleiro_jogador1[linha][j] = 'N';
                    }
                } else {
                    for (int i = linha; i < linha + tamanho; i++) {
                        tabuleiro_jogador1[i][coluna] = 'N';
                    }
                }
                printf("Navio posicionado com sucesso!\n");
            }
        }
    }
    
    limparTela();
    
    printf("JOGADOR 2 - Posicione seus navios:\n");
    for (int navio = 0; navio < TOTAL_NAVIOS; navio++) {
        int tamanho = tamanhos_navios[navio];
        int linha, coluna;
        char direcao, linha_char;
        int posicao_valida = 0;
        
        printf("\nNavio %d (tamanho %d):\n", navio + 1, tamanho);
        
        while (!posicao_valida) {
            printf("Seu tabuleiro:\n");
            printf("   A B C D E F G H I J\n");
            for (int i = 0; i < 10; i++) {
                printf("%2d ", i + 1);
                for (int j = 0; j < 10; j++) {
                    if (tabuleiro_jogador2[i][j] == 'N') {
                        printf("[N]");
                    } else {
                        printf("[ ]");
                    }
                }
                printf("\n");
            }
            
            printf("Digite a posicao (ex: A5) e direcao (H para horizontal, V para vertical): ");
            scanf(" %c%d %c", &linha_char, &linha, &direcao);
            
            coluna = toupper(linha_char) - 'A';
            linha = linha - 1;
            
            if (linha < 0 || linha > 9 || coluna < 0 || coluna > 9) {
                printf("Posicao invalida! Use A-J para coluna e 1-10 para linha.\n");
                continue;
            }
            
            direcao = toupper(direcao);
            if (direcao != 'H' && direcao != 'V') {
                printf("Direcao invalida! Use H para horizontal ou V para vertical.\n");
                continue;
            }
            
            posicao_valida = 1;
            if (direcao == 'H') {
                if (coluna + tamanho > 10) {
                    printf("Navio nao cabe na horizontal a partir desta posicao!\n");
                    posicao_valida = 0;
                    continue;
                }
            } else {
                if (linha + tamanho > 10) {
                    printf("Navio nao cabe na vertical a partir desta posicao!\n");
                    posicao_valida = 0;
                    continue;
                }
            }
            
            if (direcao == 'H') {
                for (int j = coluna; j < coluna + tamanho; j++) {
                    if (tabuleiro_jogador2[linha][j] == 'N') {
                        printf("Posicao sobrepoe outro navio!\n");
                        posicao_valida = 0;
                        break;
                    }
                }
            } else {
                for (int i = linha; i < linha + tamanho; i++) {
                    if (tabuleiro_jogador2[i][coluna] == 'N') {
                        printf("Posicao sobrepoe outro navio!\n");
                        posicao_valida = 0;
                        break;
                    }
                }
            }
            
            if (posicao_valida) {
                if (direcao == 'H') {
                    for (int j = coluna; j < coluna + tamanho; j++) {
                        tabuleiro_jogador2[linha][j] = 'N';
                    }
                } else {
                    for (int i = linha; i < linha + tamanho; i++) {
                        tabuleiro_jogador2[i][coluna] = 'N';
                    }
                }
                printf("Navio posicionado com sucesso!\n");
            }
        }
    }
    
    printf("\n=== COMECA O JOGO ===\n");
    
    while (!game_over) {
        int linha, coluna;
        char linha_char;
        
        printf("\n=== VEZ DO JOGADOR %d ===\n", jogador_atual);
        
        printf("TABULEIRO DO OPONENTE (seus tiros):\n");
        printf("   A B C D E F G H I J\n");
        for (int i = 0; i < 10; i++) {
            printf("%2d ", i + 1);
            for (int j = 0; j < 10; j++) {
                if (jogador_atual == 1) {
                    printf("[%c]", tabuleiro_oponente1[i][j]);
                } else {
                    printf("[%c]", tabuleiro_oponente2[i][j]);
                }
            }
            printf("\n");
        }
        
        printf("\nSEU TABULEIRO (seus navios):\n");
        printf("   A B C D E F G H I J\n");
        for (int i = 0; i < 10; i++) {
            printf("%2d ", i + 1);
            for (int j = 0; j < 10; j++) {
                if (jogador_atual == 1) {
                    if (tabuleiro_jogador1[i][j] == 'N') {
                        printf("[N]");
                    } else {
                        printf("[%c]", tabuleiro_jogador1[i][j]);
                    }
                } else {
                    if (tabuleiro_jogador2[i][j] == 'N') {
                        printf("[N]");
                    } else {
                        printf("[%c]", tabuleiro_jogador2[i][j]);
                    }
                }
            }
            printf("\n");
        }
        
        int tiro_valido = 0;
        while (!tiro_valido) {
            printf("\nJogador %d, digite a posicao para atirar (ex: A5): ", jogador_atual);
            scanf(" %c%d", &linha_char, &linha);
            
            coluna = toupper(linha_char) - 'A';
            linha = linha - 1;
            
            if (linha < 0 || linha > 9 || coluna < 0 || coluna > 9) {
                printf("Posicao invalida! Use A-J para coluna e 1-10 para linha.\n");
                continue;
            }
            
            tiro_valido = 1;
        }
        
        if (jogador_atual == 1) {
            if (tabuleiro_jogador2[linha][coluna] == 'N') {
                printf("ACERTOU!\n");
                tabuleiro_jogador2[linha][coluna] = '0';
                tabuleiro_oponente1[linha][coluna] = '0';
                
                int navios_afundados = 1;
                for (int i = 0; i < 10 && navios_afundados; i++) {
                    for (int j = 0; j < 10; j++) {
                        if (tabuleiro_jogador2[i][j] == 'N') {
                            navios_afundados = 0;
                            break;
                        }
                    }
                }
                
                if (navios_afundados) {
                    game_over = 1;
                }
            } else {
                printf("AGUA!\n");
                tabuleiro_oponente1[linha][coluna] = 'X';
                if (tabuleiro_jogador2[linha][coluna] == ' ') {
                    tabuleiro_jogador2[linha][coluna] = 'X';
                }
            }
        } else {
            if (tabuleiro_jogador1[linha][coluna] == 'N') {
                printf("ACERTOU!\n");
                tabuleiro_jogador1[linha][coluna] = '0';
                tabuleiro_oponente2[linha][coluna] = '0';
                
                int navios_afundados = 1;
                for (int i = 0; i < 10 && navios_afundados; i++) {
                    for (int j = 0; j < 10; j++) {
                        if (tabuleiro_jogador1[i][j] == 'N') {
                            navios_afundados = 0;
                            break;
                        }
                    }
                }
                
                if (navios_afundados) {
                    game_over = 1;
                }
            } else {
                printf("AGUA!\n");
                tabuleiro_oponente2[linha][coluna] = 'X';
                if (tabuleiro_jogador1[linha][coluna] == ' ') {
                    tabuleiro_jogador1[linha][coluna] = 'X';
                }
            }
        }
        
        if (!game_over) {
            jogador_atual = (jogador_atual == 1) ? 2 : 1;
            printf("\nPressione ENTER para passar para o proximo jogador...");
            getchar();
            getchar();
            limparTela();
        }
    }
    
    printf("\n=== FIM DO JOGO ===\n");
    printf("Jogador %d venceu!\n", jogador_atual);
    printf("Parabens!\n");
    
    return 0;
}