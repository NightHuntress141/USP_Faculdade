/*
QUESTÃO 2 – Parte II – Índices Primários

Enunciado:
Escreva uma função para inserir um novo registro r no arquivo,
tomando cuidado para evitar chaves duplicadas (use o índice primário).
A inserção deve ser física no final do arquivo, e a chave deve ser adicionada à tabela de índice.
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

// ---------- Função principal de inserção ----------

bool inserirComIndice(const char *arquivo, INDICE tabela[], int *n, REGISTRO novo) {
    if (buscarEndereco(tabela, *n, novo.NroUSP) != -1) {
        return false;  // chave duplicada
    }

    FILE *f = fopen(arquivo, "ab");
    if (!f) return false;

    fseek(f, 0, SEEK_END);
    long pos = ftell(f) / sizeof(REGISTRO);  // endereço lógico (posição do novo registro)

    novo.valido = true;
    fwrite(&novo, sizeof(REGISTRO), 1, f);
    fclose(f);

    inserirIndice(tabela, n, novo.NroUSP, (int)pos);
    return true;
}

// ---------- Função de teste ----------

void criarArquivoInicial(const char *arquivo, INDICE tabela[], int *n) {
    FILE *f = fopen(arquivo, "wb");
    if (!f) return;

    REGISTRO r1 = {101, 10, 35, 20, true};
    REGISTRO r2 = {202, 20, 25, 22, true};

    fwrite(&r1, sizeof(REGISTRO), 1, f);
    fwrite(&r2, sizeof(REGISTRO), 1, f);

    inserirIndice(tabela, n, r1.NroUSP, 0);
    inserirIndice(tabela, n, r2.NroUSP, 1);

    fclose(f);
}

int main() {
    const char *arquivo = "registros.bin";
    INDICE tabela[MAX];
    int n = 0;

    criarArquivoInicial(arquivo, tabela, &n);

    REGISTRO novo1 = {303, 30, 33, 23, true}; // deve ser inserido
    REGISTRO novo2 = {101, 99, 99, 99, true}; // chave duplicada

    printf("Tentando inserir NroUSP %d...\n", novo1.NroUSP);
    if (inserirComIndice(arquivo, tabela, &n, novo1))
        printf("✅ Inserção realizada.\n");
    else
        printf("❌ Chave duplicada. Inserção negada.\n");

    printf("Tentando inserir NroUSP %d...\n", novo2.NroUSP);
    if (inserirComIndice(arquivo, tabela, &n, novo2))
        printf("✅ Inserção realizada.\n");
    else
        printf("❌ Chave duplicada. Inserção negada.\n");

    return 0;
}