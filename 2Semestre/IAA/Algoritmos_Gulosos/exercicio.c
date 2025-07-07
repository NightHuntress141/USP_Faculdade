#include <stdio.h>
#include <stdlib.h>

typedef struct{
    double inicio;
    double fim;
}Intervalo;

int compara_crescente(const void *a, const void *b) {
    double A = *(double*)a;
    double B = *(double*)b;
    
    if (A < B) return -1;  
    if (A > B) return 1;   
    return 0;              
}

double menor_colecao(double *vetor, int n){
    
    Intervalo colecao[n];

    qsort(vetor, n, sizeof(double), compara_crescente);

    int j = 0;
    int i = 0;

    colecao[j].inicio = vetor[i];

    while (i < n){
        while (i < n && vetor[i] - colecao[j].inicio <= 1){
           
            colecao[j].fim = vetor[i];
            i++;
        }

        j++;
        colecao[j].inicio = vetor[i];
        if (i == n-1){
            colecao[j].fim = colecao[j].inicio;
            i++;
        }
    }

    

    printf("Colecao (tamanho %d): { ", j+1);
    for (int k = 0; k <= j; k++){
        printf("{%.2f - %.2f} , ", colecao[k].inicio, colecao[k].fim);
    }
    printf("}\n");

    return j+1;
}

int main() {
    // Exemplo de conjunto de pontos
    double pontos[] = {1.5, 1.7, 1.8, 2.4, 3, 3.1, 4.9, 5.2, 5.8, 6.0};
    int n = 10;

    int num_intervalos = menor_colecao(pontos, n);
    printf("Numero de intervalos: %d\n", num_intervalos);
}