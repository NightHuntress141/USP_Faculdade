#include <stdio.h>
#include <malloc.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

#define MAX 10000

typedef struct{
    int chave;
    int campoDaEstrutura[1000];
} REGISTRO;

typedef struct{
    REGISTRO lista[MAX];
} LISTA;

typedef REGISTRO* PONT;

// Declaração das funções
void SelectionSort(LISTA* estruturas, int* mov, int* comp, int n);

void gerar_estruturas(LISTA* estruturas, int n, int array[]){
    for (int i = 0; i < n; i++){
        estruturas -> lista[i].chave = array[i];
    }
}

void testarSelectionSort(LISTA* estruturas, int n)
{
    clock_t hora_inicio, hora_fim;
    int mov = 0;
    int comp = 0;

    hora_inicio = clock();
    SelectionSort(estruturas, &mov, &comp, n);
    hora_fim = clock();
    double tempo = (double)(hora_fim - hora_inicio) * (1000000000.0 / CLOCKS_PER_SEC);
    
    printf("Tempo: %.100f \\n", tempo);
    printf("Movimentos: %d \\n", mov);
    printf("Comparações: %d \\n", comp);

    // Imprimir a lista ordenada
    printf("Lista ordenada:\\n");
    for (int i = 0; i < n; i++) { 
        printf("%d ", estruturas->lista[i].chave);
    }
    printf("\\n");
}

void SelectionSort(LISTA* estruturas, int *mov, int *comp, int n){

    for (int i = 0; i < n - 1; i++) {
        int minIndex = i;
        
        for (int j = i + 1; j < n; j++) {
            (*comp)++; // Conta uma comparação
            if (estruturas->lista[j].chave < estruturas->lista[minIndex].chave) {
                minIndex = j;
            }
        }

        // Realiza uma troca se o índice mínimo mudou
        if (minIndex != i) {
            REGISTRO temp = estruturas->lista[i];
            estruturas->lista[i] = estruturas->lista[minIndex];
            estruturas->lista[minIndex] = temp;
            (*mov) += 3; // Conta três movimentações (troca de três valores)
        }
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
    /*
    printf("Numero de elementos: %d\\n", n);
    printf("Elementos: \\n");
    for (int i = 0; i < n; i++) {
        printf("%d ", array[i]);
    }
    printf("\\n");
    */

    
    /*Criação da Array de Estruturas estática*/
    LISTA estruturas;
    gerar_estruturas(&estruturas, n, array);
    
    /*Testes dos Algoritmos*/
    testarSelectionSort(&estruturas, n); //Sem tempo

    // Libere a memória alocada
    free(array);

    return 0;
}
