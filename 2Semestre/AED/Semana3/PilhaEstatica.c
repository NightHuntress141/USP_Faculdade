#include <stdio.h>
#define MAX 50
#define true 1
#define false 0

typedef struct{
    int chave;
}REGISTRO;

typedef struct{
    REGISTRO A[MAX];
    int top;
}PILHA;

void inicializarPilha (PILHA *p){
    p -> top = -1;
}

int tamanhoPilha (PILHA *p){
    return p -> top + 1;
}

void exibirPilha (PILHA *p){
    int i;
    for (i = p -> top; i >= 0; i--){
        printf("%i \n", p -> A[i].chave);
    }
}

int inserirPilha (PILHA *p, REGISTRO *reg){
    if (p -> top >= MAX - 1){
        return false;
    }
    else{
        p -> top++;
        p -> A[p -> top] = *reg;
        return true;
    }
}

int excluirPilha (PILHA *p){
    if (p -> top == -1){
        return false;
    }
    else{
        p -> top--;
        return true;
    }
}

void reinicializarPilha (PILHA *p){
    p -> top = -1;
}

int main (){

    PILHA pilha1;

    inicializarPilha(&pilha1);

    int tamanho = tamanhoPilha(&pilha1);
    printf("Tamanho da Pilha: %i \n", tamanho);

    exibirPilha(&pilha1);

    for (int i = 0; i < 3; i++){
        REGISTRO reg1;
        printf("Insira o elemento que se deseja adicionar ao topo da Pilha: ");
        scanf("%i", &reg1.chave);
        int resultado = inserirPilha(&pilha1, &reg1);
        do{
            if (resultado == false){
                printf("A Pilha está cheia, não foi possível inserir! \n");
            }
            else{
                printf("Inserção bem sucedida! \n");
            }
        }while(false);
    }

    exibirPilha(&pilha1);

    int resultado1 = excluirPilha(&pilha1);
    do{
        if (resultado1 == false){
            printf("A Pilha está vazia, não foi possível excluir! \n");
        }
        else{
            printf("Ixclusão bem sucedida! \n");
        }
    }while(false);

    exibirPilha(&pilha1);

    reinicializarPilha(&pilha1);

    return 0;
}