/*
QUESTÃO 5 – Parte II – Índices Primários

Enunciado:
Escreva uma função para alterar o curso de um aluno, identificando-o pelo nroUSP.
Use a tabela de índice primário para localizar o registro.
A alteração deve:
- Atualizar o curso no arquivo (acesso direto com fseek)
- Não alterar o índice (já que a chave primária permanece a mesma)
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

// ---------- Função principal de atualização ----------

bool alterarCurso(const char *arquivo, INDICE tabela[], int n, int nroUSP, int novoCurso) {
    FILE* arq = fopen(arquivo, "r+b");
    if(!arq) return false;

    int end = buscarEndereco(tabela, n, nroUSP);
    if(end == -1) return false;

    REGISTRO r;
    fseek(arq, end*sizeof(REGISTRO), SEEK_SET);
    fread(&r, sizeof(REGISTRO), 1, arq);

    if(!r.valido) {
        fclose(arq);
        return false;
    }

    r.curso = novoCurso;

    fseek(arq, -sizeof(REGISTRO), SEEK_CUR);
    fwrite(&r, sizeof(REGISTRO), 1, arq);

    fclose(arq);
    return true;
}

// ---------- Função de teste ----------

void criarArquivoDeTeste(const char *arquivo, INDICE tabela[], int *n) {
    FILE *f = fopen(arquivo, "wb");
    if (!f) return;

    REGISTRO r1 = {111, 10, 11, 18, true};
    REGISTRO r2 = {222, 20, 22, 19, true};
    REGISTRO r3 = {333, 30, 33, 20, true};

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

    criarArquivoDeTeste(arquivo, tabela, &n);

    int usp = 222;
    int novoCurso = 99;

    printf("✏️ Atualizando curso do aluno %d para %d...\n", usp, novoCurso);
    if (alterarCurso(arquivo, tabela, n, usp, novoCurso))
        printf("✅ Curso atualizado com sucesso.\n");
    else
        printf("❌ Aluno não encontrado ou inválido.\n");

    return 0;
}