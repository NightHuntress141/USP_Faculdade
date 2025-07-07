/*
17. Seja um grafo g e dois vértices a e b. Verifique se há um caminho qualquer entre a e b retornando 
true/false conforme o caso. 
18. Variação 1: contar quantos vértices há no caminho de a até b. 
19. Variação 2: retornar a lista dos vértices que compõe o caminho de a até b. 
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

// Problema 17
bool BuscaProfCaminho(vertice* g, int i, int j){
    g[i].flag = 1;
    NO* p = g[i].inicio;

    if(i == j) return true;

    while(p){
        if(g[p -> adj].flag == 0){
            if(BuscaProfCaminho(g, p -> adj, j)){
                return true;
            }
        }
        p = p -> prox;
    }
    g[i].flag = 2;
    return false;
}

// Problema 18
bool BuscaProfContaVertices(vertice* g, int i, int j, int* tamanho){
    g[i].flag = 1;
    NO* p = g[i].inicio;
    (*tamanho)++;

    if(i == j) return true;

    while(p){
        if(g[p -> adj].flag == 0){
            if(BuscaProfContaVertices(g, p -> adj, j, tamanho)){
                return true;
            }
        }
        p = p -> prox;
    }
    g[i].flag = 2;
    (*tamanho)--; // backtrack: esse caminho não leva ao destino, desfaz a contagem
    return false;
}
// Problema 19
bool BuscaProfMostraCaminho(vertice* g, int i, int j, int* caminho, int* tamanho){
    g[i].flag = 1;
    NO* p = g[i].inicio;
    caminho[*tamanho] = i;  // adiciona o vértice ao caminho
    (*tamanho)++;

    if(i == j) return true;

    while(p){
        if(g[p -> adj].flag == 0){
            if(BuscaProfMostraCaminho(g, p -> adj, j, caminho, tamanho)){
                return true;
            }
        }
        p = p -> prox;
    }
    g[i].flag = 2;
    (*tamanho)--; // backtrack: esse caminho não leva ao destino, desfaz a contagem
    return false;
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

    // Testes de caminhos
    int testes[][2] = {
        {1, 4}, // Deve retornar true
        {1, 5}, // Deve retornar true
        {2, 5}, // Deve retornar false
        {4, 2}, // Deve retornar false
        {3, 5}, // Deve retornar true
        {1, 1}  // Deve retornar true
    };

    int numTestes = sizeof(testes) / sizeof(testes[0]);

    for (int t = 0; t < numTestes; t++) {
        int origem = testes[t][0];
        int destino = testes[t][1];

        zerarFlag(g); // Resetar flags antes de cada busca
        bool resultado = BuscaProfCaminho(g, origem, destino);
        printf("Há caminho de %d até %d? %s\n", origem, destino, resultado ? "Sim" : "Não");
    }

    printf("\nContagem de vértices no caminho:\n");
    int origem = 1;
    int destino = 4;
    int contador = 0;
    zerarFlag(g);
    if (BuscaProfContaVertices(g, origem, destino, &contador)) {
        printf("Número de vértices de %d até %d: %d\n", origem, destino, contador);
    } else {
        printf("Não há caminho de %d até %d.\n", origem, destino);
    }

    printf("\nCaminho entre vértices:\n");
    int origem1 = 1;
    int destino1 = 4;
    int caminho[V +1];     // array com espaço suficiente
    int tamanho = 0;
    zerarFlag(g);

    if (BuscaProfMostraCaminho(g, origem1, destino1, caminho, &tamanho)) {
        printf("Caminho de %d até %d: ", origem1, destino1);
        for (int k = 0; k < tamanho; k++) {
            printf("%d ", caminho[k]);
        }
        printf("\n");
    } else {
        printf("Não há caminho de %d até %d.\n", origem1, destino1);
    }



    liberarGrafo(g);
    return 0;
}
