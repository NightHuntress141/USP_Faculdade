/*
QUESTÃO 3 – Parte II – Índices Primários

Enunciado:
Escreva uma função que, dado um número USP X, retorne o registro correspondente (use o índice primário).
A função deve:
1. Consultar a tabela de índices primários em memória
2. Se encontrar, usar fseek() para acessar diretamente o registro no arquivo
3. Retornar o registro, se válido
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
    int endereco; // posição lógica do registro no arquivo (0, 1, 2, ...)
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

// ---------- Função de busca usando índice ----------

bool buscarRegistroPorIndice(const char *arquivo, INDICE tabela[], int n, int nroUSP, REGISTRO *saida) {
    int end = buscarEndereco(tabela, n, nroUSP);
    if(end == -1) return false;

    FILE* arq = fopen(arquivo, "rb");
    if(!arq) return false;

    fseek(arq, end*sizeof(REGISTRO), SEEK_SET);
    int lidos = fread(saida, sizeof(REGISTRO), 1, arq);
    fclose(arq);

    return(lidos == 1 && saida -> valido);
}

// ---------- Função de teste ----------

void criarArquivoComIndice(const char *arquivo, INDICE tabela[], int *n) {
    FILE *f = fopen(arquivo, "wb");
    if (!f) return;

    REGISTRO r1 = {111, 1, 11, 18, true};
    REGISTRO r2 = {222, 2, 22, 19, true};
    REGISTRO r3 = {333, 3, 33, 20, true};

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

    criarArquivoComIndice(arquivo, tabela, &n);

    REGISTRO r;
    int nro = 222;

    printf("🔍 Buscando aluno com NroUSP %d...\n", nro);
    if (buscarRegistroPorIndice(arquivo, tabela, n, nro, &r)) {
        printf("✅ Registro encontrado:\n");
        printf("NroUSP: %d | Curso: %d | Estado: %d | Idade: %d\n",
               r.NroUSP, r.curso, r.estado, r.idade);
    } else {
        printf("❌ Registro não encontrado ou inválido.\n");
    }

    return 0;
}