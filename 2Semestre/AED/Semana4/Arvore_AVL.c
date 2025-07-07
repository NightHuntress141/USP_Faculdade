#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct NO_ {
	struct NO_ *esq;
	struct NO_ *dir;
	int val;        //Guarda o valor dentro do nó
	int bal;        //Guarda o fator de balanceamento
} NO, *PONT;

//Essa função retorna quem virou a nova raiz depois da rotação a esquerda
PONT rotacaoLL(PONT p){
    //Define o filho e o neto do nó com problema
    PONT u, v;
    //u (filho do problema) vai receber o endereço do filho da esquerda do problema
    u = p -> esq;
    //Se o balanceamento do filho do nó com problema for -1
    if (u -> bal == -1){
        //p vai apontar para o filho no qual o seu antigo filho apontava para direita
        p -> esq = u -> dir;
        //p vira filho a direita de u
        u -> dir = p;
        p -> bal = 0;
        u -> bal = 0;
        //u toma o lugar de p
        return u;
    }
    if (u -> bal == 1){
        v = u -> dir;
        u -> dir = v -> esq;
        v -> esq = u;
        p -> esq = v -> dir;
        v -> dir = p;
        if (v -> bal == -1) p -> bal = 1;
        else p -> bal = 0;
        if(v -> bal = 0;
        )
    }
}

//Essa função retorna quem virou a nova raiz depois da rotação a direita
PONT rotacaoRR(PONT p){
    //Define o filho e o neto do nó com problema
    PONT u, v;
    //u (filho do problema) vai receber o endereço do filho da esquerda do problema
    u = p -> dir;
    //Se o balanceamento do filho do nó com problema for -1
    if (u -> bal == -1){
        //p vai apontar para o filho no qual o seu antigo filho apontava para direita
        p -> dir = u -> esq;
        //p vira filho a direita de u
        u -> esq = p;
        p -> bal = 0;
        u -> bal = 0;
        //u toma o lugar de p
        return u;
    }
}
