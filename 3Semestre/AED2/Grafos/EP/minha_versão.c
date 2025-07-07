#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <stdbool.h>

/*
-> Funções complementares:
- Todas relacionadas a fila -> Inicializar, entrar, sair, vazia (FEITO)
- Todas relacionadas a lista -> adicionar, imprimir (FEITO)
- Todas relacionadas a grafos -> Inicializar, aresta existe, adicionar, imprimir, zerar flags (FEITO)

-> Passo a passo:
- Transformamos em um grafo (FEITO)
- Fazemos uma lista de distâncias dos outros vértices com busca em largura para o vértice v1 (Função Busca em Largura) -> (FEITO)
- Fazemos uma lista de distâncias dos outros vértices com busca em largura para o vértice v2 (Função Busca em Largura) -> (FEITO)
- Comparamos essas listas descontando os próprios valores de v1 e v2 e retornamos uma lista (Função equidistantes)
*/

// Estruturas: Grafos + Lista + Fila
typedef struct estr {
      int adj;
      struct estr *prox;
} NO;

typedef struct{
    NO* inicio;
    int flag;
} VERTICE;

typedef struct {
    NO* inicio;
    NO* fim;
} FILA;

// Funções da Fila
void InicializarFila(FILA *f) {
    f -> inicio = f -> fim = NULL;
}

void EntrarFila(FILA* f, int adj) {
    NO* novo = (NO*) malloc(sizeof(NO));
    novo -> adj = adj;
    novo -> prox = NULL;
    if (f -> fim) f -> fim -> prox = novo;
    else f -> inicio = novo;
    f -> fim = novo;
}

int SairFila(FILA* f) {
    if (!f -> inicio) return -1;
    NO* temp = f -> inicio;
    int adj = temp -> adj;
    f -> inicio = f -> inicio -> prox;
    if (!f -> inicio) f -> fim = NULL;
    free(temp);
    return adj;
}

bool FilaVazia(FILA* f) {
    return f -> inicio == NULL;
}

// Funções lista
void InserirLista(NO** lista, int valor){
    NO* novo = (NO*) malloc(sizeof(NO));
    novo -> adj = valor;
    novo -> prox = *lista;
    *lista = novo;
}

void ImprimirLista(NO* lista) {
    printf("\n\n Imprimindo lista de resposta:\n");
    while (lista) {
        printf(" -> %d", lista -> adj);
        lista = lista -> prox;
    }
    printf("\n");
}

// Funções Grafos
void InserirAresta(VERTICE* g, int i, int j) {
    NO* ida = (NO*)malloc(sizeof(NO));
    if (!ida) return;
    ida->adj = j;
    ida->prox = g[i].inicio;
    g[i].inicio = ida;

    NO* volta = (NO*)malloc(sizeof(NO));
    if (!volta) return;
    volta->adj = i;
    volta->prox = g[j].inicio;
    g[j].inicio = volta;
} 

void InicializarGrafo(VERTICE *g, int V){
    int i;
    for(i = 1; i <= V; i++){
        g[i].inicio = NULL;
        g[i].flag = 0;
    }
}

void ImprimirGrafo(VERTICE* g, int V) {
    for (int i = 1; i <= V; i++) {
        printf("Vertice %d:", i);
        NO* p = g[i].inicio;
        while (p) {
            printf(" -> %d", p->adj);
            p = p->prox;
        }
        printf("\n");
    }
}

VERTICE* TransformarEmGrafo(int V, int A, int ij[]){
    VERTICE* g = (VERTICE*) malloc((V + 1) * sizeof(VERTICE));
    InicializarGrafo(g, V);
    int checar = 0;
    for(int k = 0; k < A*2; k++){
        if(!(k % 2 == 0)) continue;
        InserirAresta(g, ij[k], ij[k+1]);
        checar++;
    }
    if(checar != A){
        printf("O grafo nao esta com as mesmas quantidades de arestas pedidas \n\n");
    }
    printf("Grafo criado a partir do vetor passado: \n\n");
    ImprimirGrafo(g, V);
    return g;
}

void ZerarFlag(VERTICE* g, int V) {
    for (int i = 1; i <= V; i++) {
        g[i].flag = 0;
    }
}

void BuscaLargura (VERTICE* g, int V, int i, int distancias[]) {
    ZerarFlag(g, V);
    FILA f;
    InicializarFila(&f);
    EntrarFila(&f, i);
    g[i].flag = 1;
    distancias[i] = 0;
    
    while (!FilaVazia(&f)) {
        int atual = SairFila(&f);
        g[atual].flag = 2;
        
        NO* p = g[atual].inicio;
        while (p) {
            if (g[p -> adj].flag == 0) {
                g[p -> adj].flag = 1;
                distancias[p -> adj] = distancias[atual] + 1;
                EntrarFila(&f, p -> adj);
            }
            p = p->prox;
        }
    }
    
    printf("\n\n Vertices relacionados a %d:\n", i);
    for (int k = 1; k <= V; k++) {
        if (k == i) continue;
        if (distancias[k] != -1) {
            printf("Distancia entre %d e %d: %d \n", i, k, distancias[k]);
        }
    }
}

// Grafo de V vértices numeradas de 1 a V e A arestas. O vetor ij[] contém exatamente 2*A elementos, e cada par representa uma aresta i,j. 
NO* equidistantes(int V, int A, int ij[], int v1, int v2);

NO* equidistantes(int V, int A, int ij[], int v1, int v2){
	NO* resp = NULL;

    int distancias_v1[1+V];
    int distancias_v2[1+V];

    for(int k = 0; k <= V; k++){
        distancias_v1[k] = -1;
        distancias_v2[k] = -1;
    }

    VERTICE* g = TransformarEmGrafo(V, A, ij);
    BuscaLargura(g, V, v1, distancias_v1);
    BuscaLargura(g, V, v2, distancias_v2);

    for(int h = 1; h <= V; h++){
        if(distancias_v1[h] == distancias_v2[h] && distancias_v1[h] > 0 && distancias_v2[h] > 0){
            InserirLista(&resp, h);
        }
    }

    ImprimirLista(resp);

	return resp;
}

int main() {
    int ij[] = {1, 2, 1, 3, 2, 4, 3, 4}; // Exemplo de arestas
    int V = 4, A = 4;
    int v1 = 1, v2 = 2;

    NO* resultado = equidistantes(V, A, ij, v1, v2);

    while (resultado) {
        NO* temp = resultado;
        resultado = resultado->prox;
        free(temp);
    }

    return 0;
}

