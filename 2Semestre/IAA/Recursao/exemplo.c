#include <stdio.h>
#include <stdlib.h>

int fatorial_rec(int n){
    // se fatorial de 1 ou de 0    
    if (n < 2) return 1;

    // chamada recursiva
    else return (n * fatorial_rec(n-1));
}

int busca_sequencial_rec(int num, int *v, int tam){
    // se a lista esta vazia
    if (tam == 0) return -1;

    // se o numero esta na ultima posicao
    if (num == v[tam-1]) return tam-1;

    return busca_sequencial_rec(num, v ,tam-1);
}

int fibonnaci_rec(int n){
    if (n == 0 || n == 1) return 1;

    return fibonnaci_rec(n-1) + fibonnaci_rec(n-2);
}

int main(){
    char resposta;

    do{
        printf("Deseja calcular o fatorial de um numero natural? Digite 's' para sim e 'n' para nao: ");
        scanf("%c", &resposta);
        if (resposta != 's'){
            printf("Obrigado por usar o programa!\n");
            break;
        }

        printf("Digite um numero natural: ");
        int numero;
        scanf("%d", &numero);
        getchar();
        int resultado = fatorial_rec(numero); 
        printf("Fatorial de %d: %d\n", numero, resultado); 
    }while (resposta == 's');

    int tam = 7;
    int v[] = {1, 2, 5, 6, 3, 8, 9};
    int num = 5;

    int busca = busca_sequencial_rec(num, v, tam);
    printf("Numero %d encontrado na posicao %d\n", num, busca);

    for (int i = 0; i < 6; i++ ){
        printf("Fibonnaci(%d): %d\n", i, fibonnaci_rec(i));
    }

    return 0;
}