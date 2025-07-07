#include <stdio.h>
#include <stdlib.h>

// Exercicio 1
int busca_binaria_rec(int num, int *v, int esq, int dir){
    if (dir < esq) return -1;

    int meio = (esq + dir) / 2;

    if (num < v[meio]) return busca_binaria_rec(num, v, esq, meio-1);

    else if (num > v[meio]) return busca_binaria_rec(num, v, meio+1, dir);

    else return meio;
}

// Exercicio 2
int soma_elementos_rec(int *v, int tam){
    if (tam == 0) return 0;

    else{
        return (v[tam-1] + soma_elementos_rec(v, tam-1));
    }
}

// Exercicio 3
int soma_elementos_rec_v2(int *v, int inicio, int fim){
    if (fim == 0) return 0;

    else if (inicio == fim-1) return v[inicio];

    else{
        return (v[fim-1] + soma_elementos_rec_v2(v, inicio, fim-1));
    }
}

// Exercicio 4
int acha_max(int *v, int tam){
    if (tam == 0) return -1;

    else if (tam == 1) return v[tam-1];

    int aux = acha_max(v, tam - 1);

    if (v[tam - 1] > aux) {
        return v[tam - 1];
    } else {
        return aux;
    }
}

// Exercicio 5
int soma_digitos(int n, int soma){
    if (n == 0) return soma;

    else{
        soma += n % 10;
        return soma_digitos(n/10, soma);
    }
}

// Exercicio 6
int calcula_potencia(int base, int expoente){
    if ((base == 1) || (base == 0 && expoente == 0)) return 1;
    else if (base == 0) return 0;
    else if (expoente == 0) return 1;

    else return (base * calcula_potencia(base, expoente-1));
}

// Exercicio 7
int equacao_recursiva(int x){
    if (x <= 0) return 2;
    
    else return ((2 * equacao_recursiva(x-1)) - 4);
}

int main(){

    int v[] = {5, 19, 10, 3, 17};
    int tam = 5;

    int esq = 0;
    int dir = tam-1;
    int num_busc = 10;
    int busca = busca_binaria_rec(num_busc, v, esq, dir);

    if (busca != -1){
        printf("Numero %d encontrado na posicao %d\n", num_busc, busca);
    }
    else{
        printf("Numero %d nao pertence a lista\n", num_busc);
    }

    int soma = soma_elementos_rec(v, tam);
    int soma_v2 = soma_elementos_rec_v2(v, 0, tam);
    printf("A soma dos elementos eh: %d\n", soma);
    printf("A soma dos elementos v2 eh: %d\n", soma_v2);

    int maior = acha_max(v, tam);
    printf("o maior elemento eh: %d\n", maior);

    int n = 123;
    int soma_dig = soma_digitos(n, 0);
    printf("A soma dos digitos de %d eh: %d\n", n, soma_dig);

    int base = 2;
    int expoente = 5;
    int potencia = calcula_potencia(base, expoente);
    printf("%d^%d eh: %d\n", base, expoente, potencia);
    
    for (int i = 0; i <= 4; i++) {
        printf("R(%d) = %d\n", i, equacao_recursiva(i));
    }
    return 0;
}