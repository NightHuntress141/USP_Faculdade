/*
-> Códigos fundamentais para Grafos:
    - Inicialização
    - Verificar se aresta existe 
    - Adicionar aresta
    - Excluir aresta 
    - Copiar Grafo
    - Grau de Saída e Entrada
    - Desalocar um Grafo
*/

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define V 4 // Número de vértice que existem no grafo

typedef struct{
    int matriz[V + 1][V + 1]; 
    int flag[V + 1];
} Grafo;

typedef struct node {
    int dado;
    struct node* prox;
} NO_FILA;

typedef struct {
    NO_FILA* inicio;
    NO_FILA* fim;
} FILA;


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

void inicializarFila(FILA *f) {
    f->inicio = f->fim = NULL;
}

void entrarFila(FILA *f, int dado) {
    NO_FILA* novo = (NO_FILA*) malloc(sizeof(NO_FILA));
    novo->dado = dado;
    novo->prox = NULL;
    if (f->fim) f->fim->prox = novo;
    else f->inicio = novo;
    f->fim = novo;
}

int sairFila(FILA *f) {
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

void buscaProf(Grafo *g, int i){
    zerarFlags(g);
    printf("%d ", i);
    g -> flag[i] = 1; // Descoberto
    for(int j = 1; j <= V; j++){ // A partir de todos os vértices existentes
        if(g -> matriz[i][j] == 1 && g -> flag[j] == 0){
            buscaProf(g, j);
        }
    }
    g -> flag[i] = 2;
}

void buscaLargura(Grafo* g, int i){
    // Inicialização
    zerarFlags(g);
    FILA f;
    inicializarFila(&f);
    entrarFila(&f, i);
    g -> flag[i] = 1; // Acabou de ser descoberto

    while(!filaVazia(&f)){ // Enquanto houver elementos na fila
        i = sairFila(&f);
        printf("%d ", i);
        g -> flag[i] = 2; // Acabou de ser processado
        for(int j = 1; j <= V; j++){
            if(g -> matriz[i][j] == 1 && g->flag[j] == 0){
                entrarFila(&f, j);
                g -> flag[j] = 1;
            }
        }

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
    

    return 0;
}