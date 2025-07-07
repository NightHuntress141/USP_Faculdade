#include <stdio.h>
#include <malloc.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#define MAX 10000

typedef struct {
    int chave;
    int campoDaEstrutura[1000];
} REGISTRO;

typedef struct {
    REGISTRO lista[MAX];
} LISTA;

typedef REGISTRO* PONT;

void gerar_estruturas(LISTA* estruturas, int n, int array[]) {
    for (int i = 1; i <= n; i++) {
        estruturas->lista[i].chave = array[i];
    }
}

// Declaração das funções
void InsertionSort(LISTA* estruturas, int* mov, int* comp, int n);

void testarInsertionSort(LISTA* estruturas, int n) {
    clock_t hora_inicio, hora_fim;
    int mov = 0;
    int comp = 0;

    hora_inicio = clock();
    InsertionSort(estruturas, &mov, &comp, n);
    hora_fim = clock();
    double tempo = (double)(hora_fim - hora_inicio) * (1000000.0 / CLOCKS_PER_SEC);

    printf("Tempo: %.100f\n", tempo);
    printf("Movimentos: %d\n", mov);
    printf("Comparações: %d\n", comp);

    // Imprimir a lista ordenada
    printf("Lista ordenada:\n");
    for (int i = 1; i < n; i++) { // Ignorando o índice 0 que é o sentinela
        printf("%d ", estruturas->lista[i].chave);
    }
    printf("\n");
}

void InsertionSort(LISTA* estruturas, int* mov, int* comp, int n) {
    int i, j;
    REGISTRO key;

    // Adicionar o sentinela no início do array
    REGISTRO sentinela = estruturas->lista[0];
    for (i = 1; i < n; i++) {
        if (estruturas->lista[i].chave < sentinela.chave) {
            sentinela = estruturas->lista[i];
        }
    }
    estruturas->lista[0] = sentinela;

    // Insertion Sort
    for (i = 2; i < n; i++) {
        key = estruturas->lista[i];
        j = i - 1;
        (*comp)++; // Contando a comparação inicial
        while (key.chave < estruturas->lista[j].chave) {
            estruturas->lista[j + 1] = estruturas->lista[j];
            (*mov)++; // Contando a movimentação
            j--;
            (*comp)++; // Contando cada comparação do while
        }
        estruturas->lista[j + 1] = key;
        (*mov)++; // Contando a movimentação final
    }
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Uso: %s <nome_do_arquivo>\n", argv[0]);
        return 1;
    }
    FILE *file;
    int n;
    // Abra o arquivo para leitura
    file = fopen(argv[1], "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }
    // Leia o valor da primeira linha para a variável n
    fscanf(file, "%d", &n);
    // Crie um array para armazenar os elementos da segunda linha
    int *array = (int*)malloc(n * sizeof(int));
    if (array == NULL) {
        printf("Erro de alocação de memória.\n");
        fclose(file);
        return 1;
    }
    // Leia os valores da segunda linha e armazene no array
    for (int i = 0; i < n; i++) {
        fscanf(file, "%d", &array[i + 1]);
    }
    // Feche o arquivo
    fclose(file);
    // Exemplo: imprimir n e o array para verificar
    printf("Número de elementos: %d\n", n);
    printf("Elementos:\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", array[i + 1]);
    }
    printf("\n");

    /* Criação da Array de Estruturas estática */
    LISTA estruturas;
    gerar_estruturas(&estruturas, n, array);

    /* Testes dos Algoritmos */
    testarInsertionSort(&estruturas, n);

    // Libere a memória alocada
    free(array);

    return 0;
}
