#include <stdio.h>
#include <stdlib.h>

/*Este codigo resolve o problema da mochila binaria, em que eh dada uma mochila de tamanho K e se quer saber quais itens de tamanhos guardados no array 'itens' de tamanho n conseguem satisfazer a capacidade da mochila completamente. Caso nao existe nenhuma combinacao, o codigo retorna a combinacao mais proxima do sucesso. */


// Estrutura da mochila, onde cada item pode existir e/ou pertencer a mochila
typedef struct{
    int existe;
    int pertence;
}MOCHILA;


// Imprime a matriz de combinacaoes da mochila
void imprime_MatrizMochila(MOCHILA **mochila, int n, int K){
    for(int i = 0; i < n; i++){
        printf("I_%d: ", i);
        for (int j = 0; j <= K; j++){
            printf("| %d / %d | ", mochila[i][j].existe, mochila[i][j].pertence);
        }
        printf("\n");
    }
    printf("\n");
}

// Aloca memoria para a matriz
void inicializa_MatrizMochila(MOCHILA ***mochila, int n, int K){
    *mochila = (MOCHILA **)malloc(n * sizeof(MOCHILA*));
    for (int i = 0; i < n; i++) {
        (*mochila)[i] = (MOCHILA *)malloc((K+1) * sizeof(MOCHILA));
    }
}


// Cria uma matriz com todas as possibilidades de preencher mochila
void MatrizMochila(MOCHILA **mochila, int *itens, int K, int n){
    mochila[0][0].existe = 0;

    for (int k = 1; k <= K; k++){
        mochila[0][k].existe = -1;
    }

    for (int i = 1; i < n; i++){

        for (int k = 0; k <= K; k++){
            mochila[i][k].existe = -1;

            if (mochila[i-1][k].existe == 0){
                mochila[i][k].existe = 0;
                mochila[i][k].pertence = -1;
            }
            else{
                if (k - itens[i] >= 0){

                    if(mochila[i-1][k-itens[i]].existe == 0){
                        mochila[i][k].existe = 0;
                        mochila[i][k].pertence = 0;
                    }
                }
            }
        }
    }
}

// Encontra os itens que satisfazem o problema
void resolve_ProblemaMochila(MOCHILA **mochila, int *resp, int n, int K, int *itens){
    int a = 0;

    while (K > 0){
        int achou = -1;
        for (int i = 0; i < n; i++){
            if (mochila[i][K].existe == 0 && mochila[i][K].pertence == 0){
                resp[a] = itens[i];
                a++;
                K = K - itens[i];
                achou = 0;
                break;
            }
        }
        if (achou == -1) K--;
    }
}

// Main
int main(){

    MOCHILA **mochila;
    int n = 5;
    int K = 9;
    int I[] = {0, 2, 3, 5, 6};

    inicializa_MatrizMochila(&mochila, n, K);

    MatrizMochila(mochila, I, K, n);

    imprime_MatrizMochila(mochila, n, K);

    int *resposta = (int *)malloc(n * sizeof(int));

    resolve_ProblemaMochila(mochila, resposta, n, K, I);

    printf("Itens na mochila: ");
    for (int i = 0; i < n && resposta[i] != 0; i++) {
        printf("%d ", resposta[i]);
    }
    printf("\n");

    return 0;
}