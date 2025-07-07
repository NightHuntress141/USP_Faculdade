#include <stdio.h>
#include <malloc.h>
#include <stdbool.h>

//"esquedo" e "direito" são constantes do tipo LADO
typedef enum{esquerdo, direito} LADO;

typedef struct aux{
    int chave;
    struct aux* esq;
    struct aux* dir;
}NO, *PONT;

//Busca recursiva: Primeiro verifica na esquerda e depois na direita
PONT buscarChave(PONT raiz, int chave_buscada){
    //Condição de parada
    if (raiz == NULL) return NULL;
    //Se a raiz contém a chave, retornar raiz
    if (raiz -> chave == chave_buscada) return raiz;
    //Busca no filho a esquerda da raiz antiga
    PONT aux = buscarChave(raiz, raiz -> esq);
    //Se a raiz não é NULL e nem sua chave é igual a buscada, então a resposta está obrigatoriamente na direita
    if (aux != NULL) return aux;
    return buscarChave(raiz -> dir, chave_buscada);
}

PONT criarNo(int chave_nova){
    PONT novoNo = (PONT) malloc(sizeof(NO));
    novoNo -> chave = chave_nova;
    novoNo -> esq = NULL;
    novoNo -> dir = NULL;
    return novoNo;
}

PONT inicializar(PONT* raiz, int chave_raiz){
    *raiz = criarNo(chave_raiz);
}

bool inserirFilho(PONT raiz, int chave_filho, int chave_pai, LADO lado_pedido){
    //Buscamos a localização do pai
    PONT pai = buscar(raiz, chave_pai);
    //Verificamos se o pai existe ou não
    if(pai == NULL) return false;
    //Se o pai existir, criamos o novo nó
    PONT novo_no = criarNo(chave_filho);
    //Verificamos qual lado adicionar e modificar os ponteiros
    if(lado_pedido == esquerdo){
        //Caso já houvesse outro filho na esquerda, então o novo nó substitui seu lugar e o anterior vira seu filho
        novo_no -> esq = pai -> esq;
        pai -> esq = novo_no;
    }
    else{
        //Caso já houvesse outro filho na direita, então o novo nó substitui seu lugar e o anterior vira seu filho
        novo_no -> esq = pai -> esq;
        pai -> dir = novo_no;
    }
    return true;

}

int main(){
    int chave_raiz = 10;
    PONT raiz;
    criarRaiz(&raiz, chave_raiz);
    inserirFilho(raiz, 2, 10, esquerdo);   
}