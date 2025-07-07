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
void HeapSort(LISTA* estruturas, int* mov, int* comp, int n);
void heapify(LISTA* estruturas, int n, int i, int* mov, int* comp);
void swap(REGISTRO* a, REGISTRO* b, int* mov);

void gerar_estruturas(LISTA* estruturas, int n, int array[]){
    for (int i = 0; i < n; i++){
        estruturas -> lista[i].chave = array[i];
    }
}

void testarHeapSort(LISTA* estruturas, int n)
{
    clock_t hora_inicio, hora_fim;
    int mov = 0;
    int comp = 0;

    hora_inicio = clock();
    HeapSort(estruturas, &mov, &comp, n);
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

void HeapSort(LISTA* estruturas, int* mov, int* comp, int n){
    // Constrói o heap (reorganiza o array)
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(estruturas, n, i, mov, comp);
    }

    // Extrai elementos do heap um por um
    for (int i = n - 1; i > 0; i--) {
        // Move a raiz atual para o fim
        swap(&estruturas->lista[0], &estruturas->lista[i], mov);
        // Chama heapify na heap reduzida
        heapify(estruturas, i, 0, mov, comp);
    }
}

void heapify(LISTA* estruturas, int n, int i, int* mov, int* comp) {
    int largest = i; // Inicializa largest como a raiz
    int left = 2 * i + 1; // Filho esquerdo
    int right = 2 * i + 2; // Filho direito

    // Se o filho esquerdo é maior que a raiz
    if (left < n) {
        (*comp)++; // Conta uma comparação
        if (estruturas->lista[left].chave > estruturas->lista[largest].chave) {
            largest = left;
        }
    }

    // Se o filho direito é maior que o maior até agora
    if (right < n) {
        (*comp)++; // Conta uma comparação
        if (estruturas->lista[right].chave > estruturas->lista[largest].chave) {
            largest = right;
        }
    }

    // Se o maior não é a raiz
    if (largest != i) {
        swap(&estruturas->lista[i], &estruturas->lista[largest], mov);
        // Recursivamente heapifica a subárvore afetada
        heapify(estruturas, n, largest, mov, comp);
    }
}

void swap(REGISTRO* a, REGISTRO* b, int* mov) {
    REGISTRO temp = *a;
    *a = *b;
    *b = temp;
    *mov += 3; // Contabiliza 3 movimentações (temp, *a, *b)
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
    testarHeapSort(&estruturas, n);

    // Libere a memória alocada
    free(array);

    return 0;
}
