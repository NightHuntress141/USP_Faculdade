/*
24. Para  todos  os  vértices  de  um  grafo,  calcular  o  tamanho  do  caminho  mais  curto  a  partir  de  um 
vértice inicial i. 
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define V 5

typedef struct r{
    struct r *prox;
    int adj;
} NO;

typedef struct{
    NO* inicio;
    int flag;
} vertice;

typedef struct node {
    int dado;
    struct node* prox;
} NO_FILA;

typedef struct {
    NO_FILA* inicio;
    NO_FILA* fim;
} FILA;

void inicializar(vertice *g){
    int i;
    for(i = 1; i <= V; i++){
        g[i].inicio = NULL;
        g[i].flag = 0;
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

bool excluiAresta(vertice *g, int i, int j) {
    // Criamos um ponteiro auxiliar que indicara o vértice anterior
    NO *ant;
    // Recebemos o valor achado que indica o vértice i que aponta para j
    NO *atual = arestaExiste(g, i, j, &ant);

    if (!atual) return false; //Não existe, não tem como excluir

    // Se existe um anterior, então apenas aponte para o próximo
    if (ant) 
        ant->prox = atual->prox;
    // Caso contrário, se o elemento está no início da lista
    else 
        g[i].inicio = atual->prox;

    free(atual); // Libera espaço

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
    free(g);
}

void zerarFlag(vertice* g){
    for(int i = 1; i <= V; i++){
        g[i].flag = 0;
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

void caminhoMaiscurto(vertice* g, int i) {
    zerarFlag(g);
    int distancias[V + 1]; // Índices de 1 a V
    for (int k = 1; k <= V; k++) {
        distancias[k] = -1; // Inicializa com -1 (inacessível)
    }
    
    FILA f;
    inicializarFila(&f);
    entrarFila(&f, i);
    g[i].flag = 1;
    distancias[i] = 0;
    
    while (!filaVazia(&f)) {
        int atual = sairFila(&f);
        g[atual].flag = 2;
        
        NO* p = g[atual].inicio;
        while (p) {
            if (g[p->adj].flag == 0) {
                g[p->adj].flag = 1;
                distancias[p->adj] = distancias[atual] + 1;
                entrarFila(&f, p->adj);
            }
            p = p->prox;
        }
    }
    
    // Imprime as distâncias
    for (int k = 1; k <= V; k++) {
        if (k == i) continue;
        if (distancias[k] != -1) {
            printf("Caminho mais curto entre %d e %d é %d\n", i, k, distancias[k]);
        } else {
            printf("Não há caminho entre %d e %d\n", i, k);
        }
    }
}

int main() {
    vertice *g = (vertice*) malloc((V + 1) * sizeof(vertice));
    inicializar(g);

    // Construindo o grafo
    inserirAresta(g, 1, 2);
    inserirAresta(g, 1, 3);
    inserirAresta(g, 2, 4);
    inserirAresta(g, 3, 5);

    imprimirGrafo(g);
    
    printf("\nCaminhos mais curtos a partir do vértice 1:\n");
    caminhoMaiscurto(g, 1);
   
    liberarGrafo(g);
    return 0;
}
