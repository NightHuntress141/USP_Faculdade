/*
20. Um grafo não dirigido é completo se todos seus vértices são adjacentes, ou seja, existe uma aresta 
conectando cada par de vértices de um grafo. Escreva um algoritmo que, dado um grafo simples g, 
verifique se g é completo, retornando true/false conforme o caso. 
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

bool verificarCompleto(vertice* g) {
    for (int i = 1; i <= V; i++) {
        // Verifica se o vértice i tem V-1 arestas
        NO* p = g[i].inicio;
        int contador = 0;
        while (p) {
            contador++;
            p = p->prox;
        }
        if (contador != V - 1) return false;

        // Verifica se todas as arestas necessárias estão presentes
        for (int j = 1; j <= V; j++) {
            if (i != j) {
                NO* ant;
                if (!arestaExiste(g, i, j, &ant)) {
                    return false;
                }
            }
        }
    }
    return true;
}
int main() {
    vertice *g = (vertice*) malloc((V + 1) * sizeof(vertice));
    inicializar(g);

    // Construindo um grafo completo (exemplo)
    for (int i = 1; i <= V; i++) {
        for (int j = i + 1; j <= V; j++) {
            inserirAresta(g, i, j);
            inserirAresta(g, j, i); // Garante que o grafo seja não dirigido
        }
    }

    imprimirGrafo(g);

    if (verificarCompleto(g)) {
        printf("O grafo é completo.\n");
    } else {
        printf("O grafo não é completo.\n");
    }

    liberarGrafo(g);
    return 0;
}
