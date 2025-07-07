#include <stdio.h>

int main() {
    int x = 7;
    int y = 13;
    int* z = &x;
    printf("x: %i   y: %i   z: %p\n", x, y, z);
    printf("&x: %p   &y: %p   &z: %p\n", &x, &y, &z);
    *z = x + y;
    printf("Novo valor de x: %i\n", x);    
    return 0;
}
/*
x: 7   y: 13   z: endereço de memória de x
&x: endereço de memória de x   &y: endereço de memória de y   &z: endereço de memória de z (cujo contéudo é o endereço de memória de x)
Novo valor de x: 20
*/