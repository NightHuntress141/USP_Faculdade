//--------------------------------------------------------------
// COLOQUE OS NOMES DOS RESPONS�VEIS AQUI: Rebecka Bocci Domingues E blablabla
//--------------------------------------------------------------

/*
-> Grafos não-dirigidos


*/



#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

// INFORME O NRO DO GRUPO CONFORME PLANILHA DIVULGADA
int grupo() {
  return 0;
}

// ######### ESCREVA O NROUSP AQUI
int nroUSP1() {
    return 0;
}

// E O SEGUNDO NROUSP AQUI, SE HOUVER
int nroUSP2() {
    return 0;
}

// elemento da lista de resposta - NAO ALTERE ESTA DEFINICAO
typedef struct estr {
      int adj; // um nro. de vertice
      struct estr *prox;
} NO;


// grafo de V vértices numeradas de 1 a V e A arestas. O vetor ij[] contém exatamente 2*A elementos, e cada par representa uma aresta i,j. 
NO* equidistantes(int V, int A, int ij[], int v1, int v2);

//------------------------------------------
// O EP consiste em implementar esta funcao
// e outras funcoes auxiliares que esta
// necessitar
//------------------------------------------
NO* equidistantes(int V, int A, int ij[], int v1, int v2){
	NO* resp = NULL;

	// seu codigo AQUI
	//...

	return resp;
}



//---------------------------------------------------------
// use main() para fazer chamadas de teste ao seu programa
//---------------------------------------------------------
int main() {


	// aqui vc pode incluir codigo de teste - mas n�o precisa entregar isso




	// o EP sera testado com uma serie de chamadas como esta
	NO* teste = null;
	teste = NO *equidistantes(int V, int A, int ij[], int *v1, int *v2);

}

// por favor nao inclua nenhum c�digo abaixo da fun��o main()
