#include <stdio.h>
#include <malloc.h>
#define true 1
#define false 0
typedef int bool;
typedef enum {esquerdo, direito} LADO;
typedef char TIPOCHAVE;

typedef struct aux {
    TIPOCHAVE chave;
    struct aux *esq, *dir;
} NO, *PONT;

PONT buscarChave(TIPOCHAVE ch, PONT raiz) {
    if (raiz == NULL) return NULL;
    if (raiz->chave == ch) return raiz;
    PONT aux = buscarChave(ch, raiz->esq);
    if (aux) return aux;
    return buscarChave(ch, raiz->dir);
}

PONT criarNovoNo(TIPOCHAVE ch) {
    PONT novoNo = (PONT)malloc(sizeof(NO));
    novoNo->esq = NULL;
    novoNo->dir = NULL;
    novoNo->chave = ch;
    return novoNo;
}

bool inserirFilho(PONT raiz, TIPOCHAVE novaChave, TIPOCHAVE chavePai, LADO lado) {
    PONT pai = buscarChave(chavePai, raiz);
    if (!pai) return false;
    PONT novo = criarNovoNo(novaChave);
    if (lado == esquerdo) {
        novo->esq = pai->esq;
        pai->esq = novo;
    } else {
        novo->esq = pai->dir;
        pai->dir = novo;
    }
    return true;
}

void exibirArvore(PONT raiz) {
    if (raiz == NULL) return;
    printf("%c ", raiz->chave);
    exibirArvore(raiz->esq);
    exibirArvore(raiz->dir);
}

int max(int a, int b) {
    if (a > b) return a;
    return b;
}
int funcao2(PONT raiz) {
    if (!raiz) return -1;
    int e = funcao2(raiz->esq);
    int d = funcao2(raiz->dir);
    return 1 + max(e, d);
}

int funcao1(PONT raiz) {
    if (!raiz) return 0;
    return 1 + funcao1(raiz->esq) + funcao1(raiz->dir);
}

void inicializar(PONT *raiz) {
    *raiz = NULL;
}

void criarRaiz(PONT *raiz, TIPOCHAVE ch) {
    *raiz = criarNovoNo(ch);
}

int main() {
    PONT raiz;
    inicializar(&raiz);
    criarRaiz(&raiz, 'a');
    inserirFilho(raiz, 'b', 'a', esquerdo);
    inserirFilho(raiz, 'c', 'a', direito);
    printf("Funcao1 [parte 1]: %i.\n", funcao1(raiz));
    printf("Funcao2 [parte 1]: %i.\n", funcao2(raiz));
    exibirArvore(raiz);
    printf("\n");

    inserirFilho(raiz, 'd', 'c', esquerdo);
    inserirFilho(raiz, 'e', 'b', esquerdo);
    inserirFilho(raiz, 'f', 'a', esquerdo);
    inserirFilho(raiz, 'g', 'a', esquerdo);
    printf("Funcao1 [parte 2]: %i.\n", funcao1(raiz));
    printf("Funcao2 [parte 2]: %i.\n", funcao2(raiz));
    exibirArvore(raiz);
    printf("\n");

    inserirFilho(raiz, 'h', 'g', esquerdo);
    inserirFilho(raiz, 'i', 'h', direito);
    printf("Funcao1 [parte 3]: %i.\n", funcao1(raiz));
    printf("Funcao2 [parte 3]: %i.\n", funcao2(raiz));

    return 0;
}
