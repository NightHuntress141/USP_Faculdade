/*
QUESTÃO 5 – Parte III – Índices Secundários

Enunciado:
Escreva uma função para alterar a idade atual de um registro de nroUSP X para a idade Y.
Use o índice primário para localizar o registro e atualize o campo idade.
Verifique se o registro é válido antes de alterar.
A alteração do índice secundário não é necessária.
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

// ---------- Índices em memória ----------

INDICE tabelaPrimario[MAX];
int nPrim = 0;

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

// ---------- Função principal ----------

bool alterarIdade(const char *arquivo, int nroUSP, int novaIdade) {
    int end = buscarEndereco(tabelaPrimario, nPrim, nroUSP);
    if(end == -1) return false;

    FILE* arq = fopen(arquivo, "r+b");
    if(!arq) return false;

    REGISTRO r;
    fseek(arq, sizeof(REGISTRO)*end, SEEK_SET);
    fread(&r, sizeof(REGISTRO), 1, arq);

    if(!r.valido){
        r.idade = novaIdade;
        fseek(arq, -sizeof(REGISTRO), SEEK_CUR);
        fwrite(&r, sizeof(REGISTRO), 1, arq);
        
        fclose(arq);
        return true;
    }

    fclose(arq);
}

// ---------- Teste ----------

int main() {
    const char *arquivo = "registros.bin";

    // Índice primário
    tabelaPrimario[0] = (INDICE){111, 0};
    nPrim = 1;

    // Criação do arquivo de registros
    FILE *f = fopen(arquivo, "wb");
    if (f) {
        REGISTRO a = {111, 10, 5, 20, true};
        fwrite(&a, sizeof(REGISTRO), 1, f);
        fclose(f);
    }

    // Alteração de idade
    printf("🔁 Alterando idade do aluno 111 para 99...\n");
    if (alterarIdade(arquivo, 111, 99))
        printf("✅ Idade atualizada com sucesso.\n");
    else
        printf("❌ Falha na alteração.\n");

    return 0;
}