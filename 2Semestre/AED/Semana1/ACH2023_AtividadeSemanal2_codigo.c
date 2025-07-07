#include <stdlib.h>
#include <stdio.h>
#define MAX 5

typedef struct aux {
  
  /* COMPLETAR */

} PESSOA;

PESSOA* inicializar(int id){
  PESSOA A[MAX];
  int nroElem;
  /* COMPLETAR */

}

void registrar(PESSOA* filho, PESSOA* mae, PESSOA* pai){

  /* COMPLETAR */
  
}

int main(){
  PESSOA* m = inicializar(1);   
  PESSOA* p = inicializar(2);
  PESSOA* f = inicializar(3);

  registrar(f, m, p);
  
  printf("%p %p %p\n", f, f->mae, f->pai);    

  return 0;
}