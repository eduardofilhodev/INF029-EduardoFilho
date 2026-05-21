#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>


int NUM_NAVIOS = 5; 
int TAMANHO_DOS_NAVIOS[] = {4, 3, 1, 1, 1}; // 1 de 4, 1 de 3, 3 de 1


char AGUA = ' ';
char NAVIO = 'N';
char ABATIDO = '0';
char ERRO = 'X';

// (cada jogador tem seu mapa e vida)
typedef struct {
    char mapa[10][10];
    char telaOponente[10][10]; 
    int naviosRestantes;
} Jogador;

void inicializarMapas(Jogador *j) {
    for (int r = 0; r < 10; r++) {
        for (int c = 0; c < 10; c++) {
            j->mapa[r][c] = AGUA;
            j->telaOponente[r][c] = AGUA;
        }
    }
    
    j->naviosRestantes = 0;
    for(int i = 0; i < NUM_NAVIOS; i++){
        j->naviosRestantes += TAMANHO_DOS_NAVIOS[i];
    }
}

void mostrarMapa(char mapa[10][10], const char* titulo) {
    printf("\n=== %s ===\n", titulo);
    printf("   0 1 2 3 4 5 6 7 8 9\n");
    for (int r = 0; r < 10; r++) {
        printf("%c  ", 'A' + r);
        for (int c = 0; c < 10; c++) {
            printf("[%c]", mapa[r][c]);
        }
        printf("\n");
    }
}


void posicionarNavios(Jogador *j, int numJogador) {
    char entrada[5];
    int linha, coluna;

    printf("\n>>> JOGADOR %d, POSICIONE SEUS NAVIOS <<<\n", numJogador);
    
    for (int i = 0; i < NUM_NAVIOS; i++) {
        int tamanho = TAMANHO_DOS_NAVIOS[i];
        int posicionado = 0;

        while (!posicionado) {
            mostrarMapa(j->mapa, "SEU MAPA ATUAL");
            printf("Posicione um navio de tamanho %d.\n", tamanho);
            printf("Informe a coordenada inicial (ex: A0): ");
            scanf("%s", entrada);

            linha = toupper(entrada[0]) - 'A';
            coluna = entrada[1] - '0';

            // Verifica se a jogada cabe no mapa
            if (linha >= 0 && linha < 10 && coluna >= 0 && coluna + tamanho <= 10) {
                // Verifica se já tem navio no caminho
                int espacoLivre = 1;
                for (int k = 0; k < tamanho; k++) {
                    if (j->mapa[linha][coluna + k] != AGUA) espacoLivre = 0;
                }

                if (espacoLivre) {
                    for (int k = 0; k < tamanho; k++) {
                        j->mapa[linha][coluna + k] = NAVIO;
                    }
                    posicionado = 1;
                } else {
                    printf("[!] Espaco ocupado por outro navio!\n");
                }
            } else {
                printf("[!] Coordenada invalida ou navio sai do mapa!\n");
            }
        }
    }
   
    printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n"); 
}

int main() {
    Jogador j1, j2;
    inicializarMapas(&j1);
    inicializarMapas(&j2);

    posicionarNavios(&j1, 1);
    posicionarNavios(&j2, 2);

    int turno = 1;
    char entrada[5];
    int linha, coluna;

    printf("\n>>> QUE COMECE A BATALHA! <<<\n");

    
    while (j1.naviosRestantes > 0 && j2.naviosRestantes > 0) {
        Jogador *atacante = (turno == 1) ? &j1 : &j2;
        Jogador *defensor = (turno == 1) ? &j2 : &j1;

        printf("\n==================================\n");
        printf("Vez do JOGADOR %d atirar!\n", turno);
        
        
        mostrarMapa(defensor->telaOponente, "MAPA DE TIROS (INIMIGO)");
        mostrarMapa(atacante->mapa, "SEU MAPA (DEFESA)");

        printf("Informe a coordenada do tiro (ex: A0): ");
        scanf("%s", entrada);

        linha = toupper(entrada[0]) - 'A';
        coluna = entrada[1] - '0';

        if (linha >= 0 && linha < 10 && coluna >= 0 && coluna < 10) {
            
            
            if (defensor->mapa[linha][coluna] == NAVIO) {
                printf("\n>>> BOOM! Voce acertou um navio! <<<\n");
                // Atualiza o mapa original e a tela do oponente
                defensor->mapa[linha][coluna] = ABATIDO;
                defensor->telaOponente[linha][coluna] = ABATIDO;
                defensor->naviosRestantes--;
                
            } else if (defensor->mapa[linha][coluna] == AGUA) {
                printf("\n>>> SPLASH! Tiro na agua! <<<\n");
                defensor->mapa[linha][coluna] = ERRO;
                defensor->telaOponente[linha][coluna] = ERRO;
                
            } else {
                printf("\n[!] Voce ja atirou nessa posicao!\n");
                continue; 
            }

            turno = (turno == 1) ? 2 : 1; 
        } else {
            printf("\n[!] Coordenada invalida!\n");
        }
    }

    int ganhador = (j1.naviosRestantes == 0) ? 2 : 1;
    printf("\n==================================\n");
    printf(">>> FIM DE JOGO! O JOGADOR %d VENCEU! <<<\n", ganhador);

    return 0;
}