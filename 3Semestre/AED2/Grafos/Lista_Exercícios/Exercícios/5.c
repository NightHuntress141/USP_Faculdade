/* Escreva um algoritmo que dado um grafo m representado em matriz, retorne o mesmo grafo em listas de adjacências. */

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define V 4 // Número de vértice que existem no grafo

typedef struct{
    int matriz[V + 1][V + 1]; 
    int flag[V + 1];
} Grafo;

typedef struct r{
    struct r* prox; 
    int adj; 
}NO;

typedef struct s{
    NO* inicio; 
}vertice;

void inicializarLista(vertice* g){
    for(int i = 1; i <= V; i++){
        g[i].inicio = NULL;
    }
}

void inicializar(Grafo* g){
    for(int i = 1; i <= V; i++){
        for(int j = 1; j <= V; j++){
            g -> matriz[i][j] = 0;
            g -> flag[i] = 0;
        }
    }
}

bool arestaExiste(Grafo* g, int i, int j){
    if(g -> matriz[i][j]) return true;
    else return false;
}

void adicionarAresta(Grafo* g, int i, int j) {
    if (i < 1 || i > V || j < 1 || j > V) {
        printf("Erro: vértices fora dos limites!\n");
        return;
    }
    if (!arestaExiste(g, i, j)) {
        g->matriz[i][j] = 1;
        // Para grafos não direcionados, descomente a linha abaixo:
        // g->matriz[j][i] = 1;
    }
}

void excluirAresta(Grafo* g, int i, int j) {
    if (i < 1 || i > V || j < 1 || j > V) {
        printf("Erro: vértices fora dos limites!\n");
        return;
    }
    if (arestaExiste(g, i, j)) {
        g->matriz[i][j] = 0;
        // Para grafos não direcionados, descomente a linha abaixo:
        // g->matriz[j][i] = 0;
    }
}

void imprimirGrafo(Grafo *g) {
    for (int i = 1; i <= V; i++) {
        for (int j = 1; j <= V; j++) {
            printf("%d ", g->matriz[i][j]);
        }
        printf("\n");
    }
}

void adicionarAresta(vertice* g, int i, int j){
    NO* novo_no = (NO*) malloc(sizeof(NO));
    novo_no -> prox = g[i].inicio;
    novo_no -> adj = j;
    g[i].inicio = novo_no;
}

vertice* criarLista(Grafo* g){
    vertice* lista = (vertice*) malloc((V + 1) * sizeof(vertice));
    inicializarLista(&lista);
    for(int i = 1; i <= V; i++){
        for(int j = 1; j <= V; j++){
            if(g -> matriz[i][j] == 1){
                adicionarArestaLista(&lista, i, j);
            }
        }
    }
    return &lista;
}

// Imprime a lista de adjacência
void imprimirLista(vertice* g) {
    for (int i = 1; i <= V; i++) {
        printf("%d: ", i);
        NO* atual = g[i].inicio;
        while (atual) {
            printf("%d -> ", atual->adj);
            atual = atual->prox;
        }
        printf("NULL\n");
    }
}

int main(){
    Grafo g;
    inicializar(&g);
    adicionarAresta(&g, 1, 2);
    adicionarAresta(&g, 1, 3);
    adicionarAresta(&g, 2, 4);
    adicionarAresta(&g, 3, 2);

    printf("Matriz de Adjacência:\n");
    imprimirGrafo(&g);

    printf("\nRemovendo aresta entre 1 e 3...\n");
    excluirAresta(&g, 1, 3);
    imprimirGrafo(&g);

    printf("\nBusca em Profundidade a partir do vértice 1:\n");
    buscaProf(&g, 1);
    
    printf("\nBusca em Largura a partir do vértice 1:\n");
    buscaLargura(&g, 1);
    
    vertice* lista = criarLista(&g);
    printf("\nLista de Adjacência:\n");
    imprimirLista(lista);

    free(lista);
    return 0;
}