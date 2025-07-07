#include <stdio.h>
#include <stdlib.h>

// estrutura que contem a relacao valor/peso e o peso dos itens
typedef struct{
    double valor_peso;
    int peso;
}Mochila;

// funcao auxiliar ao qsort
int compara_decrescente(const void *a, const void *b) {
    Mochila A = *(Mochila*)a;
    Mochila B = *(Mochila*)b;
    
    if (A.valor_peso < B.valor_peso) return 1;
    if (A.valor_peso > B.valor_peso) return -1;
    return 0;
}

// funcao que resolve o problema
double mochila_fracionada(int *valor, int *peso, int K, int n){
    Mochila itens[n]; // cria o array que armazena os itens
    double itens_mochila[n]; // cria o array que armazenara a quantidade de cada item
    double valor_mochila = 0; // valor total na mochila

    // inicializa os itens na mochila como 0
    for (int i = 0; i < n; i++) {
        itens_mochila[i] = 0;
    }

    // calcula valor/peso de cada item e atribui ao array
    for (int i = 0; i < n; i++){
        
        itens[i].valor_peso = (double) valor[i] / peso[i];
        itens[i].peso = peso[i];
    }

    // ordena descrescentemente
    qsort(itens, n, sizeof(Mochila), compara_decrescente);

    // imprime o array de valor/peso ordenado
    printf("Array ordenado (valor/peso): ");
    for (int i = 0; i < n; i++){
        printf("%.2f, ", itens[i].valor_peso);
    }
    printf("\n");

    int capacidade = K;
    int j = 0;
    
    // loop principal que adiciona 1 ao array da mochila se o item for inserido inteiro e uma fracao caso seja adicionado somente uma parte
    while (capacidade > 0 && j < n){

        if (itens[j].peso <= capacidade){
            itens_mochila[j] = 1.0;
            capacidade = capacidade - itens[j].peso;
            valor_mochila += itens[j].valor_peso * itens[j].peso;
        }
        else{
            itens_mochila[j] = (double) capacidade / itens[j].peso;
            valor_mochila += itens_mochila[j] * itens[j].valor_peso * itens[j].peso;
            capacidade = 0;
        }
        
        j++;
    }

    // se acabaram os itens e sobrou espaco na mochila
    if (capacidade > 0){
        printf("Acabaram os itens e sobrou %d de espaco na mochila!\n", capacidade);
    }

    // imprime as fracoes dos itens na mochila
    printf("Itens na Mochila (fracoes): ");
    for (int i = 0; i < n; i++){
        if (itens_mochila[i] != 0){
            printf("%.2f, ", itens_mochila[i]);
        }
    }

    return valor_mochila;

}

// main
int main(){
    int K = 50;
    int n = 4;

    int valor[] = {120, 60, 100, 120};
    int peso[] = {30, 10, 20, 30};

    double valor_mochila = mochila_fracionada(valor, peso, K, n);
    printf("\nValor maximo na mochila: %.2f\n", valor_mochila);

    return 0;
}