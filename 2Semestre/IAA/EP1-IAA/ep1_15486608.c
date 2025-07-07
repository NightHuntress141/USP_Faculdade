/*EP 1 de IAA -> Rebecka Bocci Domingues, NUSP 15486608*/

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 256      //Totalmente branco (255) +1 para base de comparação
#define MIN -1       //Totalmente preto (0) -1 para base de comparação

/*A seguinte estrutura guarda as principais informações do pixel analisado: intensidade 
da cor e posição na matriz*/
typedef struct{
    int intensidade;
    int coluna;
    int linha;
}PIXEL;


/*A seguinte estrutura guarda as principais informações do pixel mais escuro: intensidade 
da cor e posição na matriz*/
typedef struct{
    int intensidade;
    int coluna;
    int linha;
}PIXEL_MAIS_ESCURO;


/*A seguinte estrutura guarda as principais informações do pixel mais claro: intensidade 
da cor e posição na matriz*/
typedef struct{
    int intensidade;
    int coluna;
    int linha;
}PIXEL_MAIS_CLARO;


/*A seguinte função recebe como parâmetros a dimensão N da matriz e o nome do arquivo
e retorna a estrutura PIXEL preenchida com as informações lidas no arquivo de entrada*/
PIXEL **ler_arquivo_entrada(const char *nome_arquivo, int N) {
    FILE *arquivo = fopen(nome_arquivo, "r");

    //Sinal de erro ao ler o arquivo
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo %s.\n", nome_arquivo);
        return NULL;
    }

    //Alocação dinâmica da matriz NxN 
    PIXEL **matriz = (PIXEL **) malloc(N * sizeof(PIXEL *));
    for (int i = 0; i < N; i++) {
        matriz[i] = (PIXEL *) malloc(N * sizeof(PIXEL));
    }

    //Preenchimento da matriz a partir da leitura dos valores contidos no arquivo
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            int valor;
            //Leitura dos valores dos pixels contidos no arquivo gerado
            fscanf(arquivo, "%d", &valor);
            
            matriz[i][j].intensidade = valor;
            matriz[i][j].linha = i;
            matriz[i][j].coluna = j;
        }
    }

    fclose(arquivo);
    printf("Arquivo de entrada %s lido com sucesso! \n\n", nome_arquivo);

    return matriz;
}


/*A seguinte função recebe como parâmetros a dimensão N da matriz e os elementos de 
sua estrutura e não retorna nenhum valor*/
void exibir_matriz(PIXEL **matriz, int N) {
    if (matriz != NULL) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                printf("Pixel (%d, %d): intensidade = %d\n", 
                       matriz[i][j].linha, matriz[i][j].coluna, 
                       matriz[i][j].intensidade);
            }
        }
    }
}


/*A seguinte função recebe como parâmetros a matriz e os elementos de sua estrutura, o valor da linha inicial,
o valor da coluna inicial, o valor da dimensão N da matriz e o valor max do pixel e não retorna nenhum valor*/
void achar_max_pixel (PIXEL **matriz, int LinhaInicial, int ColunaInicial, int N, PIXEL_MAIS_CLARO *max) {

    /*Caso Base: caso a submatriz for 1x1, isto é, um pixel*/
    if (N == 1){
        int maior_intensidade = matriz[LinhaInicial][ColunaInicial].intensidade;
        if (maior_intensidade > max -> intensidade){
            max -> intensidade = maior_intensidade;
            max -> linha = matriz[LinhaInicial][ColunaInicial].linha;
            max -> coluna = matriz[LinhaInicial][ColunaInicial].coluna;
        }
        return;
    }

    int div = N / 2;
    
    /*Primeiro quadrante*/
    achar_max_pixel(matriz, LinhaInicial, ColunaInicial, div, max);
    
    /*Segundo quadrante*/
    achar_max_pixel(matriz, LinhaInicial, ColunaInicial + div, div, max);
    
    /*Terceiro quadrante*/
    achar_max_pixel(matriz, LinhaInicial + div, ColunaInicial, div, max);
    
    /*Quarto quadrante*/
    achar_max_pixel(matriz, LinhaInicial + div, ColunaInicial + div, div, max);

}


/*A seguinte função recebe como parâmetros a matriz e os elementos de sua estrutura, o valor da linha inicial,
o valor da coluna inicial, o valor da dimensão N da matriz e o valor min do pixel e não retorna nenhum valor*/
void achar_min_pixel (PIXEL **matriz, int LinhaInicial, int ColunaInicial, int N, PIXEL_MAIS_ESCURO *min) {

    /*Caso Base: caso a submatriz for 1x1, isto é, um pixel*/
    if (N == 1){
        int menor_intensidade = matriz[LinhaInicial][ColunaInicial].intensidade;
        if (menor_intensidade < min -> intensidade){
            min -> intensidade = menor_intensidade;
            min -> linha = matriz[LinhaInicial][ColunaInicial].linha;
            min -> coluna = matriz[LinhaInicial][ColunaInicial].coluna;
        }
        return;
    }

    int div = N / 2;
    
    /*Primeiro quadrante*/
    achar_min_pixel(matriz, LinhaInicial, ColunaInicial, div, min);
    
    /*Segundo quadrante*/
    achar_min_pixel(matriz, LinhaInicial, ColunaInicial + div, div, min);
    
    /*Terceiro quadrante*/
    achar_min_pixel(matriz, LinhaInicial + div, ColunaInicial, div, min);
    
    /*Quarto quadrante*/
    achar_min_pixel(matriz, LinhaInicial + div, ColunaInicial + div, div, min);

}


/*A seguinte função recebe como parâmetros o nome do arquivo de saida e os elementos da estrurtura sobre
o pixel mais claro e mais escuro e não retorna nenhum valor*/
void fazer_arquivo_saida (const char *nome_arquivo_saida, PIXEL_MAIS_ESCURO *min, PIXEL_MAIS_CLARO *max){
    FILE *arquivo = fopen(nome_arquivo_saida, "w");

    fprintf(arquivo, "min = %d; pos = (%d, %d)", min -> intensidade, min -> linha, min -> coluna);
    fprintf(arquivo, "max = %d; pos = (%d, %d)", max -> intensidade, max -> linha, max -> coluna);

    fclose(arquivo);
    printf("Arquivo de saida %s gerado com sucesso! \n\n", nome_arquivo_saida);
}


int main (int argc, char* argv[]){

    int N;

   /*Recebendo a dimensão NxN da Matriz*/
    N = atoi(argv[1]);

    /*Geração do arquivo de entrada com a matriz*/
    const char *nome_arquivo = argv[2];

    /*Leitura do arquivo de entrada e alocação dinamica dos valores para estrutura PIXEL*/
    PIXEL **matriz = ler_arquivo_entrada(nome_arquivo, N);

    /*Exibição da matriz lida pela função*/
    if (matriz != NULL) {
        exibir_matriz(matriz, N); 
    }

    /*Função recursiva para achar o máximo*/
    PIXEL_MAIS_CLARO max;
    max.intensidade = MIN;
    achar_max_pixel(matriz, 0, 0, N, &max);
    printf("Pixel mais claro (intensidade): %d\n", max.intensidade);
    printf("Pixel mais claro (coluna): %d\n", max.coluna);
    printf("Pixel mais claro (linha): %d\n", max.linha);

    /*Função recursiva para achar o mínimo*/
    PIXEL_MAIS_ESCURO min;
    min.intensidade = MAX;
    achar_min_pixel(matriz, 0, 0, N, &min);
    printf("Pixel mais escuro (intensidade): %d\n", min.intensidade);
    printf("Pixel mais escuro (coluna): %d\n", min.coluna);
    printf("Pixel mais escuro (linha): %d\n", min.linha);

    /*Escrevendo o output*/
    const char *nome_arquivo_saida = argv[3];
    fazer_arquivo_saida(nome_arquivo_saida, &min, &max);
    
    /*Liberação da memória alocada durante a execução do programa*/
    for (int i = 0; i < N; i++) {
        free(matriz[i]);
    }
    free(matriz);
    
    return 0;
}