#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define V 10

typedef struct r{
    struct r* prox;
    int adj;
} NO;

typedef struct{
    NO* inicio;
    int Flag;
    bool temAr;
} vertice;

/* Esta busca possui o objetivo de achar todos os vértices os quais possuem uma característica
 de possuir ar condicionado. Dessa maneira, deve retornar uma lista com tais vértices*/
void BuscaProfTodasSalas(vertice *g, int i, NO** resp){

    g[i].Flag = 1; // Acabou de ser descoberto

    if(g[i].temAr){
        NO* novo = (NO*) malloc(sizeof(NO));
        novo -> adj = i;
        novo -> prox = *resp;
        *resp = novo;
    }

    NO* p = g[i].inicio;

    /*if(g[i].temAr){
        *resp = 1;
        return;
    } */

    while(p){ 
        if(g[p -> adj].Flag == 0) BuscaProfTodasSalas(g, p -> adj, resp); // Não irá percorrer o que já foi percorrido
        p = p -> prox;
    }

    g[i].Flag = 2; // Já foi descoberto
}

/* Esta busca possui o objetivo de achar N vértices os quais possuem uma característica
 de possuir ar condicionado. Dessa maneira, deve retornar uma lista com tais vértices*/
void BuscaProfNSalas(vertice *g, int i, NO** resp, int* N){

    g[i].Flag = 1; // Acabou de ser descoberto

    if(g[i].temAr && *N > 0){
        NO* novo = (NO*) malloc(sizeof(NO));
        novo -> adj = i;
        novo -> prox = *resp;
        *resp = novo;
        *N = *N - 1;
    }

    NO* p = g[i].inicio;

    while(p){ 
        if(g[p -> adj].Flag == 0) BuscaProfNSalas(g, p -> adj, resp, N); // Não irá percorrer o que já foi percorrido
        p = p -> prox;
    }

    g[i].Flag = 2; // Já foi descoberto
}

/* Esta busca possui o objetivo de achar apenas um vértice o qual possui uma característica
 de possuir ar condicionado. Dessa maneira, deve retornar uma lista com tais vértices*/
void BuscaProf1Sala(vertice *g, int i, int *resp){

    if (*resp >= 0) return; // Se já encontramos uma sala, paramos a busca

    g[i].Flag = 1; // Acabou de ser descoberto

    NO* p = g[i].inicio;

    if(g[i].temAr){
        *resp = i;
        return;
    } 

    while(p){ 
        if(g[p -> adj].Flag == 0) BuscaProf1Sala(g, p -> adj, resp); // Não irá percorrer o que já foi percorrido
        if(*resp >= 0) return;
        p = p -> prox;
    }

    g[i].Flag = 2; // Já foi descoberto
}

void resetarFlags(vertice *g) {
    for (int i = 1; i <= V; i++) {
        g[i].Flag = 0;
    }
}

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
    vertice g[V+1];
    inicializar(g);
    
    inserirAresta(g, 1, 2);
    inserirAresta(g, 2, 3);
    inserirAresta(g, 3, 4);
    inserirAresta(g, 4, 5);
    inserirAresta(g, 5, 6);
    inserirAresta(g, 6, 7);
    inserirAresta(g, 7, 8);
    inserirAresta(g, 8, 9);
    inserirAresta(g, 9, 10);
    inserirAresta(g, 1, 10);
    
    g[3].temAr = true;
    g[6].temAr = true;
    g[9].temAr = true;
    g[1].temAr = false;
    g[2].temAr = false;
    g[4].temAr = false;
    g[5].temAr = false;
    g[7].temAr = false;
    g[8].temAr = false;
    g[10].temAr = false;
    
    NO* resp = NULL;
    int resultado = -1;
    
    resetarFlags(g);
    BuscaProfTodasSalas(g, 1, &resp);
    printf("Salas com ar condicionado encontradas: ");
    while (resp) {
        printf("%d ", resp->adj);
        NO* temp = resp;
        resp = resp->prox;
        free(temp);
    }
    printf("\n");
    
    resetarFlags(g);
    int N = 2;
    resp = NULL;
    BuscaProfNSalas(g, 1, &resp, &N);
    printf("Duas primeiras salas com ar condicionado: ");
    while (resp) {
        printf("%d ", resp->adj);
        NO* temp = resp;
        resp = resp->prox;
        free(temp);
    }
    printf("\n");
    
    resetarFlags(g);
    BuscaProf1Sala(g, 1, &resultado);
    printf("Uma sala com ar condicionado: %d\n", resultado);
    
    liberarGrafo(g);
    return 0;
}
