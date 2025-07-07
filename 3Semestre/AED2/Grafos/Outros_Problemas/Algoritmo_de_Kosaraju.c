#include <stdio.h>
#include <stdlib.h>

#define MAX 100

// Estrutura de Lista de Adjacência
typedef struct No {
    int vertice;
    struct No* prox;
} No;

typedef struct {
    No* lista[MAX];  // Lista de adjacência
    int visitado[MAX];
    int numVertices;
} Grafo;

// Função para criar um nó
No* criarNo(int v) {
    No* novoNo = (No*)malloc(sizeof(No));
    novoNo->vertice = v;
    novoNo->prox = NULL;
    return novoNo;
}

// Inicializa o grafo
void inicializarGrafo(Grafo* g, int numVertices) {
    g->numVertices = numVertices;
    for (int i = 0; i < numVertices; i++) {
        g->lista[i] = NULL;
        g->visitado[i] = 0;
    }
}

// Adiciona uma aresta direcionada ao grafo
void adicionarAresta(Grafo* g, int v1, int v2) {
    No* novoNo = criarNo(v2);
    novoNo->prox = g->lista[v1];
    g->lista[v1] = novoNo;
}

// Algoritmo DFS para empilhar vértices na ordem de finalização
void dfsPilha(Grafo* g, int v, int pilha[], int* topo) {
    g->visitado[v] = 1;
    
    No* atual = g->lista[v];
    while (atual != NULL) {
        if (!g->visitado[atual->vertice])
            dfsPilha(g, atual->vertice, pilha, topo);
        atual = atual->prox;
    }
    
    pilha[(*topo)++] = v; // Adiciona o vértice à pilha
}

// Cria o grafo transposto (arestas invertidas)
void transporGrafo(Grafo* g, Grafo* gt) {
    inicializarGrafo(gt, g->numVertices);
    
    for (int v = 0; v < g->numVertices; v++) {
        No* atual = g->lista[v];
        while (atual != NULL) {
            adicionarAresta(gt, atual->vertice, v); // Inverte a aresta
            atual = atual->prox;
        }
    }
}

// Algoritmo DFS para encontrar os componentes fortemente conexos no grafo transposto
void dfsComponente(Grafo* g, int v) {
    g->visitado[v] = 1;
    printf("%d ", v);
    
    No* atual = g->lista[v];
    while (atual != NULL) {
        if (!g->visitado[atual->vertice])
            dfsComponente(g, atual->vertice);
        atual = atual->prox;
    }
}

// Função principal para encontrar e imprimir os componentes fortemente conexos
void encontrarComponentesFortementeConexos(Grafo* g) {
    int pilha[MAX], topo = 0;

    // Passo 1: DFS no grafo original para empilhar vértices na ordem de finalização
    for (int v = 0; v < g->numVertices; v++) {
        if (!g->visitado[v])
            dfsPilha(g, v, pilha, &topo);
    }

    // Passo 2: Criar o grafo transposto
    Grafo gt;
    transporGrafo(g, &gt);

    // Passo 3: Processar os vértices na ordem inversa da pilha no grafo transposto
    for (int i = 0; i < g->numVertices; i++)
        gt.visitado[i] = 0;

    int contador = 0;
    while (topo > 0) {
        int v = pilha[--topo]; // Pega o próximo vértice da pilha
        
        if (!gt.visitado[v]) {
            printf("Componente %d: ", ++contador);
            dfsComponente(&gt, v);
            printf("\n");
        }
    }
}

// Função principal
int main() {
    Grafo g;
    int numVertices = 5;

    inicializarGrafo(&g, numVertices);

    adicionarAresta(&g, 0, 2);
    adicionarAresta(&g, 2, 1);
    adicionarAresta(&g, 1, 0);
    adicionarAresta(&g, 1, 3);
    adicionarAresta(&g, 3, 4);

    printf("Componentes Fortemente Conexos:\n");
    encontrarComponentesFortementeConexos(&g);

    return 0;
}
