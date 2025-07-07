/*
8 - Sejam dois grafos g1 e g2 contendo exatamente os mesmos vértices. Verifique se g2 é um subgrafo 
de g1, retornando true/false conforme o caso. Para tornar o problema mais interessante, considere 
que um grafo é representado em listas e outro em matriz.
    É um problema de busca? Não, pois queremos conferir se é um subgrafo, logo se as relações de g2 
    são as mesmas que g1, podendo haver menos, mas nunca a mais e diferentes de contidas em g1
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

bool verificarSubgrafo(vertice* g, vertice* h){
    for(int i = 1; i <= V; i++){
        NO* k = h[i].inicio; 
        while(k){
            NO* p = g[i].inicio; // Resetamos p a cada nova iteração de k
            bool encontrado = false;
            while(p){
                if(k->adj == p->adj) {
                    encontrado = true;
                    break; // Encontrou a aresta, pode parar a busca
                }
                p = p->prox;
            }
            if (!encontrado) return false; // Se a aresta não existe em g, retorna falso
            k = k->prox;
        }
    }
    return true; // Se todas as arestas de h estão em g, retorna verdadeiro
}

int main() {
    vertice *g = (vertice*) malloc((V + 1) * sizeof(vertice));
    vertice *h = (vertice*) malloc((V + 1) * sizeof(vertice));
    inicializar(g);
    inicializar(h);

    inserirAresta(g, 1, 2);
    inserirAresta(g, 1, 3);
    inserirAresta(g, 2, 4);
    inserirAresta(g, 3, 5);
    inserirAresta(h, 1, 2);
    inserirAresta(h, 2, 4);

    if (verificarSubgrafo(g, h))
        printf("h é subgrafo de g\n");
    else
        printf("h NÃO é subgrafo de g\n");

    liberarGrafo(g);
    return 0;
}