#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define V 5

typedef struct r{
    // O campo prox é um ponteiro para o próximo nó da lista, permitindo criar listas encadeadas.
    struct r *prox;
    // O campo adj armazena o valor de um vértice adjacente 
    int adj;
    // Aqui, também poderia caber um campo "peso" para indicar valores em grafos ponderados
} NO;

typedef struct{
    // Possui apenas a cabeça da lista de adjacencia
    NO* inicio;
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

// Função de busca por profundidade que possui como entrada o grafo a ser analisado e o vértice i que começa a busca
void BuscaProf(vertice *g, int i){
    g[i].Flag = 1; // Acabou de ser descoberto
    NO* p = g[i].inicio;
    while(p){ // Percorre a lista 
        if(g[p -> adj].Flag == 0) BuscaProf(g, p -> adj); // Não irá percorrer o que já foi percorrido
        p = p -> prox;
    }
    g[i].Flag = 2; // Já foi descoberto
}

void resetarFlags(vertice *g) {
    for (int i = 1; i <= V; i++) {
        g[i].Flag = 0;
    }
}

void testarBuscaProf(vertice *g, int inicio) {
    printf("\nExecutando busca em profundidade a partir do vértice %d...\n", inicio);
    resetarFlags(g);
    BuscaProf(g, inicio);

    printf("Estado dos vértices após a busca:\n");
    for (int i = 1; i <= V; i++) {
        printf("Vértice %d: Flag = %d\n", i, g[i].Flag);
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

int main(){
    vertice *g = (vertice*) malloc((V+1) * sizeof(vertice));
    inicializar(g);

    printf("Inserindo arestas...\n");
    inserirAresta(g, 1, 2);
    inserirAresta(g, 1, 3);
    inserirAresta(g, 2, 4);
    inserirAresta(g, 3, 4);
    inserirAresta(g, 4, 5);

    printf("Grafo original:\n");
    imprimirGrafo(g);

    // Testando busca por profundidade a partir de diferentes vértices
    testarBuscaProf(g, 1);
    testarBuscaProf(g, 3);
    testarBuscaProf(g, 5);

    liberarGrafo(g);
    return 0;
}