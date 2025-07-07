/*
QUESTÃO 2 – Parte III – Índices Secundários

Enunciado:
Escreva uma função para exibir todos os registros do curso X.
Use o índice secundário `chavesCurso(X)` para obter uma lista ligada de NroUSP.
Para cada NroUSP, use o índice primário para localizar e exibir o registro, se for válido.
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

NO *chavesCurso(int curso) {
    return indiceCurso[curso];
}

// ---------- Função principal ----------

void exibirRegistrosDoCurso(const char *arquivo, int cursoAlvo) {
    // Abrindo um Arquivo
    FILE* arq = fopen(arquivo, "rb");
    if(!arq){
        printf("Não foi possível abrir o arquivo");
        return;
    }

    NO* lista = chavesCurso(cursoAlvo);
    if (!lista) {
        printf("Nenhum registro encontrado para o curso %d.\n", cursoAlvo);
        return;
    }

    REGISTRO r;
    while(lista){
        int end = buscarEndereco(tabelaPrimario, nPrim, lista -> nroUSP);
        if(end != -1){
            fseek(arq, end*sizeof(REGISTRO), SEEK_SET);
            fread(&r, sizeof(REGISTRO), 1, arq);
            if(r.valido){
                printf("USP: %d | Curso: %d | Estado: %d | Idade: %d\n", r.NroUSP, r.curso, r.estado, r.idade);
            }
        }
        lista = lista -> prox;
    }

    fclose(arq);
}

// ---------- Teste ----------

NO *inserir(NO *lista, int nroUSP) {
    NO *novo = malloc(sizeof(NO));
    novo->nroUSP = nroUSP;
    novo->prox = lista;
    return novo;
}

int main() {
    const char *arquivo = "registros.bin";

    // Índice primário
    tabelaPrimario[0] = (INDICE){111, 0};
    tabelaPrimario[1] = (INDICE){222, 1};
    nPrim = 2;

    // Índice secundário por curso
    indiceCurso[10] = inserir(indiceCurso[10], 222);
    indiceCurso[10] = inserir(indiceCurso[10], 111);

    // Criação do arquivo de registros
    FILE *f = fopen(arquivo, "wb");
    if (f) {
        REGISTRO a = {111, 10, 5, 20, true};
        REGISTRO b = {222, 10, 5, 21, true};
        fwrite(&a, sizeof(REGISTRO), 1, f);
        fwrite(&b, sizeof(REGISTRO), 1, f);
        fclose(f);
    }

    // Execução
    printf("📚 Alunos do curso 10:\n");
    exibirRegistrosDoCurso(arquivo, 10);

    return 0;
}