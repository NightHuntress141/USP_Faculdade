/* Problema 1: Dado um ponto i de origem e um ponto j de destino, ache um caminho entre i e j, 
usando apenas vértices sem passar por cidades perigosas (não válidas) */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define V 5

typedef struct r{
    struct r *prox;
    int adj;
} NO;

typedef struct{
    // Possui apenas a cabeça da lista de adjacencia
    NO* inicio;
    // Diz se a cidade é perigosa ou não
    bool valido;
    int Flag;
} vertice;

void inicializar(vertice *g){
    int i;
    for(i = 1; i <= V; i++){
        g[i].inicio = NULL;
        g[i].Flag = 0;
    }
}

NO* arestaExiste(vertice *g, int i, int j, NO** ant){
    // Recebemos como argumento um ponteiro auxiliar que indicara o vértice anterior
    *ant = NULL;
    // Criamos um ponteiro p que vai iniciar do começo de cada lista (vertice)
    NO* p = g[i].inicio;
    // Loop que percorre lista por lista em busca da aresta que aponta de um vértice para outro
    while(p){
        if(p -> adj == j) return p; // Achou o vértice
        *ant = p; // Anterior recebe o valor do atual
        p = p -> prox; // Atual recebe o valor do pŕoximo
    }
    return NULL; //aresta não existe
}

// Cria-se uma aresta de um vértice i (origem da aresta) para apontar para o vértice i (destino da aresta)
bool inserirAresta(vertice *g, int i, int j){
    // Criamos um ponteiro auxiliar que indicara o vértice anterior
    NO* ant;
    // Recebemos o valor achado que indica o vértice i que aponta para j
    NO* atual = arestaExiste(g, i, j, &ant);

    if(atual) return false; //Já existe

    NO *novo = (NO*) malloc(sizeof(NO)); // Alocamos um novo espaço na mémoria

    novo->adj = j; // Coloca o valor do vértice j
    novo->prox = g[i].inicio; // Faz com que o novo (j) aponte como proximo o vértice (i)

    // Insere o novo nó no início da lista de adjacência do vértice i
    g[i].inicio = novo; // O início da lista agora passa a ser o novo nó.

    return true;
}

void imprimirGrafo(vertice *g) {
    for (int i = 1; i < V; i++) {
        printf("Vértice %d:", i);
        NO* p = g[i].inicio;
        while (p) {
            printf(" -> %d", p->adj);
            p = p->prox;
        }
        printf("\n");
    }
}

void BuscaProfCaminho(vertice* g, int i, int j, bool* Fim){
    g[i].Flag = 1;
    if(*Fim) return;
    if(i == j){
        *Fim = true;
        return;
    }
    NO* p = g[i].inicio;
    while(p){ 
        if( g[p -> adj].valido == true && g[p -> adj].Flag == 0){
            BuscaProfCaminho(g, p -> adj, j, Fim);
            if(*Fim) return;
        }
        p = p -> prox;
    }
    g[i].Flag = 2; // Já foi descoberto
}

void resetarFlags(vertice *g) {


    for (int i = 1; i <= V; i++) {
        g[i].Flag = 0;
    }
}

int main(){
    vertice *g = (vertice*) malloc((V+1) * sizeof(vertice));
    inicializar(g);
    resetarFlags(&g);


    
}