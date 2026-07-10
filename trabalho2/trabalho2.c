#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "trabalho2.h"

#define TAM 10

typedef struct {
    int *elementos;
    int quantidadeOcupada;
    int tamanhoAlocado;
} EstruturaAuxiliar;

EstruturaAuxiliar *vetorPrincipal[TAM];

int posicaoValida(int posicao) {
    return posicao >= 1 && posicao <= TAM;
}

int compararInteiros(const void *a, const void *b) {
    int valorA = *(const int *) a;
    int valorB = *(const int *) b;

    if (valorA < valorB) {
        return -1;
    }

    if (valorA > valorB) {
        return 1;
    }

    return 0;
}

int totalElementosOcupados() {
    int total = 0;

    for (int i = 0; i < TAM; i++) {
        if (vetorPrincipal[i] != NULL) {
            total += vetorPrincipal[i]->quantidadeOcupada;
        }
    }

    return total;
}

void inicializar() {
    for (int i = 0; i < TAM; i++) {
        vetorPrincipal[i] = NULL;
    }
}

void finalizar() {
    for (int i = 0; i < TAM; i++) {
        if (vetorPrincipal[i] != NULL) {
            free(vetorPrincipal[i]->elementos);
            free(vetorPrincipal[i]);
            vetorPrincipal[i] = NULL;
        }
    }
}

void dobrar(int *x) {
    if (x != NULL) {
        *x *= 2;
    }
}

int criarEstruturaAuxiliar(int posicao, int tamanho) {
    if (!posicaoValida(posicao)) {
        return POSICAO_INVALIDA;
    }

    if (tamanho < 1) {
        return TAMANHO_INVALIDO;
    }

    int indice = posicao - 1;

    if (vetorPrincipal[indice] != NULL) {
        return JA_TEM_ESTRUTURA_AUXILIAR;
    }

    EstruturaAuxiliar *nova = (EstruturaAuxiliar *) malloc(sizeof(EstruturaAuxiliar));

    if (nova == NULL) {
        return SEM_ESPACO_DE_MEMORIA;
    }

    nova->elementos = (int *) malloc(tamanho * sizeof(int));

    if (nova->elementos == NULL) {
        free(nova);
        return SEM_ESPACO_DE_MEMORIA;
    }

    nova->quantidadeOcupada = 0;
    nova->tamanhoAlocado = tamanho;
    vetorPrincipal[indice] = nova;

    return SUCESSO;
}

int inserirNumeroEmEstrutura(int posicao, int valor) {
    if (!posicaoValida(posicao)) {
        return POSICAO_INVALIDA;
    }

    EstruturaAuxiliar *auxiliar = vetorPrincipal[posicao - 1];

    if (auxiliar == NULL) {
        return SEM_ESTRUTURA_AUXILIAR;
    }

    if (auxiliar->quantidadeOcupada >= auxiliar->tamanhoAlocado) {
        return SEM_ESPACO;
    }

    auxiliar->elementos[auxiliar->quantidadeOcupada] = valor;
    auxiliar->quantidadeOcupada++;

    return SUCESSO;
}

int excluirNumeroDoFinaldaEstrutura(int posicao) {
    if (!posicaoValida(posicao)) {
        return POSICAO_INVALIDA;
    }

    EstruturaAuxiliar *auxiliar = vetorPrincipal[posicao - 1];

    if (auxiliar == NULL) {
        return SEM_ESTRUTURA_AUXILIAR;
    }

    if (auxiliar->quantidadeOcupada == 0) {
        return ESTRUTURA_AUXILIAR_VAZIA;
    }

    auxiliar->quantidadeOcupada--;

    return SUCESSO;
}

int excluirNumeroEspecificoDeEstrutura(int posicao, int valor) {
    if (!posicaoValida(posicao)) {
        return POSICAO_INVALIDA;
    }

    EstruturaAuxiliar *auxiliar = vetorPrincipal[posicao - 1];

    if (auxiliar == NULL) {
        return SEM_ESTRUTURA_AUXILIAR;
    }

    if (auxiliar->quantidadeOcupada == 0) {
        return ESTRUTURA_AUXILIAR_VAZIA;
    }

    for (int i = 0; i < auxiliar->quantidadeOcupada; i++) {
        if (auxiliar->elementos[i] == valor) {
            for (int j = i; j < auxiliar->quantidadeOcupada - 1; j++) {
                auxiliar->elementos[j] = auxiliar->elementos[j + 1];
            }

            auxiliar->quantidadeOcupada--;
            return SUCESSO;
        }
    }

    return NUMERO_INEXISTENTE;
}

int getDadosEstruturaAuxiliar(int posicao, int vetorAux[]) {
    if (!posicaoValida(posicao)) {
        return POSICAO_INVALIDA;
    }

    EstruturaAuxiliar *auxiliar = vetorPrincipal[posicao - 1];

    if (auxiliar == NULL) {
        return SEM_ESTRUTURA_AUXILIAR;
    }

    for (int i = 0; i < auxiliar->quantidadeOcupada; i++) {
        vetorAux[i] = auxiliar->elementos[i];
    }

    return SUCESSO;
}

int getDadosOrdenadosEstruturaAuxiliar(int posicao, int vetorAux[]) {
    int resultado = getDadosEstruturaAuxiliar(posicao, vetorAux);

    if (resultado != SUCESSO) {
        return resultado;
    }

    qsort(vetorAux, vetorPrincipal[posicao - 1]->quantidadeOcupada, sizeof(int), compararInteiros);

    return SUCESSO;
}

int getDadosDeTodasEstruturasAuxiliares(int vetorAux[]) {
    int k = 0;

    if (totalElementosOcupados() == 0) {
        return TODAS_ESTRUTURAS_AUXILIARES_VAZIAS;
    }

    for (int i = 0; i < TAM; i++) {
        if (vetorPrincipal[i] == NULL) {
            continue;
        }

        for (int j = 0; j < vetorPrincipal[i]->quantidadeOcupada; j++) {
            vetorAux[k] = vetorPrincipal[i]->elementos[j];
            k++;
        }
    }

    return SUCESSO;
}

int getDadosOrdenadosDeTodasEstruturasAuxiliares(int vetorAux[]) {
    int resultado = getDadosDeTodasEstruturasAuxiliares(vetorAux);

    if (resultado != SUCESSO) {
        return resultado;
    }

    qsort(vetorAux, totalElementosOcupados(), sizeof(int), compararInteiros);

    return SUCESSO;
}

int modificarTamanhoEstruturaAuxiliar(int posicao, int novoTamanho) {
    if (!posicaoValida(posicao)) {
        return POSICAO_INVALIDA;
    }

    EstruturaAuxiliar *auxiliar = vetorPrincipal[posicao - 1];

    if (auxiliar == NULL) {
        return SEM_ESTRUTURA_AUXILIAR;
    }

    int tamanhoFinal = auxiliar->tamanhoAlocado + novoTamanho;

    if (tamanhoFinal < 1) {
        return NOVO_TAMANHO_INVALIDO;
    }

    int *novoVetor = (int *) realloc(auxiliar->elementos, tamanhoFinal * sizeof(int));

    if (novoVetor == NULL) {
        return SEM_ESPACO_DE_MEMORIA;
    }

    auxiliar->elementos = novoVetor;
    auxiliar->tamanhoAlocado = tamanhoFinal;

    if (auxiliar->quantidadeOcupada > tamanhoFinal) {
        auxiliar->quantidadeOcupada = tamanhoFinal;
    }

    return SUCESSO;
}

int getQuantidadeElementosEstruturaAuxiliar(int posicao) {
    if (!posicaoValida(posicao)) {
        return POSICAO_INVALIDA;
    }

    EstruturaAuxiliar *auxiliar = vetorPrincipal[posicao - 1];

    if (auxiliar == NULL) {
        return SEM_ESTRUTURA_AUXILIAR;
    }

    return auxiliar->quantidadeOcupada;
}

No *montarListaEncadeadaComCabecote() {
    No *cabecote = (No *) malloc(sizeof(No));

    if (cabecote == NULL) {
        return NULL;
    }

    cabecote->conteudo = 0;
    cabecote->prox = NULL;

    No *fim = cabecote;

    for (int i = 0; i < TAM; i++) {
        if (vetorPrincipal[i] == NULL) {
            continue;
        }

        for (int j = 0; j < vetorPrincipal[i]->quantidadeOcupada; j++) {
            No *novo = (No *) malloc(sizeof(No));

            if (novo == NULL) {
                destruirListaEncadeadaComCabecote(&cabecote);
                return NULL;
            }

            novo->conteudo = vetorPrincipal[i]->elementos[j];
            novo->prox = NULL;
            fim->prox = novo;
            fim = novo;
        }
    }

    return cabecote;
}

void getDadosListaEncadeadaComCabecote(No *inicio, int vetorAux[]) {
    if (inicio == NULL) {
        return;
    }

    No *atual = inicio->prox;
    int i = 0;

    while (atual != NULL) {
        vetorAux[i] = atual->conteudo;
        atual = atual->prox;
        i++;
    }
}

void destruirListaEncadeadaComCabecote(No **inicio) {
    if (inicio == NULL || *inicio == NULL) {
        return;
    }

    No *atual = *inicio;

    while (atual != NULL) {
        No *proximo = atual->prox;
        free(atual);
        atual = proximo;
    }

    *inicio = NULL;
}
