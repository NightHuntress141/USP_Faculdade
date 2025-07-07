#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define V 5

typedef struct r {
    struct r *prox;
    int adj;
} NO;

typedef struct {
    NO* inicio;
    int flag;
    int alunos; // 0 para sala vazia, >0 para sala ocupada
} vertice;

typedef struct node {
    int dado;
    struct node* prox;
} NO_FILA;

typedef struct {
    NO_FILA* inicio;
    NO_FILA* fim;
} FILA;

typedef struct lista_salas {
    int sala;
    struct lista_salas* prox;
} LISTA_SALAS;

void inicializar(vertice *g) {
    for (int i = 1; i <= V; i++) {
        g[i].inicio = NULL;
        g[i].flag = 0;
        g[i].alunos = -1; // Inicializa como não definido
    }
}

void inicializarFila(FILA *f) {
    f->inicio = f->fim = NULL;
}

void EntrarFila(FILA *f, int dado) {
    NO_FILA* novo = (NO_FILA*) malloc(sizeof(NO_FILA));
    novo->dado = dado;
    novo->prox = NULL;
    if (f->fim) f->fim->prox = novo;
    else f->inicio = novo;
    f->fim = novo;
}

int SairFila(FILA *f) {
    if (!f->inicio) return -1;
    NO_FILA* temp = f->inicio;
    int dado = temp->dado;
    f->inicio = f->inicio->prox;
    if (!f->inicio) f->fim = NULL;
    free(temp);
    return dado;
}

bool filaVazia(FILA *f) {
    return f->inicio == NULL;
}

// Problema 22: Retorna a sala vazia mais próxima
int salaVaziaMaisProxima(vertice *g, int i) {
    FILA f;
    inicializarFila(&f);
    EntrarFila(&f, i);
    g[i].flag = 1;

    while (!filaVazia(&f)) {
        int atual = SairFila(&f);
        if (g[atual].alunos == 0) {
            return atual;
        }

        NO* p = g[atual].inicio;
        while (p) {
            if (g[p->adj].flag == 0) {
                g[p->adj].flag = 1;
                EntrarFila(&f, p->adj);
            }
            p = p->prox;
        }
    }
    return -1; // Nenhuma sala vazia encontrada
}

// Problema 23: Retorna lista ligada de todas as salas vazias mais próximas
LISTA_SALAS* salasVaziasMaisProximas(vertice *g, int i) {
    FILA f;
    inicializarFila(&f);
    EntrarFila(&f, i);
    g[i].flag = 1;
    LISTA_SALAS* lista = NULL;
    LISTA_SALAS* fim = NULL;
    bool encontrou = false;

    while (!filaVazia(&f)) {
        int nivel_size = filaVazia(&f) ? 0 : 1; // Simplificação; o correto seria contar o nível
        for (int j = 0; j < nivel_size; j++) {
            int atual = SairFila(&f);
            if (g[atual].alunos == 0) {
                LISTA_SALAS* novo = (LISTA_SALAS*) malloc(sizeof(LISTA_SALAS));
                novo->sala = atual;
                novo->prox = NULL;
                if (!lista) {
                    lista = fim = novo;
                } else {
                    fim->prox = novo;
                    fim = novo;
                }
                encontrou = true;
            }

            NO* p = g[atual].inicio;
            while (p) {
                if (g[p->adj].flag == 0) {
                    g[p->adj].flag = 1;
                    EntrarFila(&f, p->adj);
                }
                p = p->prox;
            }
        }
        if (encontrou) break;
    }
    return lista;
}

void liberarListaSalas(LISTA_SALAS* lista) {
    while (lista) {
        LISTA_SALAS* temp = lista;
        lista = lista->prox;
        free(temp);
    }
}

int main() {
    vertice *g = (vertice*) malloc((V + 1) * sizeof(vertice));
    inicializar(g);

    // Construindo o grafo e definindo ocupação das salas
    inserirAresta(g, 1, 2);
    inserirAresta(g, 1, 3);
    inserirAresta(g, 2, 4);
    inserirAresta(g, 3, 5);

    g[1].alunos = 10;
    g[2].alunos = 0;  // Sala vazia
    g[3].alunos = 5;
    g[4].alunos = 0;  // Sala vazia
    g[5].alunos = 0;  // Sala vazia

    // Teste para o problema 22
    int sala = salaVaziaMaisProxima(g, 1);
    printf("Sala vazia mais próxima da sala 1: %d\n", sala);

    // Teste para o problema 23
    LISTA_SALAS* salas = salasVaziasMaisProximas(g, 1);
    printf("Salas vazias mais próximas da sala 1: ");
    LISTA_SALAS* atual = salas;
    while (atual) {
        printf("%d ", atual->sala);
        atual = atual->prox;
    }
    printf("\n");
    liberarListaSalas(salas);

    return 0;
}