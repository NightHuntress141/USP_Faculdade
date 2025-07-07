/*
QUESTÃO 1 – Parte III – Índices Secundários

Enunciado:
Escreva uma função para inserir um novo registro r no arquivo,
tomando cuidado para evitar chaves duplicadas.
Verifique quais índices precisam ser atualizados.
Atualize:
- Índice primário
- Índice secundário por curso
- Índice secundário por estado
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

// Lista ligada para índice secundário (simplificada)
typedef struct no {
    int nroUSP;
    struct no *prox;
} NO;

// ---------- Índices auxiliares ----------

INDICE tabelaPrimario[MAX];
int nPrim = 0;

// Índices secundários simulados como vetores de ponteiros (simplificados para fins didáticos)
NO *indiceCurso[100];   // índice por curso
NO *indiceEstado[100];  // índice por estado

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

// ---------- Índices secundários ----------

void inserirIndiceSecundario(NO *indice[], int chave, int nroUSP) {
    NO *novo = malloc(sizeof(NO));
    novo->nroUSP = nroUSP;
    novo->prox = indice[chave];
    indice[chave] = novo;
}

NO *chavesCurso(int curso) {
    return indiceCurso[curso];
}

NO *chavesEstado(int estado) {
    return indiceEstado[estado];
}

// ---------- Função principal ----------

bool inserirComIndices(const char *arquivo, REGISTRO novo) {
    if(buscarEndereco(tabelaPrimario, nPrim, novo.NroUSP) != -1){ // Verificando se chave já existe
        return false;
    }

    FILE* arq = fopen(arquivo, "ab");
    if(!arq) return false;

    fseek(arq, 0, SEEK_END);
    long pos = ftell(arq) / sizeof(REGISTRO); // posição lógica

    novo.valido = true;
    fwrite(&novo, sizeof(REGISTRO), 1, arq);
    fclose(arq);

    inserirIndice(tabelaPrimario, &nPrim, novo.NroUSP, (int)pos);
    inserirIndiceSecundario(indiceCurso, novo.curso, novo.NroUSP);
    inserirIndiceSecundario(indiceEstado, novo.estado, novo.NroUSP);
}

// ---------- Teste ----------

void imprimirLista(NO *lista) {
    while (lista) {
        printf("%d ", lista->nroUSP);
        lista = lista->prox;
    }
    printf("\n");
}

int main() {
    const char *arquivo = "registros.bin";

    REGISTRO a = {101, 10, 5, 20, true};
    REGISTRO b = {102, 10, 5, 21, true};
    REGISTRO c = {103, 20, 7, 22, true};

    inserirComIndices(arquivo, a);
    inserirComIndices(arquivo, b);
    inserirComIndices(arquivo, c);

    printf("🎓 USP do curso 10: ");
    imprimirLista(chavesCurso(10));  // 102, 101

    printf("🌎 USP do estado 5: ");
    imprimirLista(chavesEstado(5));  // 102, 101

    return 0;
}