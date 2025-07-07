#include <stdio.h>

int main() {
    int nusp = 15486609;
    printf("Imprimindo inteiro: %i\n", nusp);
    printf("Imprimindo numero: %d\n", nusp);
    printf("Imprimindo float (com cast): %f\n", (float)nusp);
    printf("Imprimindo quociente: %i\n", nusp/2);
    printf("Imprimindo resto: %d\n", nusp%2);
    printf("Imprimindo quadrado: %d\n", nusp*nusp);
    return 0;
}

/*Qual a diferença entre %i e %d?
A diferença prática entre %i e %d é que %i também pode ser usado com scanf 
para interpretar diferentes bases numéricas (decimal, octal, hexadecimal), 
enquanto %d é usado apenas para números decimais.
*/

/*Imprimindo inteiro: 15486609
Imprimindo numero: 15486609
Imprimindo float (com cast): 15486609.000000     
Imprimindo quociente: 7743304
Imprimindo resto: 1
Imprimindo quadrado: -210457055*/