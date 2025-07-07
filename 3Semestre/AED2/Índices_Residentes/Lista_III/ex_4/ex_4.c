/*
QUESTÃO 4 – Parte III – Índices Secundários

Enunciado:
Escreva uma função para excluir todos os registros do curso X.
Para cada registro:
- Marque como inválido (`valido = false`)
- Remova a chave do índice primário
- A atualização dos índices secundários é opcional
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 1000

// ---------- Estruturas ----------

typedef struct {
    int NroUSP;
    int curso;
    int estado;
    int idade;
    bool valido;
} REGISTRO;

typedef struct {
    int nroUSP;
    int endereco;
} INDICE;

typedef struct no {
    int nroUSP;
    struct no *prox;
} NO;

// ---------- Índices em memória ----------

INDICE tabelaPrimario[MAX];
int nPrim = 0;

NO *indiceCurso[100];

// ---------- Funções auxiliares ----------

int buscarEndereco(INDICE tabela[], int n, int nroUSP) {
    int esq = 0, dir = n - 1;
    while (esq <= dir) {
        int meio = (esq + dir) / 2;
        if (tabela[meio].nroUSP == nroUSP) return tabela[meio].endereco;
        if (tabela[meio].nroUSP < nroUSP) esq = meio + 1;
        else dir = meio - 1;
    }
    return -1;
}

int excluirIndice(INDICE tabela[], int *n, int nroUSP) {
    for (int i = 0; i < *n; i++) {
        if (tabela[i].nroUSP == nroUSP) {
            int end = tabela[i].endereco;
            for (int j = i; j < *n - 1; j++) {
                tabela[j] = tabela[j + 1];
            }
            (*n)--;
            return end;
        }
    }
    return -1;
}

NO *chavesCurso(int curso) {
    return indiceCurso[curso];
}

// ---------- Função principal ----------

int excluirRegistrosDoCurso(const char *arquivo, int cursoAlvo) {
    FILE* arq = fopen(arquivo, "r+b");
    if(!arq){
        printf("Não foi possível abrir o arquivo");
        return -1;
    }

    NO* lista = chavesCurso(cursoAlvo);
    if(!lista) return 0;

    REGISTRO r;
    int excluidos = 0;

    while(lista){
        int end = buscarEndereco(tabelaPrimario, nPrim, lista -> nroUSP);
        if(end != -1){
            fseek(arq, end*sizeof(REGISTRO), SEEK_SET);
            fread(&r, sizeof(REGISTRO), 1, arq);
            if(r.valido = true){
                r.valido = false;
                fseek(arq, -sizeof(REGISTRO), SEEK_CUR);
                fwrite(&r, sizeof(REGISTRO), 1, arq);
                excluirIndice(tabelaPrimario, &nPrim, r.NroUSP);
                excluidos++;
            }
        }
        lista = lista -> prox;
    }
    fclose(arq);
    return excluidos;
}

// ---------- Teste ----------

NO *inserir(NO *lista, int nroUSP) {
    NO *novo = malloc(sizeof(NO));
    novo->nroUSP = nroUSP;
    novo->prox = lista;
    return novo;
}

void imprimirLista(NO *lista) {
    while (lista) {
        printf("%d ", lista->nroUSP);
        lista = lista->prox;
    }
    printf("\n");
}

int main() {
    const char *arquivo = "registros.bin";

    // Índice primário
    tabelaPrimario[0] = (INDICE){111, 0};
    tabelaPrimario[1] = (INDICE){222, 1};
    tabelaPrimario[2] = (INDICE){333, 2};
    nPrim = 3;

    // Índice secundário por curso
    indiceCurso[10] = inserir(indiceCurso[10], 222);
    indiceCurso[10] = inserir(indiceCurso[10], 111);
    indiceCurso[20] = inserir(indiceCurso[20], 333);

    // Criação do arquivo de registros
    FILE *f = fopen(arquivo, "wb");
    if (f) {
        REGISTRO a = {111, 10, 5, 20, true};
        REGISTRO b = {222, 10, 5, 21, true};
        REGISTRO c = {333, 20, 7, 22, true};
        fwrite(&a, sizeof(REGISTRO), 1, f);
        fwrite(&b, sizeof(REGISTRO), 1, f);
        fwrite(&c, sizeof(REGISTRO), 1, f);
        fclose(f);
    }

    // Exclusão dos registros do curso 10
    printf("🧹 Excluindo registros do curso 10...\n");
    int total = excluirRegistrosDoCurso(arquivo, 10);
    printf("✅ %d registro(s) excluído(s).\n", total);

    return 0;
}