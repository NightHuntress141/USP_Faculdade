#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct aux{
    int chave;
    struct aux* esq;
    struct aux* dir;
    int h;
}NO, *PONT;

PONT criaNo (int chave_nova){
    PONT novo_no = (PONT) malloc(sizeof(NO));
    novo_no -> chave = chave_nova;
    novo_no -> esq = NULL;
    novo_no -> dir = NULL;
    novo_no -> h = 0;
    return novo_no;
}

PONT inicializa(){
    return NULL;
}

int max(int a, int b){
    if (a > b) return a;
    return b;
}

//Função relativa a rotação para direita
PONT direita(PONT r){
    PONT aux;
    aux = r -> esq;
    r -> esq = aux -> dir;
    aux -> dir = r;

    //max é a função que compara dois valores e retorna o maior
    r -> h = max(altura(r -> dir), altura(r -> esq)) + 1;
    aux -> h = max(altura(aux -> esq), r -> h) + 1;

    return aux;
}

//Função relativa a rotação para esquerda
PONT esquerda(PONT p){
    PONT u;
    PONT v;
    //u (filho do problema) vai receber o esdereço do filho a esquerda
    u = p -> esq;
    if (u -> )
}

//Rotação dupla
PONT esquerdaDireita(PONT r){
    r -> esq = esquerda(r -> esq);
    return direita(r);
}

//Rotação dupla
PONT esquerdaEsquerda(PONT r){
    r -> dir = direita(r -> dir);
    return esquerda(r);
}

int altura (PONT raiz){
    if (!raiz) return -1;
    return raiz -> h;
}


/* 
Para inserir elementos devemos calcular o fator de balanceamento de cada nó, para isso temos que:
- Possuir uma função que calcula a altura de casa subárvore
- Funções de rotação caso desbalanceio
*/

int main(){
    PONT r = inicializa();

    return 0;
}