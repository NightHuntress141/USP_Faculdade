/* Problema 1: Dado um ponto inicial i, encontre o local mais próximo com nível de serviço bom
es 1 = serviço ruim
es 2 = serviço moderado
es 3 = serviço bom */

/* (i) modelagem 
   (ii) é um problema de busca? 
   (iii) se sim, é busca por profundidade ou largura? */

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
    int Flag;
    int es;
} vertice;

typedef struct node {
    int dado;
    struct node* prox;
} NO_FILA;

typedef struct {
    NO_FILA* inicio;
    NO_FILA* fim;
} FILA;

void inicializar(vertice *g) {
    for(int i = 1; i <= V; i++) {
        g[i].inicio = NULL;
        g[i].Flag = 0;
        g[i].es = 0;
    }
}

void resetarFlags(vertice *g) {
    for (int i = 1; i <= V; i++) {
        g[i].Flag = 0;
    }
}

NO* arestaExiste(vertice *g, int i, int j, NO** ant) {
    *ant = NULL;
    NO* p = g[i].inicio;
    while(p) {
        if(p->adj == j) return p;
        *ant = p;
        p = p->prox;
    }
    return NULL;
}

bool inserirAresta(vertice *g, int i, int j, int x) {
    NO* ant;
    NO* atual = arestaExiste(g, i, j, &ant);
    if(atual) return false;

    NO *novo = (NO*) malloc(sizeof(NO));
    novo->adj = j;
    novo->prox = g[i].inicio;
    g[i].inicio = novo;
    g[i].es = x;

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

void inicializarFila(FILA *f) {
    f->inicio = f->fim = NULL;
}

void EntrarFila(FILA *f, int dado) {
    NO_FILA* novo = (NO_FILA*) malloc(sizeof(NO_FILA));
    novo->dado = dado;
    novo->prox = NULL;
    if (f->fim) f->fim->prox = novo;
    else f->inicio = novo;
    f->fim = novo;
}

int SairFila(FILA *f) {
    if (!f->inicio) return -1;
    NO_FILA* temp = f->inicio;
    int dado = temp->dado;
    f->inicio = f->inicio->prox;
    if (!f->inicio) f->fim = NULL;
    free(temp);
    return dado;
}

bool filaVazia(FILA *f) {
    return f->inicio == NULL;
}

int largura(vertice *g, int i, int x) {
    resetarFlags(g);
    FILA F;
    inicializarFila(&F);
    EntrarFila(&F, i);
    g[i].Flag = 1;

    while (!filaVazia(&F)) {
        i = SairFila(&F);
        printf("Visitando: %d\n", i);
        g[i].Flag = 2;
        if(g[i].es == x){
            while(!filaVazia(&F)){
                SairFila(&F);
                return (i);
            }
        }
        NO* p = g[i].inicio;
        while (p) {
            if (g[p->adj].Flag == 0) {
                g[p->adj].Flag = 1;
                EntrarFila(&F, p->adj);
            }
            p = p->prox;
        }
    }

}

int main() {
    vertice *g = (vertice*) malloc((V + 1) * sizeof(vertice));
    inicializar(g);

    inserirAresta(g, 1, 2, 1);
    inserirAresta(g, 1, 3, 2);
    inserirAresta(g, 2, 4, 1);
    inserirAresta(g, 2, 5, 2);
    inserirAresta(g, 3, 5, 3);
    inserirAresta(g, 4, 5, 2);

    printf("Grafo:\n");
    imprimirGrafo(g);
    
    printf("\nBusca em Largura a partir do vértice 1 por serviços bons (3):\n");
    largura(g, 1, 3);
    
    free(g);
    return 0;
}
