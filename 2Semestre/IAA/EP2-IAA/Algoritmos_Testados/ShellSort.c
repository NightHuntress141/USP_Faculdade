#include <stdio.h>
#include <malloc.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#define MAX 10000

typedef struct{
    int chave;
    int campoDaEstrutura[1];
} REGISTRO;

typedef struct{
    REGISTRO lista[MAX];
} LISTA;

typedef REGISTRO* PONT;

// Declaração das funções
void ShellSort(LISTA* estruturas, int* mov, int* comp, int n);


void gerar_estruturas(LISTA* estruturas, int n, int array[]){
    for (int i = 0; i < n; i++){
        estruturas -> lista[i].chave = array[i];
    }
}

void testarShellSort(LISTA* estruturas, int n)
{
    clock_t hora_inicio, hora_fim;
    int mov = 0;
    int comp = 0;

    hora_inicio = clock();
    ShellSort(estruturas, &mov, &comp, n);
    hora_fim = clock();
    double tempo = (double)(hora_fim - hora_inicio) * (1000000000.0 / CLOCKS_PER_SEC);
    
    printf("Tempo: %.100f \n", tempo);
    printf("Movimentos: %d \n", mov);
    printf("Comparações: %d \n", comp);

    // Imprimir a lista ordenada
    printf("Lista ordenada: \n");
    for (int i = 0; i < n; i++) { 
        printf("%d ", estruturas->lista[i].chave);
    }
    printf("\\n");
}

void ShellSort(LISTA* estruturas, int* mov, int* comp, int n){
    // Inicializa o contador de movimentações e comparações
    *mov = 0;
    *comp = 0;

    // Define os intervalos usando a sequência de Knuth
    int h = 1;
    while (h < n / 3) {
        h = 3 * h + 1;
    }

    // Realiza o ShellSort
    while (h >= 1) {
        for (int i = h; i < n; i++) {
            for (int j = i; j >= h && estruturas->lista[j].chave < estruturas->lista[j - h].chave; j -= h) {
                (*comp)++; // Incrementa o contador de comparações
                // Troca os elementos e incrementa o contador de movimentações
                REGISTRO temp = estruturas->lista[j];
                estruturas->lista[j] = estruturas->lista[j - h];
                estruturas->lista[j - h] = temp;
                (*mov) += 3; // Contabiliza como três movimentações: duas atribuições diretas e uma indireta
            }
            // Incrementa uma comparação que não entra no while interno
            if (i >= h && !(estruturas->lista[i].chave < estruturas->lista[i - h].chave)) {
                (*comp)++;
            }
        }
        h /= 3;
    }
}

int main(int argc, char *argv[]){

    if (argc != 2) {
        printf("Uso: %s <nome_do_arquivo> \n", argv[0]);
        return 1;
    }
    FILE *file;
    int n;
    // Abra o arquivo para leitura
    file = fopen(argv[1], "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo. \n");
        return 1;
    }
    // Leia o valor da primeira linha para a variável n
    fscanf(file, "%d", &n);
    // Crie um array para armazenar os elementos da segunda linha
    int *array = (int*)malloc(n * sizeof(int));
    if (array == NULL) {
        printf("Erro de alocação de memória. \n");
        fclose(file);
        return 1;
    }
    // Leia os valores da segunda linha e armazene no array
    for (int i = 0; i < n; i++) {
        fscanf(file, "%d", &array[i]);
    }
    // Feche o arquivo
    fclose(file);
    // Exemplo: imprimir n e o array para verificar
    printf("Numero de elementos: %d \n", n);
    printf("Elementos: \n");
    for (int i = 0; i < n; i++) {
        printf("%d ", array[i]);
    }
    printf(" \n");

    
    /*Criação da Array de Estruturas estática*/
    LISTA estruturas;
    gerar_estruturas(&estruturas, n, array);
    
    /*Testes dos Algoritmos*/
    testarShellSort(&estruturas, n);

    // Libere a memória alocada
    free(array);

    return 0;
}
