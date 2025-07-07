#include <stdio.h>
#include <stdbool.h>

#define MAX 50

typedef struct{
    int chave;
}REGISTRO;

typedef struct{
    REGISTRO A[MAX];
    int top1;
    int top2;
}PILHADUPLA;

void inicializarPilha (PILHADUPLA *p){
    p -> top1 = -1;
    p -> top2 = MAX;
}

int tamanhoPilha (PILHADUPLA *p){
    return p -> top1 + 1 + MAX - p -> top2;
}

void exibirPilha (PILHADUPLA *p){
    int i;
    printf("Lista 1: \n");
    for (i = p -> top1; i >= 0; i--){
        printf("%i \n", p -> A[i].chave);
    }
    int j;
    printf("Lista 2: \n");
    for (j = p -> top2; j < MAX; j++){
        printf("%i \n", p -> A[j].chave);
    }
}

int inserirPilha (PILHADUPLA *p, REGISTRO *reg, int pilha){
    if (pilha < 1 || pilha > 2){
        return false;
    }
    else if ( p -> top1 + 1 == p -> top2){
        return false;
    }
    else if (pilha == 1){
        p -> top1++;
        p -> A[p -> top1] = *reg;
    }
    else{
        p -> top2--;
        p -> A[p -> top2] = *reg;
    }
    return true;
}

int excluirPilha (PILHADUPLA *p, int pilha){
    if (pilha < 1 || pilha > 2){
        return false;
    }
    else if (pilha == 1){
        if(p -> top1 == -1){
            return false;
        }
        else{
            p -> top1--;
        }
    }
    else{
        if (p -> top2 == MAX){
            return false;
        }
        else{
            p -> top2++;
        }
    }
    return true;
}

void reinicializarPilha (PILHADUPLA *p){
    inicializarPilha(p);
}

int main (){
    PILHADUPLA pilha1;

    inicializarPilha(&pilha1);

    int tamanho = tamanhoPilha(&pilha1);
    printf("Tamanho total das pilhas: %i \n", tamanho);

    exibirPilha(&pilha1);

    for (int i = 0; i < 5; i++){
        REGISTRO reg;
        int pilha_escolhida;
        printf("Insira a pilha que se deseja adicionar um elemento no topo: ");
        scanf("%i", &pilha_escolhida);
        printf("Insira o elemento que se deseja adicionar ao topo da Pilha: ");
        scanf("%i", &reg.chave);
        int resultado = inserirPilha(&pilha1, &reg, pilha_escolhida);
        do{
            if (resultado == false){
                printf("A Pilha está cheia ou o valor inserido não foi válido, não foi possível inserir! \n");
            }
            else{
                printf("Inserção bem sucedida! \n");
            }
        }while(false);
    }

    exibirPilha(&pilha1);

    int pilha_escolhida;
    printf("Insira a pilha que se deseja excluir o elemento do topo: ");
    scanf("%i", &pilha_escolhida);
    int resultado = excluirPilha(&pilha1, pilha_escolhida);
    do{
        if (resultado == false){
            printf("A Pilha está vazia ou o valor inserido não foi válido, não foi possível excluir! \n");
        }
        else{
            printf("Ixclusão bem sucedida! \n");
        }
    }while(false);
    
    reinicializarPilha(&pilha1);

    return 0;
}