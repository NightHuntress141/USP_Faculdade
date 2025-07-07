/*
 - Definição Árvore Binária: Aquela cujo os nós apontam no máximo 2 endereços para esquerda ou direita;

 - Definição Árvore Binária de Busca: Aquela cujo os nós apontam para esquerda valores menores do que o seu
   e para direita valores maiores do que o seu;

 - Funções a serem estudadas:
    - Inicialização de uma árvore;
    - Inserção de um elemento;
    - Busca de um elemento;
    - Contagem no número de elementos;
    - Leitura de uma árvore;
    - Remoção de um elemento
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

//Estrutura principal do Nó da árvore
typedef struct aux{
    int chave;       //Guarda o valor do nó
    struct aux* esq; //Guarda o endereço do descendente a esquerda
    struct aux* dir; //Guarda o endereço do descendente a direita
}NO;

//Ponteiro especifico para estruturas do tipo Nó
typedef NO* PONT; 

void exibir_arvore_rec(PONT raiz, int nivel);

PONT inicializar(){
    //Basta colocar o endereço da raiz como NULL
    return NULL;
}

PONT criar_no(int nova_chave){
    //Aloca espaço para uma nova estrutura do tipo NO
    PONT novo_no = (PONT) malloc(sizeof(NO));

    //Define os valores das áreas dessa estrutura
    novo_no -> chave = nova_chave;
    novo_no -> dir = NULL;
    novo_no -> esq = NULL;
    
    return novo_no;
}

PONT inserir_no(PONT raiz, PONT novo_no){
    //Se a raiz está vazia, então o nó inserido volta como valor da raiz, sendo adicionado na árvore
    if (raiz == NULL) return novo_no;

    //Percorrendo a árvore de maneira recursiva:

    //Se o nó inserido for menor que a raiz, é deslocado para esquerda
    if (novo_no -> chave < raiz -> chave){
        raiz -> esq = inserir_no(raiz -> esq, novo_no);
    }
    //Se o nó inserido for maior que a raiz, é deslocado para direita
    else{
        raiz -> dir = inserir_no(raiz -> dir, novo_no);
    }

    //Retorna a raiz e o novo nó criado NÃO é adicionado na árvore
    return raiz;
}

PONT busca_no(PONT raiz, int chave){
    //Busca Binária
    if (raiz == NULL) return NULL;
    if (raiz -> chave == chave) return raiz;
    if (raiz -> chave > chave) return busca_no(raiz -> esq, chave);
    else return busca_no(raiz -> dir, chave);
}

int contagem_arvore(PONT raiz){
    if(raiz == NULL) return 0;
    return (contagem_arvore(raiz -> esq) + 1 + contagem_arvore(raiz -> dir));
}

void exibir_arvore(PONT raiz) {
    exibir_arvore_rec(raiz, 0);
}

void exibir_arvore_rec(PONT raiz, int nivel) {
    if (raiz == NULL) {
        return;
    }

    // Primeiro exibe os nós à direita, recursivamente
    exibir_arvore_rec(raiz->dir, nivel + 1);

    // Imprime espaços para representar o nível
    for (int i = 0; i < nivel; i++) {
        printf("    ");
    }

    // Imprime o valor do nó atual
    printf("%d\n", raiz->chave);

    // Por fim, exibe os nós à esquerda, recursivamente
    exibir_arvore_rec(raiz->esq, nivel + 1);
}

//Função para função de exclusão que retorna a localização da estrutura a ser excluida e seu pai
PONT pesquisa_no(PONT raiz, int chave_excluir, PONT *pai){

    //Define os parametros iniciais de procura
    PONT atual = raiz;
    *pai = NULL;

    //Procura até chegar no fim, ou seja, depois de chegar em uma folha e ainda não ter achado
    while (atual != NULL){
        //Achamos o endereço/posição do nó a ser excluido
        if (atual -> chave == chave_excluir) return atual;
        //Não achamos, então continuamos a busca
        *pai = atual;
        if(chave_excluir < atual -> chave) atual = atual -> esq;
        else atual = atual -> dir;
    }
    return NULL;
}

PONT remove_no(PONT raiz, int chave_excluir) {
    if (raiz == NULL) {
        printf("Elemento %d nao encontrado.\n", chave_excluir);
        return NULL;
    }

    // Procura o nó a ser removido
    if (chave_excluir < raiz->chave) {
        raiz->esq = remove_no(raiz->esq, chave_excluir);
    } else if (chave_excluir > raiz->chave) {
        raiz->dir = remove_no(raiz->dir, chave_excluir);
    } else { // Encontramos o nó a ser removido
        // Caso 1: Nó folha ou com apenas um filho
        if (raiz->esq == NULL) {
            PONT temp = raiz->dir;
            free(raiz);
            return temp;
        } else if (raiz->dir == NULL) {
            PONT temp = raiz->esq;
            free(raiz);
            return temp;
        }

        // Caso 2: Nó com dois filhos
        // Encontra o menor nó da subárvore direita
        PONT sucessor = raiz->dir;
        while (sucessor->esq != NULL) {
            sucessor = sucessor->esq;
        }

        // Copia o valor do sucessor para o nó atual
        raiz->chave = sucessor->chave;

        // Remove o sucessor da subárvore direita
        raiz->dir = remove_no(raiz->dir, sucessor->chave);
    }

    return raiz;
}

int profundidade(PONT raiz) {
	if (raiz == NULL) return 0;
	int pesq = profundidade(raiz->esq);
	int pdir = profundidade(raiz->dir);
	
	if (pesq > pdir) return 1 + pesq;
	else	return 1 + pdir; 
}

void exibirPreOrdem(PONT raiz){
    if (raiz == NULL) return;
    printf("%i ", raiz -> chave);
    exibirPreOrdem (raiz -> esq);
    exibirPreOrdem (raiz -> dir);
}

//Ordem crescente para o caso da Arvore binaria de pesquisa
void exibirEmordem(PONT raiz){
    if (raiz == NULL) return;
    exibirEmordem (raiz -> esq);
    printf("%i ", raiz -> chave);
    exibirEmordem (raiz -> dir);
}

void exibirPosOrdem(PONT raiz){
    if (raiz == NULL) return;
    exibirPosOrdem (raiz -> esq);
    exibirPosOrdem (raiz -> dir);
    printf("%i ", raiz -> chave);
}

void liberar_arvore(PONT raiz) {
    if (raiz == NULL) return;
    liberar_arvore(raiz->esq);
    liberar_arvore(raiz->dir);
    free(raiz);
}

int main(){

    //Inicialização da Raiz
    PONT raiz = inicializar();

    //Inserção de um elemento: Primeiro criar o nó, depois incluir na árvore
    /*OBS: Devemos manter os olhos sempre no valor da raiz, 
    ela dá a chave para todo o restante do elementos contidos na árvore*/
    int elementos[] = {4, 2, 6, 1, 3, 5, 7};
    for (int i = 0; i < 7; i++) {
        PONT no = criar_no(elementos[i]);
        raiz = inserir_no(raiz, no);
    }

    //Busca de um elemento na árvore: Busca Binária
    int elemento_procurado;
    printf("Insira o valor do elemento que se deseja procurar: ");
    scanf("%d", &elemento_procurado);
    printf("\n");
    PONT resultado = busca_no(raiz, elemento_procurado);
    if (resultado != NULL) {
        printf("Elemento: %d, esquerda: %d, direita: %d \n\n", resultado->chave, 
            resultado->esq ? resultado->esq->chave : -1, 
            resultado->dir ? resultado->dir->chave : -1);
    } else {
        printf("Elemento nao encontrado na arvore.\n\n");
    }

    //Contagem dos elementos em uma árvore binária: ordem crescente 
    //(subarvore esquerda -> raiz -> subarvore direita)
    int numero_elementos;
    numero_elementos = contagem_arvore(raiz);
    printf("Numero elementos: %d \n\n", numero_elementos);

    //Leitura da Árvore
    exibir_arvore(raiz);
    printf("\n\n\n");

    //Exclusão de elementos
    raiz = remove_no(raiz, 2);
    exibir_arvore(raiz);


    liberar_arvore(raiz);

    return 0;
}