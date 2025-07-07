#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/*Estrutura principal das árvores que não possuem limites de filhos, logo elas são formadas
pelo valor da chave, valor do primeiro filho e do seu irmão mais próximo. Então, podemos observar
um comportamento similar a formação de listas ligadas de irmãos*/
typedef struct no{
    int chave;
    struct no* primFilho;
    struct no *proxIrmao;
} NO;

typedef NO* PONT; //Criação de um ponteiro para a estrutura do tipo NO

PONT criaNovoNo (int chave_nova){
    PONT novo = (PONT) malloc(sizeof(NO));
    novo -> primFilho = NULL;
    novo -> proxIrmao = NULL;
    novo -> chave = chave_nova;
    return novo;
}

PONT inicializa(int chave){
    //Para inicializar, temos que primeiro criar um nó na memória
    return(criaNovoNo(chave));
}

void exibirArvore(PONT raiz){ if (raiz == NULL) return; printf("%d(",raiz->chave); PONT p = raiz->primFilho; while (p) { exibirArvore(p); p = p->proxIrmao; } printf(")"); }

PONT buscaChave(PONT raiz, int chave_pai_buscada){
    //Verifica se a raiz não é nula
    if (raiz == NULL) return NULL;
    //Verifica se a chave atual é igual a chave do pai buscada
    if (raiz -> chave == chave_pai_buscada) return raiz;
    PONT p = raiz -> primFilho;
    while(p != NULL){
        //Chamada recursiva
        PONT resp = buscaChave(raiz, chave_pai_buscada);
        //Caso tenha achado a chave igual a do pai buscada
        if (resp != NULL) return resp;
        //Caso contrário vai para o próximo irmão da lista
        p = p -> proxIrmao;
    }
    return NULL;
}

bool insere(PONT raiz, int chave_nova, int chave_pai){
    //Busca a localização do pai
    PONT pai = buscaChave(raiz, chave_pai);

    //Verifica se o pai existe, caso contrário não é possível inserir
    if (pai == NULL) return false;

    //Criação do novo nó com a nova chave inserida
    PONT filho_novo = criaNovoNo(chave_nova);

    //Criação de um parametro que varre a lista de irmãos
    PONT filho_atual = pai -> primFilho;

    //Caso o nó não tenha nenhum filho, ou seja, seja uma folha
    if (filho_atual == NULL) pai -> primFilho = filho_novo;
    //Caso o nó já tenha filhos, o novo filho deve ser inserido no final da lista
    else {
        while(filho_atual -> proxIrmao != NULL){
            filho_atual = filho_atual ->proxIrmao;
        }
        filho_atual -> proxIrmao = filho_novo;
    } 

    return true;
}

int main() {
    PONT r = inicializa(8);

}