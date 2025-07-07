/*
-> Códigos fundamentais para Grafos:
    - Inicialização (acertou)
    - Verificar se aresta existe (acertou)
    - Adicionar aresta (acertou)
    - Excluir aresta (errinho bobo)
    - Copiar Grafo
    - Grau de Saída e Entrada
    - Desalocar um Grafo
*/

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define V 10 // Número de vértice que existem no grafo

typedef struct s{
    NO* inicio; //Ponteiro para o início da lista dos vértices adjacentes ao vértice que estamos analisando
    int Flag;
}VERTICE;

typedef struct r{
    struct r* prox; //Ponteiro que aponta para estruturas do tipo NO e que guardará o próximo vértice
    int adj; //Guarda o valor do vértice adjacente
    // Adicionamos valores referentes às arestas aqui
}NO;

// Inicialização do Grafo
void inicializarGrafo(VERTICE* g){
    for(int i = 1; i <= V; i++){
        g[i].inicio = NULL;
    }
}

// Antes de adicionar ou excluir uma aresta, devemos verificar se ela existe
// A função recebe o grafo, e os valores dos vértices de origem (i) e destino (j). Ademais, é interessante adicionar um auxiliar chamado anterior para guardarmos
// o anterior 
// A função retorna um ponteiro para aquele nó
NO* existeAresta(VERTICE* g, int i, int j, NO** ant){
    *ant = NULL;

    NO* atual = g[i].inicio;
    // Percorrer a lista do vértice de origem (i) procurando o vértice de destino (j)
    while(atual){
        if(atual -> adj == j) return atual;
        *ant = atual;
        atual = atual -> prox;
    }
    return NULL;
}

// A função recebe o grafo, e os valores dos vértices de origem (i) e destino (j) que deseja-se criar novo
bool adicionarAresta(VERTICE* g, int i, int j){
    NO* ant;
    NO* atual = existeAresta(g, i, j, &ant);
    if(atual) return false; // Já existe

    NO* novo_no = (NO*) malloc(sizeof(NO));

    novo_no -> prox = g[i].inicio;
    novo_no -> adj = j;

    // Vai ser adicionado no começo da lista
    g[i].inicio = novo_no;

    return true;
}

bool excluirAresta(VERTICE* g, int i, int j){
    NO* ant;
    NO* atual = existeAresta(g, i, j, &ant);
    if(!atual) return false; // Não existe, não tem como excluir

    // Se existe um anterior, então apenas aponte para o próximo
    if (ant) 
        ant->prox = atual->prox;
    // Caso contrário, se o elemento está no início da lista
    else 
        g[i].inicio = atual->prox;

    free(atual);

    return true;
}

void zerarFlags(VERTICE* g){
    for(int i = 0; i <= V; i++){
        g[i].Flag = 0;
    }
}

void buscaProf(VERTICE* g, int i){
    // Inicialização
    g[i].Flag = 1;
    NO* p = g[i].inicio;
    while(p){
        if(g[p -> adj].Flag == 0) buscaProf(g, p -> adj);
        p = p -> prox;
    }
    g[i].Flag = 2;
}

void buscaLargura(VERTICE* g, int i){
    // Inicialização
    zerarFlags(g);
    FILA f;
    inicializarFila(&f);

    // Entra na fila e marca como acabou de ser achado
    entrarFila(&f, i);
    g[i].Flag = 1;

    while(f){ //Enquanto a fila não estiver vazia
        i = sairFila(&f); // Retorna quem acabou de sair da fila
        g[i].Flag = 2; // Marca como processado
        NO* p = g[i].inicio;

        while(p){
            if(g[p -> adj].Flag == 0){
                entrarFila(&f, p -> adj);
                g[p -> adj].Flag = 1;
            }
            p = p -> prox;
        }


    }

    
}

int main(){
    VERTICE g;
    inicializarGrafo(&g);
}


