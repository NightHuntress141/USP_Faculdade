/*
QUESTÃO 1 – Parte II – Índices Primários (versão com funções auxiliares)

Enunciado:
Implemente o procedimento de ordenação KeySort, que:
1. Cria uma tabela de índices primários em memória usando inserirIndice()
2. Ordena os registros por chave
3. Reescreve o arquivo ordenado em um novo arquivo binário
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

// ---------- Funções auxiliares ----------

bool inserirIndice(INDICE tabela[], int *n, int nroUSP, int endereco) {
    int i = 0;
    while (i < *n && tabela[i].nroUSP < nroUSP) i++;
    if (i < *n && tabela[i].nroUSP == nroUSP) return false;
    for (int j = *n; j > i; j--) tabela[j] = tabela[j - 1];
    tabela[i].nroUSP = nroUSP;
    tabela[i].endereco = endereco;
    (*n)++;
    return true;
}

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
            for (int j = i; j < *n - 1; j++) tabela[j] = tabela[j + 1];
            (*n)--;
            return end;
        }
    }
    return -1;
}

// ---------- Função KeySort ----------

void keySort(const char *entrada, const char *saida) {
    FILE *fin = fopen(entrada, "rb");
    FILE *fout = fopen(saida, "wb");

    if (!fin || !fout) {
        printf("Erro ao abrir arquivos.\n");
        return;
    }

    INDICE tabela[MAX];
    REGISTRO registros[MAX];
    int n = 0;
    REGISTRO r;

    int pos = 0;
    while (fread(&r, sizeof(REGISTRO), 1, fin) == 1) {
        if (r.valido) {
            registros[pos] = r;
            inserirIndice(tabela, &n, r.NroUSP, pos);
            pos++;
        }
    }

    for (int i = 0; i < n; i++) {
        int end = tabela[i].endereco;
        fwrite(&registros[end], sizeof(REGISTRO), 1, fout);
    }

    fclose(fin);
    fclose(fout);
}

// ---------- Função de teste ----------

void criarArquivoTeste(const char *nome) {
    FILE *f = fopen(nome, "wb");
    if (!f) return;

    REGISTRO r1 = {333, 1, 11, 20, true};
    REGISTRO r2 = {111, 2, 22, 21, true};
    REGISTRO r3 = {222, 3, 33, 22, true};

    fwrite(&r1, sizeof(REGISTRO), 1, f);
    fwrite(&r2, sizeof(REGISTRO), 1, f);
    fwrite(&r3, sizeof(REGISTRO), 1, f);

    fclose(f);
}

int main() {
    const char *in = "entrada.bin";
    const char *out = "ordenado.bin";

    criarArquivoTeste(in);
    keySort(in, out);

    printf("✅ Arquivo ordenado criado: '%s'\n", out);
    return 0;
}