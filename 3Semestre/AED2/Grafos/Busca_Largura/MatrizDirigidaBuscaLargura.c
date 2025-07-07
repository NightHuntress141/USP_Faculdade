/* Problema 2: Encontrar as N cidades mais próximas do tipo "tipo" */

void largura(int m[V][V], int tipo[V], int i, int x, int N){
    int Flag[V];
    ZerarFlags(Flag);
    FILA *F;
    inicializarFila(&F);
    EntrarFila(&F, i);
    g[i].Flag = 1;

    while(F){
        i = SairFila(&F);
        Flag[i] = 2;
        if(N > 0 && tipo[i] == x){
            N--;
            printf("%d", i);
            if(N == 0){
                while(F){
                    SairFila(&F);
                }
                return;
            }
        }
        int j;
        for(j = 1; j <= V; j++){
            if(m[i][j] && Flag[j] == 0){
                Flag[j] = 1;
                Entrar(&F, j);
            }
        }
    }
}