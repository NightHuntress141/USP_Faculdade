
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define V 4 // Número de vértice que existem no grafo

typedef struct{
    int matriz[V + 1][V + 1]; 
    int flag[V + 1];
} Grafo;

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

void zerarFlags(Grafo *g){
    for(int i = 1; i <= V; i++){
        g -> flag[i] = 0;
    }
}

void buscaProf(Grafo *g, int i){
    zerarFlags(g);
    g -> flag[i] = 1; // Descoberto
    for(int j = 1; j <= V; j++){ // A partir de todos os vértices existentes
        if(g -> matriz[i][j] == 1 && g -> flag[i] == 0){
            buscaProf(g, j);
        }
    }
    g -> flag[i] = 2;
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



    return 0;
}