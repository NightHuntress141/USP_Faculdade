/*
10. Considere um grafo dirigido em lista de adjacências representando uma rede de troca de emails, 
onde cada vértice representa um usuário, e cada aresta representa um email enviado. Cada aresta 
possui um campo int id que representa o conteúdo da mensagem (ou seja, o campo id faz parte da 
definição do nó das listas de adjacências). 
    Problema: circula pela rede uma mensagem x do tipo spam. Escreva um 
    algoritmo para exibir os usuários suspeitos de iniciar a propagação de x. Um 
    usuário é considerado suspeito se ele próprio não recebeu a mensagem x nenhuma vez.
-> Necessitamos verificar para cada vértice i apontada para um j especifico, se possui ou não mensagem do tipo x
*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define V 5

typedef struct r{
    struct r *prox;
    int adj;
    int id; // Considere 0 para mensagem normal e 1 para mensagem do tipo x (isto é, possívelmente spam)
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

bool inserirAresta(vertice *g, int i, int j, int id_msg){
    // Criamos um ponteiro auxiliar que indicara o vértice anterior
    NO* ant;
    // Recebemos o valor achado que indica o vértice i que aponta para j
    NO* atual = arestaExiste(g, i, j, &ant);

    if(atual) return false; //Já existe

    NO *novo = (NO*) malloc(sizeof(NO)); // Alocamos um novo espaço na mémoria

    novo->adj = j; // Coloca o valor do vértice j
    novo->id = id_msg; 
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

void checarSpam(vertice* g){
    // Inicialização da estrutura auxiliar que guardara os suspeitos
    int mandou_x[V + 1];
    int recebeu_x[V + 1];
    for(int k = 1; k <= V; k++){
        mandou_x[k] = 0;
        recebeu_x[k] = 0;
    }

        for(int i = 1; i <= V; i++){ //Verificar a relação de cada vértice
            NO* p = g[i].inicio;
            while(p){
                if(p -> id == 1){
                    mandou_x[i]++;
                    recebeu_x[p -> adj]++;
                }
                p = p -> prox;
            }
        }


    // Avaliando suspeitos
    for(int j = 1; j <= V; j++){
        if(mandou_x[j] >= 1 && recebeu_x[j] == 0){
            printf("Suspeito identificado: %d \n", j);
        }
    }

}

int main() {
    vertice *g = (vertice*) malloc((V + 1) * sizeof(vertice));
    inicializar(g);

    inserirAresta(g, 1, 2, 1); // Enviando spam (id = 1)
    inserirAresta(g, 1, 3, 0); // Email normal (id = 0)
    inserirAresta(g, 2, 4, 1); // Spam
    inserirAresta(g, 3, 5, 1); // Spam
    
    checarSpam(g);

    

    liberarGrafo(g);
    return 0;
}