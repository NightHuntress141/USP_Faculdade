#include <stdio.h>
#include <malloc.h>

typedef struct{
    int chave;
}REGISTRO;

typedef struct aux{
    REGISTRO reg;
    struct aux* prox;
}ELEMENTO;

typedef ELEMENTO *PONT;

typedef struct{
    PONT top;
}PILHA;