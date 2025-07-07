#include <stdio.h>
#include <stdbool.h>
#define MAX 20
#define INVALIDO -1

typedef int TIPOCHAVE;

typedef struct{
    TIPOCHAVE chave;
}REGISTRO;

typedef struct{
    REGISTRO reg;
    int prox;
}ELEMENTO;

typedef struct{
    ELEMENTO l[MAX];
    int inicio;
    int dispo;
}LISTA;

/*Esta função recebe como entrada o arranjo da lista 1
e não devolve nenhum valor*/
void inicializarLista(LISTA* lista1) {
	int i;
	for (i=0; i<MAX-1; i++)
		lista1->l[i].prox = i + 1;
		
	lista1->l[MAX-1].prox=INVALIDO;
	lista1->inicio=INVALIDO;
	lista1->dispo=0;
}

/*Esta função recebe como entrada o arranjo da lista 1
e devolve o valor referente ao tamanho da lista*/
int tamanho(LISTA* lista1) {
	int i = lista1->inicio;
	int tam = 0;
	
	while (i != INVALIDO) {
		tam++;
		i = lista1->l[i].prox;
	}
	return tam;
}

/*Esta função recebe como entrada o arranjo da lista 1
e não devolve nenhum valor*/
void exibirLista(LISTA* lista1) {
	int i = lista1->inicio;
	printf("Lista: \" ");
		while (i != INVALIDO) {
		printf("%i ", lista1->l[i].reg.chave);
		i = lista1->l[i].prox;
		}
	printf("\"\n");
}

/*Esta função recebe como entrada o arranjo da lista 1 e a chave que deseja ser buscada
e devolve o valor da posição (i) ou inválido (-1)*/
int buscaSequencialOrdenada (LISTA *lista1, int ch){
    int i = lista1 -> inicio;
    //Enquanto não chega ao final da lista E a chave do usuário for maior que os elementos do arranjo ordenado
    while (i != INVALIDO && lista1 -> l[i].reg.chave < ch){
        i = lista1 -> l[i].prox;
    }
    if (i != INVALIDO && lista1 -> l[i].reg.chave == ch){
        return 1 + i;
    }
    else{
        return INVALIDO;
    }
}

/*Esta função recebe como entrada o arrajo da lista 1
e devolve o valor da posição do elemento disponivel*/
int TrocaElementoDisponivel (LISTA *lista1){
    int resultado = lista1 -> dispo;
    //Checando se o valor disponivel é o final da lista
    if (lista1 -> dispo != INVALIDO){
        //A posição do valor disponivel vai ser igual ao valor do proximo elemento disponivel
        lista1 -> dispo = lista1 -> l[lista1 -> dispo].prox;
    }
    return resultado;
}

bool inserirElementoListaOrdenada (LISTA *lista1, REGISTRO *reg){
    //Lista lotada
    if (lista1 -> dispo == INVALIDO){
        return false;
    }
    int anterior = INVALIDO;
    int inicio = lista1 -> inicio;

    //Qual o problema do código abaixo?
    TIPOCHAVE ch = *reg;
    
    //Enquanto inicio não se torna o fim e enquanto a chave do elemento atual for menor que a chave buscada
    while ((inicio != INVALIDO) && (lista1 -> l[inicio].reg.chave < ch)){
        anterior = inicio;
        inicio = lista1 -> l[inicio].prox;
    }

    //Caso de elemento repetido
    if (inicio != INVALIDO && lista1 -> l[inicio].reg.chave == ch){
        return false;
    }

    inicio = TrocaElementoDisponivel(&lista1);
    lista1 -> l[inicio].reg = reg;

    if (anterior == INVALIDO){
        lista1 -> l[inicio].prox = lista1 -> inicio;
        lista1 -> inicio = inicio;
    }
    else{
        lista1 -> l[inicio].prox = lista1 -> l[anterior].prox;
        lista1 -> l[anterior].prox = inicio;
    }

}

bool excluirElemLista(LISTA* lista1, int * ch) {
	int anterior = INVALIDO;
	int inicio = lista1->inicio;
		while ((inicio != INVALIDO) && (lista1->l[inicio].reg.chave < ch)) {
		anterior = inicio;
		inicio = lista1->l[inicio].prox;
		}
	if (inicio==INVALIDO || lista1->l[inicio].reg.chave!=ch) return false;
	if (anterior == INVALIDO) lista1->inicio = lista1->l[inicio].prox;
	else lista1->l[anterior].prox = lista1->l[inicio].prox;
	devolverNo(&lista1, &inicio);
	return true;
}

void devolverNo(LISTA* lista1, int j) {
    lista1->l[j].prox = lista1->dispo;
    lista1->dispo = j;
}

int main (){
    LISTA lista1;

    inicializarLista(&lista1);

    int tamanho_lista = tamanho(&lista1);
    printf("O tamanho da lista é %i", tamanho_lista);

    exibirLista(&lista1);

    int chave_busca;
    printf("Insira o valor que se deseja buscar na lista: ");
    scanf("%i", &chave_busca);
    int pos = buscaSequencialOrdenada(&lista1, &chave_busca);
    do{
        if(pos == INVALIDO){
            printf("O valor não foi encontrado na lista \n");
        }
        else{
            printf("O valor se encontra na posição: %i", pos);
        }
    }while (false);

    REGISTRO novo_reg;
    printf("Insira o valor que se deseja inserir na lista: ");
    scanf("%i", &novo_reg.chave);
    inserirElementoListaOrdenada (&lista1, &novo_reg.chave);

    int excluir_reg;
    printf("Insira o valor que se deseja deletar da lista: ");
    scanf("%i", &excluir_reg);
    excluirElemLista(&lista1, &excluir_reg);






}