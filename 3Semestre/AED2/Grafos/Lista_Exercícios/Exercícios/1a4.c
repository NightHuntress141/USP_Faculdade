/* Exercícios:
1. Escreva um algoritmo para contar a quantidade de laços em um grafo. 
2. Variação: remover todos os laços encontrados. 
3. Escreva um algoritmo para destruir as arestas de um grafo, tornando-o vazio. 
4. Seja um grafo g dirigido. Escreva um algoritmo para retornar o grafo transposto de g.
*/

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
} vertice;

void inicializar(vertice *g){
    int i;
    for(i = 1; i <= V; i++) g[i].inicio = NULL;
}

// Essa função é responsável por verificar se existe uma aresta que aponta de um vértice i para um vértice j e
// retorna um ponteiro para uma estrutura do tipo NO
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

// Exclui-se uma aresta de um vértice i (origem da aresta) que aponta para o vértice i (destino da aresta)
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

//Percorre a lista e soma para saber o grau de saida de um dado vértice i
int GrauSaida(vertice *g, int i){
    int soma = 0;
    NO* p = g[i].inicio;
    // Percorre a lista daquele vértice até o final contando todas as arestas
    while(p){
        soma++;
        p = p -> prox;
    }
    return soma;
}

//Percorre as listas e soma para saber o grau de entrada de um dado vértice i
int GrauEntrada(vertice *g, int i){
    int soma = 0;
    int j;
    for(j = 1; j <= V; j++){
        NO* p = g[j].inicio;
        // Percorre uma lista de cada vez
        while(p){
            if(p -> adj == i) soma++;
            p = p -> prox;
        }
    }
    return soma;
}

// A função abaixo copia um grafo, retornando um ponteiro para a estrutura do tipo vértice
vertice* copiaGrafo(vertice *g){
    vertice* h = (vertice*) malloc (sizeof(vertice) * (V + 1));
    int j;
    for(int i = 1; i <= V; i++){
        NO* p = g[i].inicio;
        h[i].inicio = NULL;
        while (p){
            NO* novo = (NO*) malloc (sizeof(NO));
            novo -> adj = p -> adj;
            novo -> prox = h[i].inicio; //Sempre adicionando no começo da lista daquele vértice
            h[i].inicio = novo;
            p = p -> prox;
        }
    }
    return h;
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

// Exercício 1 -> Não é um problema de busca
// A função retorna o número de laços de um grafo
int laços(vertice* g){
    int cont = 0;
    for(int i = 1; i <= V; i++){
        NO* p = g[i].inicio;
        while(p){
            if(p -> adj == i) cont++;
            p = p -> prox;
        }
    }
    return cont;
}

// Exercício 2 -> Não é um problema de busca
// A função retorna o grafo removido de seus laço
void removerLaços(vertice* g){
    for(int i = 1; i <= V; i++){
        NO* atual = g[i].inicio;
        NO* ant = NULL;
        while(atual){
            NO* prox = atual -> prox;
            if(atual -> adj == i){
                if(ant) ant -> prox = prox; //Nesse caso, o laço a ser removido não está no começo da lista
                else g[i].inicio = prox;
                free(atual);
            }
            else ant = atual;
            atual = prox;
        }
    }
}

// Exercício 3 -> Não é um problema de busca
// A função retorna um grafo sem arestas, mas mantem as informações do vértice
void removerTodasArestas(vertice* g) {
    for (int i = 1; i <= V; i++) {
        NO* atual = g[i].inicio;
        
        while (atual) { // Percorre a lista de adjacência do vértice i
            NO* prox = atual -> prox; // Salva o próximo nó antes de remover o atual
            free(atual); // Libera a memória do nó atual
            atual = prox; // Avança para o próximo nó
        }

        g[i].inicio = NULL; // Após a remoção de todas as arestas, a lista deve estar vazia
    }
}

// Exercício 4 -> Não é um problema de busca
// A função retorna um novo grafo h, transposto de g
void CriarTransposto(vertice* g, vertice* gt) {
    // Inicializa o grafo transposto sem arestas
    for (int i = 1; i <= V; i++) {
        gt[i].inicio = NULL;
    }

    // Percorre todas as listas de adjacência do grafo original
    for (int i = 1; i <= V; i++) {
        NO* atual = g[i].inicio;
        while (atual) {
            inserirAresta(gt, atual->adj, i); // Inverte a direção da aresta
            atual = atual->prox;
        }
    }
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
    inserirAresta(g, 1, 1); // AQUI HÁ UM LAÇO

    printf("Grafo original:\n");
    imprimirGrafo(g);

    int quantidade_laços;
    quantidade_laços = laços(g);
    printf("Quantidade de laços: %d \n", quantidade_laços);

    removerLaços(g);
    printf("Grafo com laços removidos:\n");
    imprimirGrafo(g);    
 

    liberarGrafo(g);
    return 0;
}