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
void MergeSort(LISTA* estruturas, int l, int r, int* mov, int* comp);
void merge(LISTA* estruturas, int l, int m, int r, int* mov, int* comp);

void gerar_estruturas(LISTA* estruturas, int n, int array[]){
    for (int i = 0; i < n; i++){
        estruturas -> lista[i].chave = array[i];
    }
}

void testarMergeSort(LISTA* estruturas, int n)
{
    clock_t hora_inicio, hora_fim;
    int mov = 0;
    int comp = 0;

    hora_inicio = clock();
    MergeSort(estruturas, 0, n - 1, &mov, &comp);
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

void merge(LISTA* estruturas, int l, int m, int r, int* mov, int* comp) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    // Cria arrays temporários
    REGISTRO L[n1], R[n2];

    // Copia os dados para os arrays temporários L[] e R[]
    for (i = 0; i < n1; i++) {
        L[i] = estruturas->lista[l + i];
        (*mov)++; // Contabiliza movimentação
    }
    for (j = 0; j < n2; j++) {
        R[j] = estruturas->lista[m + 1 + j];
        (*mov)++; // Contabiliza movimentação
    }

    // Mescla os arrays temporários de volta em lista[l..r]
    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2) {
        (*comp)++; // Contabiliza comparação
        if (L[i].chave <= R[j].chave) {
            estruturas->lista[k] = L[i];
            (*mov)++; // Contabiliza movimentação
            i++;
        } else {
            estruturas->lista[k] = R[j];
            (*mov)++; // Contabiliza movimentação
            j++;
        }
        k++;
    }

    // Copia os elementos restantes de L[], se houver
    while (i < n1) {
        estruturas->lista[k] = L[i];
        (*mov)++; // Contabiliza movimentação
        i++;
        k++;
    }

    // Copia os elementos restantes de R[], se houver
    while (j < n2) {
        estruturas->lista[k] = R[j];
        (*mov)++; // Contabiliza movimentação
        j++;
        k++;
    }
}

void MergeSort(LISTA* estruturas, int l, int r, int* mov, int* comp){
    if (l < r) {
        int m = l + (r - l) / 2;

        // Ordena a primeira e a segunda metade
        MergeSort(estruturas, l, m, mov, comp);
        MergeSort(estruturas, m + 1, r, mov, comp);

        // Mescla as duas metades ordenadas
        merge(estruturas, l, m, r, mov, comp);
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
    testarMergeSort(&estruturas, n);

    // Libere a memória alocada
    free(array);

    return 0;
}
