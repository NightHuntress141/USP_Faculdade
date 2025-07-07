/* Análise de problemas com grafos:
- Modelagem da estrutura do grafo 
- É um problema de busca? (Tem que estar preocupado com as coisas que são alcançaveis e como fazer isso)
    - É uma busca de profundidade ou largura */

/* Problema 1: como achar os valores de um grafo desconexo NÃO DIRIGIDO a partir da busca
com profundidade. Nesse caso, devemos procurar, após uma busca a partir de tal vértice, se há
flags zerados, logo devemos procurar até todos os flags possuirem valores maiores do que 0*/

/* Problema 2: Como achar a maior comunidade? */

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

// Função de busca por profundidade que possui como entrada o grafo a ser analisado e o vértice i para ser encontrado
void BuscaProfProblema1(vertice *g, int i){
    g[i].Flag = 1; // Acabou de ser descoberto
    NO* p = g[i].inicio;
    while(p){
        if(g[p -> adj].Flag == 0) BuscaProf(g, p -> adj); // Não irá percorrer o que já foi percorrido
        p = p -> prox;
    }
    g[i].Flag = 2; // Já foi descoberto
    printf("%d", i); // Resolução do problema 1
}

// Função de busca por profundidade que possui como entrada o grafo a ser analisado e o vértice i para ser encontrado
void BuscaProfProblema2(vertice *g, int i){
    g[i].Flag = 1; // Acabou de ser descoberto
    NO* p = g[i].inicio;
    while(p){
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

    resetarFlags(&g);

    // Resolução do problema 1
    while(true){
        int i = 0; // Inválido
        for(int j = 1; j<=V; j++){
            if(g[i].Flag == 0){
                i = j;
                break;
            }
        }
        if(i == 0) break;; // Fim
        BuscaProfProblema1(g, i);
        printf("\n");
    }

    // Resolução problema 2
    int maior = 0;
    int contagem = 0;
    BuscaProfProblema2(g, i, &contagem);
    if(contagem > maior) maior = contagem;



    return 0;
}