#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int A[3];
} ARRANJO;

void mudar1(int a[3]){
	a[0] = 4;
	a[1] = 5;
	a[2] = 6;
}

void mudar2(ARRANJO b){
	b.A[0] = 4;
	b.A[1] = 5;
	b.A[2] = 6;
}

int main(){
	int x[3];
	x[0] = 1;
	x[1] = 2;
	x[2] = 7;
	
	printf("&x: %p, x: %p, *x: %i\n", &x, x, *x);
	printf("x0: %i, x1: %i, x2: %i\n", x[0], x[1], x[2]);

	mudar1(x);
	printf("x0: %i, x1: %i, x2: %i\n", x[0], x[1], x[2]);
	
	ARRANJO w;

	w.A[0] = 21;
	w.A[1] = 22;
	w.A[2] = 23;
	printf("w0: %i, w1: %i, w2: %i\n", w.A[0], w.A[1], w.A[2]);

	mudar2(w);
	printf("w0: %i, w1: %i, w2: %i\n", w.A[0], w.A[1], w.A[2]);

	/* nao pode fazer isso: tipos incompativeis:     w.A = x; */
	
	return 0;
}

/*
&x: 0x7ffe49d209e0, x: 0x7ffe49d209e0, *x: 1
x0: 1, x1: 2, x2: 7
x0: 4, x1: 5, x2: 6
w0: 21, w1: 22, w2: 23
w0: 21, w1: 22, w2: 23
*/