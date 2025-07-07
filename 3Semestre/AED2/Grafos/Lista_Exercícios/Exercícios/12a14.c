/*
12. Seja um grafo g não-dirigido. Escreva uma função para detectar ciclos em g, retornando true/false.
    -> Isso é um problema de busca com grafos não dirigidos, ou seja, se não há ciclos, então formam comuni-
    dades de vértices. Ademais, devemos apenas DETECTAR esses ciclos.
13. Variação 1: remover as arestas que provocam ciclo. 
14. Variação 2: retornar o comprimento (i.e., a quantidade de arestas) do maior ciclo encontrado
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define V 5

typedef struct r {
    struct r *prox;
    int adj;
} NO;

typedef struct {
    NO* inicio;
    int flag;
} vertice;

void inicializar(vertice *g) {
    for (int i = 1; i <= V; i++) {
        g[i].inicio = NULL;
        g[i].flag = 0;
    }
}

NO* arestaExiste(vertice *g, int i, int j, NO** ant) {
    *ant = NULL;
    NO* p = g[i].inicio;
    while (p) {
        if (p->adj == j) return p;
        *ant = p;
        p = p->prox;
    }
    return NULL;
}

bool inserirAresta(vertice *g, int i, int j) {
    if (!arestaExiste(g, i, j, NULL)) {
        NO* novo = (NO*)malloc(sizeof(NO));
        novo->adj = j;
        novo->prox = g[i].inicio;
        g[i].inicio = novo;
    }
    if (!arestaExiste(g, j, i, NULL)) {
        NO* novo = (NO*)malloc(sizeof(NO));
        novo->adj = i;
        novo->prox = g[j].inicio;
        g[j].inicio = novo;
    }
    return true;
}

bool excluiAresta(vertice *g, int i, int j) {
    NO *ant;
    NO *atual = arestaExiste(g, i, j, &ant);
    if (!atual) return false;

    if (ant) 
        ant->prox = atual->prox;
    else 
        g[i].inicio = atual->prox;
    free(atual);

    // Remove a aresta no sentido inverso (j, i)
    atual = arestaExiste(g, j, i, &ant);
    if (ant) 
        ant->prox = atual->prox;
    else 
        g[j].inicio = atual->prox;
    free(atual);

    return true;
}

void imprimirGrafo(vertice *g) {
    for (int i = 1; i <= V; i++) {
        printf("Vértice %d:", i);
        NO* p = g[i].inicio;
        while (p) {
            printf(" -> %d", p->adj);
            p = p->prox;
        }
        printf("\n");
    }
}

void liberarGrafo(vertice *g) {
    for (int i = 1; i <= V; i++) {
        NO* atual = g[i].inicio;
        while (atual) {
            NO* temp = atual;
            atual = atual->prox;
            free(temp);
        }
    }
}

void zerarFlag(vertice* g) {
    for (int i = 1; i <= V; i++) {
        g[i].flag = 0;
    }
}

// Resolução problema 12
    // if(g[p -> adj]. Flag == 1)
bool buscaProf(vertice* g, int i, int pai) {
    g[i].flag = 1;
    NO* p = g[i].inicio;
    while (p) {
        if (g[p->adj].flag == 0) {
            if (buscaProf(g, p->adj, i)) return true;
        } else if (p->adj != pai) {
            return true;
        }
        p = p->prox;
    }
    g[i].flag = 2;
    return false;
}

// Resolução problema 12
bool buscaCiclos(vertice* g) {
    zerarFlag(g);
    for (int i = 1; i <= V; i++) {
        if (g[i].flag == 0) {
            if (buscaProf(g, i, -1)) return true;
        }
    }
    return false;
}

// Resolução problema 13
bool buscaProfRemocao(vertice* g, int i, int pai){
    g[i].flag = 1;
    NO* p = g[i].inicio;
    bool ciclo_encontrado = false;
    while (p) {
        if (g[p->adj].flag == 0) {
            if (buscaProf(g, p->adj, i)) ciclo_encontrado = true;
        } else if (p->adj != pai) {
            printf("Removendo aresta que forma ciclo: %d-%d\n", i, p->adj);
            excluiAresta(g, i, p->adj);
            ciclo_encontrado = true;
        }
        p = p->prox;
    }
    g[i].flag = 2;
    return ciclo_encontrado;
}

// Resolução problema 13
void removeArestasCiclos(vertice* g) {
    zerarFlag(g);
    for (int i = 1; i <= V; i++) {
        if (g[i].flag == 0) {
            buscaProfRemocao(g, i, -1);
        }
    }
}

// Resolução problema 14
bool buscaProfMaiorCiclo(vertice* g, int i, int pai, int cont) {
    g[i].flag = 1;
    NO* p = g[i].inicio;
    while (p) {
        if (g[p->adj].flag == 0) {
            if (buscaProf(g, p->adj, i)){
                return true;
                cont++;
            }
        } else if (p->adj != pai) {
            return true;
        }
        p = p->prox;
    }
    g[i].flag = 2;
    return false;
}

// Resolução problema 14
void achaMaiorCiclo(vertice* g) {
    zerarFlag(g);
    int max_cont = -1;
    for (int i = 1; i <= V; i++) {
        if (g[i].flag == 0) {
            int cont = 0;
            cont = buscaProfMaiorCiclo(g, i, -1, cont);

            if(cont > max_cont){
                max_cont = cont;
            }
        }
    }
    printf("Número de arestas do maior ciclo: %d \n", max_cont);
}

int main() {
    vertice *g = (vertice*)malloc((V + 1) * sizeof(vertice));
    inicializar(g);

    inserirAresta(g, 1, 2);
    inserirAresta(g, 1, 3);
    inserirAresta(g, 2, 4);
    inserirAresta(g, 3, 5);

    if (buscaCiclos(g)) {
        printf("O grafo contém ciclos.\n");
    } else {
        printf("O grafo não contém ciclos.\n");
    }

    liberarGrafo(g);
    free(g);
    return 0;
}