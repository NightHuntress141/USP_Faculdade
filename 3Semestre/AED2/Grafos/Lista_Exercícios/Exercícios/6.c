/*
6. Uma árvore enraizada é um grafo acíclico, conexo e dirigido, com um único vértice fonte de onde 
todas as arestas partem. Escreva um algoritmo que, dado um grafo g, verifique se é uma árvore 
enraizada ou não, retornando true/false conforme o caso. 
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
    for(i = 1; i <= V; i++) g[i].inicio = NULL;
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

int GrauEntrada(vertice *g, int i){
    int soma = 0;
    NO* p = g[i].inicio;
    while(p){
        soma++;
        p = p -> prox;
    }
    return soma;
}

void zerarFlag(vertice* g){
    for(int i = 1; i <= V; i++){
        g[i].flag = 0;
    }
}

// Exercício 6 -> É um problema de busca, pois devemos checar para ver se há caminhos ciclicos ou não
/* O que deve ser checado?
Apenas um vértice deve ter grau de entrada igual a zero (nenhuma aresta entrando) e todos os 
outros vértices devem ter exatamente um pai (grau de entrada igual a 1).*/
bool checarGrausVerticesArvore(vertice *g) {
    int raiz = 0;
    for (int i = 1; i <= V; i++) {
        int grau = grauEntrada(g, i);
        if (grau == 0) raiz++;
        else if (grau > 1) return false;
    }
    return raiz == 1;
}

bool buscaProf(vertice *g, int i) {
    g[i].flag = 1; // Vértice está sendo visitado
    NO* p = g[i].inicio;
    while (p) {
        if (g[p->adj].flag == 1) return true; // Encontrou um ciclo
        if (g[p->adj].flag == 0 && buscaProf(g, p->adj)) return true;
        p = p->prox;
    }
    g[i].flag = 2; // Vértice já foi completamente processado
    return false;
}

//Se encontrarmos um vértice que já está na pilha de recursão flag = 1, identificamos um ciclo.
bool checarCiclo(vertice *g) {
    for (int i = 1; i <= V; i++) g[i].flag = 0; // Resetar flags
    for (int i = 1; i <= V; i++) {
        if (g[i].flag == 0 && buscaProf(g, i)) return true;
    }
    return false;
}

bool testeArvoreEnraizada(vertice *g) {
    return checarGrausVerticesArvore(g) && !checarCiclo(g);
}

int main() {
    vertice *g = (vertice*) malloc((V + 1) * sizeof(vertice));
    inicializar(g);

    inserirAresta(g, 1, 2);
    inserirAresta(g, 1, 3);
    inserirAresta(g, 2, 4);
    inserirAresta(g, 3, 5);
    
    if (testeArvoreEnraizada(g))
        printf("O grafo é uma árvore enraizada.\n");
    else
        printf("O grafo NÃO é uma árvore enraizada.\n");
    
    free(g);
    return 0;
}