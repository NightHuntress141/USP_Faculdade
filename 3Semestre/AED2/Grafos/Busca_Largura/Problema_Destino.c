// Exibir vértices de onde é possível alcançar um dado destino -> Tanto faz o tipo de busca

void buscaLargura(int m[V][V]; int i; int destino, int Flag[]){
    FILA F;
    inicializar(&F);
    Entrar(&F, i);
    Flag[i] = 1;
    int aux[V];
    ZerarFlag(aux);
    aux[i] = 1;    
    while(F){
        i = SairFila(&F);
        Flag[i] = 2;
        int j;
        for(j = 1; j <= V; j++){
            if(m[i][j] == 1 && aux[j] == 0){
                aux[j] = 1;
                EntrarFila(&F, j);
            }
        }
        if(aux[destino] == 0) return;
        for(j = 1; j <= V; j++){
            if(aux[j] == 2){
                Flag[j] = 2;
            }
        }
    }
}

int main(){
    zerarFlags(Flag[]);
    int i;
    for(i = 1; i <= V; i++){
        if (i == destino || Flag[i] > 0) continue; // Se não for um OU outro, então ele quebra para o próximo número no laço
        buscaLargura(m[V][V], i, destino, Flag[]);
    }
    for(i = 1; i <= V; i++){
        if(Flag[i] > 0) printf("%d", i);
    }
}