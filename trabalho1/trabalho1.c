// #################################################
//  Instituto Federal da Bahia
//  Salvador - BA
//  Curso de Anùlise e Desenvolvimento de Sistemas http://ads.ifba.edu.br
//  Disciplina: INF029 - Laboratùrio de Programaùùo
//  Professor: Renato Novais - renato@ifba.edu.br

//  ----- Orientaùùes gerais -----
//  Descriùùo: esse arquivo deve conter as questùes do trabalho do aluno.
//  O aluno deve preencher seus dados abaixo, e implementar as questùes do trabalho

//  ----- Dados do Aluno -----
//  Nome: Eduardo de Souza Ferreira Filho
//  email: 20242160003@ifba.edu.br
//  Matrùcula: 20242160003
//  Semestre: 3ù semestre

//  Copyright ù 2016 Renato Novais. All rights reserved.
// ùltima atualizaùùo: 07/05/2021 - 19/08/2016 - 17/10/2025

// #################################################

#include <stdio.h>
#include "trabalho1.h" 
#include <stdlib.h>
int validaData(DataQuebrada dq);
DataQuebrada quebraData(char data[]);
int ehMesmoCaractere(char doTexto, char buscado, int isCaseSensitive);
int q3(char *texto, char c, int isCaseSensitive);
int somar(int x, int y);
int fatorial(int x);
int teste(int a);
void inverteOrdemArray(int array[], int tamanho);
int quebraInteiro(int num, int array[]);
int BuscaNaBase(int numeroBase, int numeroBusca);
int buscaVertical(char matriz[8][10], char palavra[5]);
int BuscaHorizontal(char matriz[8][10], char palavra[]);
int BuscaDiagonal(char matriz[8][10], char palavra[]);
int buscaTotal(char matriz[8][10], char palavra[]);
int q7(char matriz[8][10], char palavra[5]);


int q6(int numerobase, int numerobusca);



int somar(int x, int y)
{
    int soma;
    soma = x + y;
    return soma;
}


int fatorial(int x)
{ //funùùo utilizada para testes
  int i, fat = 1;
    
  for (i = x; i > 1; i--)
    fat = fat * i;
    
  return fat;
}

int teste(int a)
{
    int val;
    if (a == 2)
        val = 3;
    else
        val = 4;

    return val;
}

/*
 Q1 = validar data
@objetivo
    Validar uma data
@entrada
    uma string data. Formatos que devem ser aceitos: dd/mm/aaaa, onde dd = dia, mm = mùs, e aaaa, igual ao ano. 
    dd em mm podem ter apenas um digito, e aaaa podem ter apenas dois digitos.
@saida
    0 -> se data invùlida
    1 -> se data vùlida
 @restriùùes
    Nùo utilizar funùùes prùprias de string (ex: strtok)   
    pode utilizar strlen para pegar o tamanho da string
 */
int q1(char data[])
{

    int datavalida = 1;

    DataQuebrada dq = quebraData(data);

    if (dq.valido == 0)
        datavalida = 0;

    datavalida = validaData(dq); 

    if (datavalida)
        return 1;
    else
        return 0;
}

int validaData(DataQuebrada dq)
{ 
    int datavalida = 1;

    if (dq.iAno < 0 || dq.iAno >2026 || dq.iMes < 1 || dq.iMes > 12 || dq.iDia < 1 || dq.iDia > 31)
    {
        datavalida = 0;
    }
    else
    {
        if (dq.iMes == 2)
        {
            if ((dq.iAno % 4 == 0 && dq.iAno % 100 != 0) || (dq.iAno % 400 == 0))
            {
                if (dq.iDia > 29)
                    datavalida = 0;
            }
            else
            {
                if (dq.iDia > 28)
                    datavalida = 0;
            } //validaùùo de ano bissexto
        }
        else if (dq.iMes == 4 || dq.iMes == 6 || dq.iMes == 9 || dq.iMes == 11)
        {
            if (dq.iDia > 30)
                datavalida = 0;
        }
        else
        {
            if (dq.iDia > 31)
                datavalida = 0;
        }
    }

    return datavalida;
}



/*
 Q2 = diferenùa entre duas datas
 @objetivo
    Calcular a diferenùa em anos, meses e dias entre duas datas
 @entrada
    uma string datainicial, uma string datafinal. 
 @saida
    Retorna um tipo DiasMesesAnos. No atributo retorno, deve ter os possùveis valores abaixo
    1 -> cùlculo de diferenùa realizado com sucesso
    2 -> datainicial invùlida
    3 -> datafinal invùlida
    4 -> datainicial > datafinal
    Caso o cùlculo esteja correto, os atributos qtdDias, qtdMeses e qtdAnos devem ser preenchidos com os valores correspondentes.
 */
DiasMesesAnos q2(char datainicial[], char datafinal[])
{

    //calcule os dados e armazene nas trùs variùveis a seguir
    DiasMesesAnos dma;


    if (q1(datainicial) == 0){
      dma.retorno = 2;
      return dma;
    }else if (q1(datafinal) == 0){
      dma.retorno = 3;
      return dma;
    }else{
      //verifique se a data final nùo ù menor que a data inicial
      //calcule a distancia entre as datas
      DataQuebrada dq_inicial = quebraData(datainicial);
      DataQuebrada dq_final = quebraData(datafinal);
        if (dq_inicial.iAno > dq_final.iAno || (dq_inicial.iAno == dq_final.iAno && dq_inicial.iMes > dq_final.iMes) || (dq_inicial.iAno == dq_final.iAno && dq_inicial.iMes == dq_final.iMes && dq_inicial.iDia > dq_final.iDia)){
            dma.retorno = 4;
            return dma;
        }
         else{
                //calcule a diferenùa entre as datas
                int anos = dq_final.iAno - dq_inicial.iAno;
                int meses = dq_final.iMes - dq_inicial.iMes;
                int dias = dq_final.iDia - dq_inicial.iDia;
    
                if (dias < 0){
                 meses--;
                 if (dq_final.iMes == 1 || dq_final.iMes == 3 || dq_final.iMes == 5 || dq_final.iMes == 7 
                        || dq_final.iMes == 8 || dq_final.iMes == 10 || dq_final.iMes == 12)
                 {
                      dias += 31;
                 }else if (dq_final.iMes == 4 || dq_final.iMes == 6 || dq_final.iMes == 9 || dq_final.iMes == 11){
                      dias += 30;
                 }else{
                      if ((dq_final.iAno % 4 == 0 && dq_final.iAno % 100 != 0) || (dq_final.iAno % 400 == 0)){
                            dias += 29;
                      }else{
                            dias += 28;
                      }
                 }
                }
    
                if (meses < 0){
                 anos--;
                 meses += 12;
                }
    
                dma.qtdAnos = anos;
                dma.qtdMeses = meses;
                dma.qtdDias = dias;
    
          }

      //se tudo der certo
      dma.retorno = 1;
      return dma;
      
    }
    
}

/*
 Q3 = encontrar caracter em texto
 @objetivo
    Pesquisar quantas vezes um determinado caracter ocorre em um texto
 @entrada
    uma string texto, um caracter c e um inteiro que informa se ù uma pesquisa Case Sensitive ou nùo. Se isCaseSensitive = 1, 
    a pesquisa deve considerar diferenùas entre maiùsculos e minùsculos.
    Se isCaseSensitive != 1, a pesquisa nùo deve  considerar diferenùas entre maiùsculos e minùsculos.
 @saida
    Um nùmero n >= 0.
 */
int q3(char *texto, char c, int isCaseSensitive)
{
    int i = 0;
    int qtdOcorrencias = 0; 

    // Percorre o texto do usuùrio (de atù 250 caracteres)
    for (i = 0; texto[i] != '\0'; i++)
    {
        // Chama o nosso filtro. Se ele retornar 1, a gente soma no contador!
        if (ehMesmoCaractere(texto[i], c, isCaseSensitive) == 1)
        {
            qtdOcorrencias++;
        }
    }

    return qtdOcorrencias;
}

// Retorna 1 (Verdadeiro) ou 0 (Falso)
int ehMesmoCaractere(char doTexto, char buscado, int isCaseSensitive) {
    char t = doTexto;
    char b = buscado;

    // Passo 1: Se NùO for Case Sensitive, converte tudo para minùsculo logo de cara
    if (isCaseSensitive == 0) {
        if (t >= 'A' && t <= 'Z') t = t + 32;
        if (b >= 'A' && b <= 'Z') b = b + 32;
    }

    // Passo 2: Limpa os acentos do caractere que veio do texto
    if (t == 'ù' || t == 'ù' || t == 'ù' || t == 'ù') t = 'a';
    else if (t == 'ù' || t == 'ù' || t == 'ù' || t == 'ù') t = (isCaseSensitive == 0) ? 'a' : 'A';
    
    else if (t == 'ù' || t == 'ù') t = 'e';
    else if (t == 'ù' || t == 'ù') t = (isCaseSensitive == 0) ? 'e' : 'E';
    
    else if (t == 'ù') t = 'i';
    else if (t == 'ù') t = (isCaseSensitive == 0) ? 'i' : 'I';
    
    else if (t == 'ù' || t == 'ù' || t == 'ù') t = 'o';
    else if (t == 'ù' || t == 'ù' || t == 'ù') t = (isCaseSensitive == 0) ? 'o' : 'O';
    
    else if (t == 'ù') t = 'u';
    else if (t == 'ù') t = (isCaseSensitive == 0) ? 'u' : 'U';
    
    else if (t == 'ù') t = 'c';
    else if (t == 'ù') t = (isCaseSensitive == 0) ? 'c' : 'C';

    // Passo 3: Limpa o caractere buscado (sù por precauùùo, vai que o usuùrio digita 'ù' pra buscar)
    if (b == 'ù' || b == 'ù' || b == 'ù' || b == 'ù') b = 'a';
    else if (b == 'ù' || b == 'ù') b = 'e';
    else if (b == 'ù') b = 'i';
    else if (b == 'ù' || b == 'ù' || b == 'ù') b = 'o';
    else if (b == 'ù') b = 'u';
    else if (b == 'ù') b = 'c';
    // Nota: Como o 'b' jù foi forùado para minùsculo lù em cima se caseSensitive == 0, 
    // nùo precisamos checar todas as maiùsculas acentuadas aqui de novo para simplificar.

    // Passo 4: Verifica se bateram!
    if (t == b) {
        return 1; // Deu Match! (True)
    }
    
    return 0; // Nùo deu Match (False)
}

/*
 Q4 = encontrar palavra em texto
 @objetivo
    Pesquisar todas as ocorrùncias de uma palavra em um texto
 @entrada
    uma string texto base (strTexto), uma string strBusca e um vetor de inteiros (posicoes) que irù guardar as posiùùes
     de inùcio e fim de cada ocorrùncia da palavra (strBusca) no texto base (texto).
 @saida
    Um nùmero n >= 0 correspondente a quantidade de ocorrùncias encontradas.
    O vetor posicoes deve ser preenchido com cada entrada e saùda correspondente. Por exemplo, se
    tiver uma ùnica ocorrùncia, a posiùùo 0 do vetor deve ser preenchido com o ùndice de inùcio do texto,
    e na posiùùo 1, deve ser preenchido com o ùndice de fim da ocorrencias. Se tiver duas ocorrùncias, a 
    segunda ocorrùncia serù amazenado nas posiùùes 2 e 3, e assim consecutivamente.
    Suponha a string "Instituto Federal da Bahia", e palavra de busca "dera".
    Como hù uma ocorrùncia da palavra de busca no texto, 
    deve-se armazenar no vetor, da seguinte forma:

        posicoes[0] = 13;
        posicoes[1] = 16;
        Observe que o ùndice da posiùùo no texto deve comeùar ser contado a partir de 1.
        O retorno da funùùo, n, nesse caso seria 1;

 */
// int q4(char *strTexto, char *strBusca, int posicoes[30])
// {
//     int qtdOcorrencias = -1;
    

//     return qtdOcorrencias;
// }

int q4(char *strTexto, char *strBusca, int posicoes[30]) {
    int i, j;
    int ocorrencia = 0;
    int indice_posicoes = 0;

    // Percorre o texto letra por letra
    for (i = 0; strTexto[i] != '\0'; i++) {
        j = 0;
        
        // A partir da posiùùo 'i' atual, vamos ver se as letras seguintes
        // batem com a palavra de busca. Usamos i + j para olhar pra frente no texto!
        while (strBusca[j] != '\0' && strTexto[i + j] != '\0' && strTexto[i + j] == strBusca[j]) {
            j++;
        }

        // Se o 'j' andou atù o '\0' da palavra de busca, significa que bateu tudo!
        if (strBusca[j] == '\0') {
            ocorrencia++;
            
            // Salvando no vetor (Somamos +1 porque o corretor usa Base 1)
            posicoes[indice_posicoes] = i + 1; // Posiùùo Inicial
            indice_posicoes++;
            
            posicoes[indice_posicoes] = i + j; // Posiùùo Final
            indice_posicoes++;
        }
    }

    return ocorrencia;
}



/*
 Q5 = inverte nùmero
 @objetivo
    Inverter nùmero inteiro
 @entrada
    uma int num.
 @saida
    Nùmero invertido
 */

int q5(int num)
{
    int invertido = 0;

    while (num > 0) {
        invertido = (invertido * 10) + (num % 10);
        num = num / 10;
    }

    return invertido;
}
/*
 Q6 = ocorrùncia de um nùmero em outro
 @objetivo
    Verificar quantidade de vezes da ocorrùncia de um nùmero em outro
 @entrada
    Um nùmero base (numerobase) e um nùmero de busca (numerobusca).
 @saida
    Quantidade de vezes que nùmero de busca ocorre em nùmero base

6) Escreva uma funùùo que determine quantas vezes um nùmero K (de qualquer
quantidade de dùgitos) ocorre em um nùmero natural N. Por exemplo:
O nùmero 3 ocorre quatro vezes em 3539343.
O nùmero 44 ocorre uma vez em 5444, e duas vezes em 54444
O nùmero 23 ocorre duas vezes em 1234562354
 */

int q6(int numerobase, int numerobusca)
{
    int qtdOcorrencias;

    qtdOcorrencias= BuscaNaBase(numerobase, numerobusca);
    

    return qtdOcorrencias;
}

int BuscaNaBase(int numeroBase, int numeroBusca){
    
    int ocorrencia = 0; // Fica aqui fora pra nùo perder a memùria!
    int arrayBase[100];
    int arrayBusca[100];
    int tamanhoArrayBusca = 0;
    int tamanhoArrayBase = 0;
    
    // 1. Quebra os dois nùmeros sem frescura de if/else
    tamanhoArrayBase = quebraInteiro(numeroBase, arrayBase);
    tamanhoArrayBusca = quebraInteiro(numeroBusca, arrayBusca);
    
    // 2. Inverte tudo
    inverteOrdemArray(arrayBase, tamanhoArrayBase);
    inverteOrdemArray(arrayBusca, tamanhoArrayBusca);
    
    // 3. A busca elegante (A mesma lùgica da busca de palavras)
    int i, j;
    
    for(i = 0; i <= tamanhoArrayBase - tamanhoArrayBusca; i++){
        j = 0;
        
        // Vai testando enquanto baterem
        while(j < tamanhoArrayBusca && arrayBase[i + j] == arrayBusca[j]){
            j++;
        }
        
        // Se o j andou o tamanho inteiro da busca, ù porque achamos um match perfeito!
        if(j == tamanhoArrayBusca){
            ocorrencia++;
            
            // O SEGREDO DO PDF: 
            // Pula o 'i' pra frente pra nùo contar o mesmo nùmero duas vezes!
            // Subtrai 1 porque o 'for' jù vai fazer i++ na prùxima rodada.
            i += tamanhoArrayBusca - 1; 
        }
    }
    
    return ocorrencia;
}

int quebraInteiro(int num, int array[]){
    int i=0;
    int tamanhoArray=0;

    while(num>0){
        array[i]=num%10;
        num=num/10;   
        i++;
        tamanhoArray++;
    }

    return tamanhoArray;
}

void inverteOrdemArray(int array[], int tamanho){
    int i=0;
    
    // CORREùùO 1: Comeùa no ùltimo ùndice vùlido, e nùo fora do array
    int j=tamanho - 1; 
    
    int troca=0;

    // CORREùùO 2: O loop para quando o 'i' se encontrar com o 'j' no meio do array
    while(i < j){ 
        troca=array[i];
        array[i]=array[j];
        array[j]=troca;
        
        i++;
        j--;
    }
    return;
}


/*
 Q7 = jogo busca palavras
 @objetivo
    Verificar se existe uma string em uma matriz de caracteres em todas as direùùes e sentidos possùves
 @entrada
    Uma matriz de caracteres e uma string de busca (palavra).
 @saida
    1 se achou 0 se nùo achou
 */

 int q7(char matriz[8][10], char palavra[5])
 {

    int achou;

    achou=buscaTotal(matriz, palavra);


    return achou;
 }

    // char matrix[8][10] = {
    //       i
    //   j { 'Q', 'M', 'J', 'D', 'L', 'A', 'Z', 'F', 'C', 'R' },
    //     { 'N', 'B', 'Y', 'G', 'P', 'S', 'K', 'H', 'E', 'X' },
    //     { 'V', 'O', 'W', 'U', 'T', 'I', 'Z', 'A', 'L', 'C' },
    //     { 'M', 'Q', 'B', 'D', 'N', 'F', 'R', 'J', 'G', 'E' },
    //     { 'H', 'S', 'K', 'T', 'U', 'X', 'W', 'O', 'P', 'Y' },
    //     { 'C', 'Z', 'A', 'I', 'L', 'M', 'V', 'G', 'N', 'B' },
    //     { 'D', 'F', 'E', 'H', 'S', 'K', 'J', 'Q', 'R', 'T' },
    //     { 'U', 'X', 'Y', 'W', 'V', 'O', 'P', 'N', 'M', 'L' }
    // };

// int buscaVertical(char matriz[8][10], char palavra[5]);
// int BuscaHorizontal(char matriz[8][10], char palavra[]);
// int BuscaDiagonal(char matriz[8][10], char palavra[]);
// int buscaTotal(char palavra[], char matriz[8][10]);


int buscaTotal(char matriz[8][10], char palavra[]){
    int achou = 0;
    
    achou = buscaVertical(matriz, palavra);
    if(achou) return 1;
    
    achou = BuscaHorizontal(matriz, palavra);
    if(achou) return 1;
    
    achou = BuscaDiagonal(matriz, palavra);
    if(achou) return 1;
    
    return 0; // Se passou pelas 3 e nùo achou nada, retorna 0
}

int buscaVertical(char matriz[8][10], char palavra[]){
    int i, j, x;
    int qtd_linhas = 8;
    int qtd_colunas = 10;

    // Descendo
    for(i = 0; i < qtd_linhas; i++){
        for(j = 0; j < qtd_colunas; j++){
            x = 0;
            while(palavra[x] != '\0' && (i + x) < qtd_linhas && matriz[i+x][j] == palavra[x]){
                x++;
            }
            if(palavra[x] == '\0') return 1; // ACHOU!
        }
    }
    
    // Subindo
    for(i = qtd_linhas - 1; i >= 0; i--){ // i comeùa de qtd_linhas - 1 para nùo estourar a matriz
        for(j = 0; j < qtd_colunas; j++){
            x = 0;
            while(palavra[x] != '\0' && (i-x) >= 0 && matriz[i-x][j] == palavra[x]){
                x++;
            }
            if(palavra[x] == '\0') return 1; // ACHOU!
        }
    }
    return 0; 
}

int BuscaHorizontal(char matriz[8][10], char palavra[]){
    int i, j, x;
    int qtd_linhas = 8;
    int qtd_colunas = 10;

    // Indo para a direita
    for(i = 0; i < qtd_linhas; i++){
        for(j = 0; j < qtd_colunas; j++){
            x = 0;
            while(palavra[x] != '\0' && (j + x) < qtd_colunas && matriz[i][j+x] == palavra[x]){
                x++;
            }
            if(palavra[x] == '\0') return 1; // ACHOU!
        }
    }
    
    // Voltando para a esquerda
    for(i = 0; i < qtd_linhas; i++){
        for(j = qtd_colunas - 1; j >= 0; j--){ // j comeùa de qtd_colunas - 1 para nùo estourar a matriz
            x = 0;
            while(palavra[x] != '\0' && (j - x) >= 0 && matriz[i][j-x] == palavra[x]){
                x++;
            }
            if(palavra[x] == '\0') return 1; // ACHOU!
        }
    }
    return 0;
}

int BuscaDiagonal(char matriz[8][10], char palavra[]){
    int i, j, x;
    int qtd_linhas = 8;
    int qtd_colunas = 10;

    for(i = 0; i < qtd_linhas; i++){
        for(j = 0; j < qtd_colunas; j++){
            
            // 1. DESCENDO DIREITA
            x = 0;
            while(palavra[x] != '\0' && (i + x) < qtd_linhas && (j + x) < qtd_colunas && matriz[i+x][j+x] == palavra[x]) x++;
            if(palavra[x] == '\0') return 1;

            // 2. SUBINDO ESQUERDA
            x = 0;
            while(palavra[x] != '\0' && (i - x) >= 0 && (j - x) >= 0 && matriz[i-x][j-x] == palavra[x]) x++;
            if(palavra[x] == '\0') return 1;

            // 3. DESCENDO ESQUERDA
            x = 0;
            while(palavra[x] != '\0' && (i + x) < qtd_linhas && (j - x) >= 0 && matriz[i+x][j-x] == palavra[x]) x++;
            if(palavra[x] == '\0') return 1;

            // 4. SUBINDO DIREITA
            x = 0;
            while(palavra[x] != '\0' && (i - x) >= 0 && (j + x) < qtd_colunas && matriz[i-x][j+x] == palavra[x]) x++;
            if(palavra[x] == '\0') return 1;
        }
    }
    return 0;
}



DataQuebrada quebraData(char data[]){
  DataQuebrada dq;
  char sDia[3];
	char sMes[3];
	char sAno[5];
	int i; 

	for (i = 0; data[i] != '/'; i++){
		sDia[i] = data[i];	
	}
	if(i == 1 || i == 2){ // testa se tem 1 ou dois digitos
		sDia[i] = '\0';  // coloca o barra zero no final
	}else {
		dq.valido = 0;
    return dq;
  }  
	

	int j = i + 1; //anda 1 cada para pular a barra
	i = 0;

	for (; data[j] != '/'; j++){
		sMes[i] = data[j];
		i++;
	}

	if(i == 1 || i == 2){ // testa se tem 1 ou dois digitos
		sMes[i] = '\0';  // coloca o barra zero no final
	}else {
		dq.valido = 0;
    return dq;
  }
	

	j = j + 1; //anda 1 cada para pular a barra
	i = 0;
	
	for(; data[j] != '\0'; j++){
	 	sAno[i] = data[j];
	 	i++;
	}

	if(i == 2 || i == 4){ // testa se tem 2 ou 4 digitos
		sAno[i] = '\0';  // coloca o barra zero no final
	}else {
		dq.valido = 0;
    return dq;
  }

  dq.iDia = atoi(sDia);
  dq.iMes = atoi(sMes);
  dq.iAno = atoi(sAno); 

	dq.valido = 1;
    
  return dq;
}

