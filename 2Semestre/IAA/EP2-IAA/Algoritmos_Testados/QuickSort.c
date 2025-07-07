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
void QuickSort(LISTA* estruturas, int low, int high, int* mov, int* comp);

void gerar_estruturas(LISTA* estruturas, int n, int array[]){
    for (int i = 0; i < n; i++){
        estruturas -> lista[i].chave = array[i];
    }
}

void testarQuickSort(LISTA* estruturas, int low, int high)
{
    clock_t hora_inicio, hora_fim;
    int mov = 0;
    int comp = 0;

    hora_inicio = clock();
    QuickSort(estruturas, low, high, &mov, &comp);
    hora_fim = clock();
    double tempo = (double)(hora_fim - hora_inicio) * (1000000000.0 / CLOCKS_PER_SEC);
    
    printf("Tempo: %.100f \n", tempo);
    printf("Movimentos: %d \n", mov);
    printf("Comparações: %d \n", comp);
}

// Função para imprimir a lista
void imprimirLista(LISTA* estruturas, int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", estruturas->lista[i].chave);
    }
    printf("\n");
}

// Função para trocar dois registros
void trocar(PONT a, PONT b, int* mov) {
    REGISTRO temp = *a;
    *a = *b;
    *b = temp;
    (*mov)++; // Incrementa o contador de movimentações
}

// Função de partição
int particionar(LISTA* estruturas, int low, int high, int* mov, int* comp) {
    int pivo = estruturas->lista[high].chave; // Pivô é o último elemento
    int i = low - 1;

    for (int j = low; j < high; j++) {
        (*comp)++; // Incrementa o contador de comparações
        if (estruturas->lista[j].chave <= pivo) {
            i++;
            trocar(&estruturas->lista[i], &estruturas->lista[j], mov);
        }
    }
    trocar(&estruturas->lista[i + 1], &estruturas->lista[high], mov);
    return i + 1;
}

// QuickSort recursivo
void QuickSort(LISTA* estruturas, int low, int high, int* mov, int* comp) {
    if (low < high) {
        int pi = particionar(estruturas, low, high, mov, comp);

        QuickSort(estruturas, low, pi - 1, mov, comp);  // Recursivamente ordena os elementos à esquerda
        QuickSort(estruturas, pi + 1, high, mov, comp); // Recursivamente ordena os elementos à direita
    }
}

int main(int argc, char *argv[]){

    if (argc != 2) {
        printf("Uso: %s <nome_do_arquivo>\\n", argv[0]);
        return 1;
    }
    FILE *file;
    int n;
    // Abra o arquivo para leitura
    file = fopen(argv[1], "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\\n");
        return 1;
    }
    // Leia o valor da primeira linha para a variável n
    fscanf(file, "%d", &n);
    // Crie um array para armazenar os elementos da segunda linha
    int *array = (int*)malloc(n * sizeof(int));
    if (array == NULL) {
        printf("Erro de alocação de memória.\\n");
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
    printf("Numero de elementos: %d\\n", n);
    printf("Elementos: \\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", array[i]);
    }
    printf("\\n");

    
    /*Criação da Array de Estruturas estática*/
    LISTA estruturas;
    gerar_estruturas(&estruturas, n, array);
    
    /*Testes dos Algoritmos*/
    testarQuickSort(&estruturas, 0, n - 1); 
    printf("Lista ordenada: ");
    imprimirLista(&estruturas, n);

    // Libere a memória alocada
    free(array);

    return 0;
}
