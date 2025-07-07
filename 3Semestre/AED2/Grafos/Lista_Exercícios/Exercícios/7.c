/* 7. Seja um grafo g não-dirigido ponderado (com um peso inteiro associado a cada aresta). Escreva um 
algoritmo que, dado g e um custo mínimo int c, retorne uma cópia de g contendo apenas as arestas 
de custo maior do que c. 
    É um problema de busca? Não, pois não estamos avaliando caminhos em si, mas apenas tipos de arestas*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define V 5
#define c 2

typedef struct r{
    struct r *prox;
    int adj;
    int peso;
} NO;

typedef struct{
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

bool inserirAresta(vertice *g, int i, int j, int peso){
    NO* ant;
    NO* atual = arestaExiste(g, i, j, &ant);

    if(atual) return false; //Já existe

    NO *novo = (NO*) malloc(sizeof(NO)); // Alocamos um novo espaço na mémoria

    novo->adj = j; // Coloca o valor do vértice j
    novo->prox = g[i].inicio; // Faz com que o novo (j) aponte como proximo o vértice (i)
    novo->peso = peso;

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

vertice* GerarCopiaMaiorC(vertice* g){
    vertice *h = (vertice*) malloc((V + 1) * sizeof(vertice));
    inicializar(h);
    for(int i = 0; i <= V; i++){
        NO* p = g[i].inicio;
        while(p){
            if(p -> peso >= c) inserirAresta(h, i, p -> adj, p -> peso);
            p = p -> prox;
        }
    }
    return h;
}

int main() {
    vertice *g = (vertice*) malloc((V+1) * sizeof(vertice));
    inicializar(g);

    printf("Inserindo arestas...\n");
    inserirAresta(g, 1, 2, 1);
    inserirAresta(g, 1, 3, 2);
    inserirAresta(g, 2, 4, 0);
    inserirAresta(g, 3, 4, 0);
    inserirAresta(g, 4, 5, 1);

    printf("Grafo original:\n");
    imprimirGrafo(g);

    printf("Grafo apenas com arestas de peso igual ou maior que c \n");
    vertice* h = GerarCopiaMaiorC(g);
    imprimirGrafo(h);

    liberarGrafo(g);
    liberarGrafo(h);
    return 0;
}