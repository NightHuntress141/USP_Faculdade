// Questão 1
int spammer(vertice* g) {
    bool mandou_x[V+1];
    bool recebeu_x[V+1];
    for(int k = 0; k <= V; k++){
        mandou_x[i] = false;
        recebeu_x[i] = false;
    }
    for (int i = 1; i <= V; i++) {
        NO* p = g[i].inicio;
        while (p) {
            if (p->id == 'x'){
            mandou_x[i] = true;
            recebeu_x[p->adj] = true;
            }
            p = p->prox;
        }
    }
    for (int j = 1; j <= V; j++) {
        if (mandou_x[j] && !(recebeu_x[j])) return j;
    }
    return -1;
}

// Questão 2
void buscaLargura(vertice* g, int i){
    // Inicialização
    zerarFlags(g);
    FILA f;
    inicializarFila(&f);
    entrarFila(&f, i);
    g[i].flag = 1;
    int resp = -1;

    while(!filaVazia(&f)){ //Enquanto a fila não estiver vazia
        i = sairFila(&f);
        g[i].flag = 2; 
        NO* p = g[i].inicio;
        while(p){
            if(g[p -> adj].flag == 0){
                if(g[p -> adj].código == 2){
                    resp = p -> adj;
                    break;
                }
                entrarFila(&f, p -> adj);
                g[p -> adj].flag = 1;
            }
            p = p -> prox;
        }
    }

    printf("O local mais próximo que possui posto de gasolina é: %d \n", resp);
}

// Questão 3
bool subgrafo(vertice* g, int m[V + 1][V + 1]){
    for (int i = 1; i <= V; i++) {
        NO* p = g[i].inicio;
        while(p){
            if(m[i][p -> adj] == 0) return false;
            p = p -> prox;
        }
    }
    return true;
}