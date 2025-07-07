/*
QUESTÃO 4 – Parte II – Índices Primários

Enunciado:
Escreva uma função para excluir todos os registros do curso X.
A exclusão deve ser lógica (valido = false) e deve atualizar a tabela de índices primários (use excluirIndice).
A exclusão física não é necessária.
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

// ---------- Funções auxiliares de índice ----------

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
            for (int j = i; j < (*n) - 1; j++) tabela[j] = tabela[j + 1];
            (*n)--;
            return end;
        }
    }
    return -1;
}

// ---------- Função principal de exclusão ----------

int excluirRegistrosPorCurso(const char *arquivo, INDICE tabela[], int *n, int cursoAlvo) {
    FILE* arq = fopen(arquivo, "r+b");
    if(!arq) return -1;

    REGISTRO r;
    int removidos = 0;

    for(int i = 0; i < *n; i ++){
        int end = tabela[i].endereco;
        fseek(arq, end*sizeof(REGISTRO), SEEK_SET);
        fread(&r, sizeof(REGISTRO), 1, arq);
        if(r.valido && r.curso == cursoAlvo){
            r.valido = false;
            fseek(arq, -sizeof(REGISTRO), SEEK_CUR);
            fwrite(&r, sizeof(REGISTRO), 1, arq);
            excluirIndice(tabela, n, r.NroUSP);
            removidos++;
        }
        else{
            i++;
        }
    }

    fclose(arq);
    return removidos;
}

// ---------- Função de teste ----------

void criarArquivoParaTeste(const char *arquivo, INDICE tabela[], int *n) {
    FILE *f = fopen(arquivo, "wb");
    if (!f) return;

    REGISTRO r1 = {111, 10, 11, 18, true};
    REGISTRO r2 = {222, 20, 22, 19, true};
    REGISTRO r3 = {333, 10, 33, 20, true};

    fwrite(&r1, sizeof(REGISTRO), 1, f);
    fwrite(&r2, sizeof(REGISTRO), 1, f);
    fwrite(&r3, sizeof(REGISTRO), 1, f);

    tabela[0] = (INDICE){111, 0};
    tabela[1] = (INDICE){222, 1};
    tabela[2] = (INDICE){333, 2};
    *n = 3;

    fclose(f);
}

int main() {
    const char *arquivo = "dados.bin";
    INDICE tabela[MAX];
    int n = 0;

    criarArquivoParaTeste(arquivo, tabela, &n);

    int curso = 10;
    printf("🧹 Excluindo registros do curso %d...\n", curso);
    int excluidos = excluirRegistrosPorCurso(arquivo, tabela, &n, curso);

    if (excluidos >= 0)
        printf("✅ %d registro(s) excluído(s) logicamente.\n", excluidos);
    else
        printf("❌ Erro ao excluir registros.\n");

    return 0;
}