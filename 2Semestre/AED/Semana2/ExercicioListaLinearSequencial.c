#include <stdio.h>
#define MAX 50
#define ERRO -1
#define true 1
#define false 0

typedef int bool;
typedef int TIPOCHAVE;

typedef struct{
    TIPOCHAVE chave;
} REGISTRO;

typedef struct {
    REGISTRO A[MAX+1];
    int nroElem;
} LISTA;

void inicializarLista(LISTA* l){
l->nroElem = 0;
}

void exibirLista(LISTA* l){
int i;
printf("Lista: \" ");
for (i=0; i < l->nroElem; i++)
printf("%i ", l->A[i].chave);
printf("\"\n");
}

int InserirFinal (LISTA *lista1, REGISTRO *ch_nova){
    if (lista1 -> nroElem == MAX){
        return -1;
    }
    lista1 -> A[lista1 -> nroElem] = *ch_nova;
    lista1 -> nroElem++;
    return 0;
}

/*Esta função recebe o valor da lista  
e devolve o registros no arranjo A de forma crescente*/
void ordenar (LISTA *lista1){
    
}

int main (){
    LISTA lista1;
    
    //Inicializar a lista colocando um valor para o número de elementos
    inicializarLista(&lista1);

    //Criação de uma pequena lista inicial
    for (int i = 0; i < 5; i++){
        REGISTRO reg = {.chave = i * i};
        InserirFinal(&lista1, &reg);
    }

    //Exibição da lista no terminal
    exibirLista(&lista1);

    //Função de ordenação em forma crescente
    ordenar(&lista1);



}
