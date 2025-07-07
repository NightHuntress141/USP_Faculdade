/*
15. Seja um grafo g não-conexo  e não-dirigido. Escreva uma função para contar a quantidade de 
grupos disjuntos de vértices mutuamente alcançáveis em g. 
16. Variação: ao invés de contar os grupos, retornar uma lista ligada contendo os vértices do maior 
grupo identificado. Se dois ou mais grupos possuem a mesma quantidade de vértices, retornar a 
lista de vértices de qualquer um.
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

void inicializar(vertice *g){
    int i;
    for(i = 1; i <= V; i++){
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
    if (i < 0 || i >= V || j < 0 || j >= V) return false; // Verificação de limites
    NO* ant;
    if (!arestaExiste(g, i, j, &ant)) {
        NO* novo = (NO*)malloc(sizeof(NO));
        if (!novo) return false;
        novo->adj = j;
        novo->prox = g[i].inicio;
        g[i].inicio = novo;
    }
    if (!arestaExiste(g, j, i, &ant)) {
        NO* novo = (NO*)malloc(sizeof(NO));
        if (!novo) return false;
        novo->adj = i;
        novo->prox = g[j].inicio;
        g[j].inicio = novo;
    }
    return true;
}

bool excluiAresta(vertice *g, int i, int j) {
    if (i < 0 || i >= V || j < 0 || j >= V) return false;
    NO *ant;
    NO *atual = arestaExiste(g, i, j, &ant);
    if (!atual) return false;

    if (ant) 
        ant->prox = atual->prox;
    else 
        g[i].inicio = atual->prox;

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


// Problema 15
void buscaProf(vertice *g, int i) {
    g[i].flag = 1;
    NO* p = g[i].inicio;
    while (p) {
        if (g[p->adj].flag == 0) 
            buscaProf(g, p->adj);
        p = p->prox;
    }
    g[i].flag = 2;
}

// Problema 15
int contarGruposDisjuntos(vertice* g) {
    zerarFlag(g);
    int grupos = 0;
    for (int i = 1; i <= V; i++) {
        if (g[i].flag == 0) {
            buscaProf(g, i);
            grupos++;
        }
    }
    return grupos;
}

// Adiciona vértice à lista encadeada
void adicionarNaLista(NO** lista, int valor) {
    NO* novo = (NO*) malloc(sizeof(NO));
    novo->adj = valor;
    novo->prox = *lista;
    *lista = novo;
}

// Cria cópia de uma lista encadeada
NO* copiarLista(NO* origem) {
    NO* nova = NULL;
    NO* temp = origem;
    while (temp) {
        adicionarNaLista(&nova, temp->adj);
        temp = temp->prox;
    }
    return nova;
}

// Libera lista encadeada
void liberarLista(NO* lista) {
    while (lista) {
        NO* tmp = lista;
        lista = lista->prox;
        free(tmp);
    }
}

// Problema 16 - Busca com construção de lista
void buscaProfLista(vertice* g, int i, NO** grupo_atual, int* contador){
    g[i].flag = 1;
    adicionarNaLista(grupo_atual, i);
    NO* p = g[i].inicio;
    while(p){
        if(g[p->adj].flag == 0){
            (*contador)++;
            buscaProfLista(g, p->adj, grupo_atual, contador);
        }
        p = p->prox;
    }
    g[i].flag = 2;
}

// Problema 16 - Retorna lista do maior grupo
NO* listaDoMaiorGrupo(vertice* g){
    zerarFlag(g);
    int grupo_max = -1;
    NO* grupo_final = NULL;

    for(int i = 1; i <= V; i++){
        if(g[i].flag == 0){
            NO* grupo_atual = NULL;
            int contador = 1;
            buscaProfLista(g, i, &grupo_atual, &contador);

            if(contador > grupo_max){
                grupo_max = contador;
                if (grupo_final) liberarLista(grupo_final);
                grupo_final = copiarLista(grupo_atual);
            }

            liberarLista(grupo_atual);
        }
    }
    return grupo_final;
}

int main() {
    vertice *g = (vertice*)malloc((V + 1) * sizeof(vertice));
    if (!g) {
        printf("Falha na alocação de memória.\n");
        return 1;
    }

    inicializar(g);

    inserirAresta(g, 1, 2);
    inserirAresta(g, 1, 3);
    inserirAresta(g, 2, 3);
    inserirAresta(g, 4, 5);

    printf("Grafo original:\n");
    imprimirGrafo(g);

    int grupos = contarGruposDisjuntos(g);
    printf("\nQuantidade de grupos disjuntos: %d\n", grupos);

    NO* resp = listaDoMaiorGrupo(g);
    printf("Vértices do maior grupo:\n");
    while (resp) {
        printf("%d ", resp->adj);
        NO* temp = resp;
        resp = resp->prox;
        free(temp);
    }
    printf("\n");

    liberarGrafo(g);
    free(g);
    return 0;
}