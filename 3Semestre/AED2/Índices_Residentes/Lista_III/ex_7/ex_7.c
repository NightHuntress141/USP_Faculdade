/*
QUESTÃO 7 – Parte III – Índices Secundários

Enunciado:
Escreva uma função para alterar o registro de nroUSP X para o novo nroUSP Y (se possível).
Isso envolve alterar a chave primária, o que exige:
- Atualização do índice primário
- Atualização dos índices secundários (curso e estado)
- Alteração do campo NroUSP no arquivo, se o novo ainda não existir
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
NO *indiceEstado[100];

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

void excluirIndiceSecundario(NO **lista, int nroUSP) {
    NO *atual = *lista;
    NO *anterior = NULL;

    while (atual) {
        if (atual->nroUSP == nroUSP) {
            if (anterior) anterior->prox = atual->prox;
            else *lista = atual->prox;
            free(atual);
            return;
        }
        anterior = atual;
        atual = atual->prox;
    }
}

void inserirIndiceSecundario(NO *indice[], int chave, int nroUSP) {
    NO *novo = malloc(sizeof(NO));
    novo->nroUSP = nroUSP;
    novo->prox = indice[chave];
    indice[chave] = novo;
}

// ---------- Função principal ----------

bool alterarChavePrimaria(const char *arquivo, int antiga, int nova) {
    if (buscarEndereco(tabelaPrimario, nPrim, nova) != -1) return false;

    int end = excluirIndice(tabelaPrimario, &nPrim, antiga);
    if (end == -1) return false;

    FILE *arq = fopen(arquivo, "r+b");
    if (!arq) return false;

    REGISTRO r;
    fseek(arq, end*sizeof(REGISTRO), SEEK_SET);
    fread(&r, sizeof(REGISTRO), 1, arq);

    if(!r.valido){
        fclose(arq);
        return false;
    }

    r.NroUSP = nova;
    fseek(arq, -sizeof(REGISTRO), SEEK_CUR);
    fwrite(&r, sizeof(REGISTRO), 1, arq);

    // Atualiza índices secundários
    excluirIndiceSecundario(&indiceCurso[r.curso], antiga);
    excluirIndiceSecundario(&indiceEstado[r.estado], antiga);

    inserirIndice(tabelaPrimario, &nPrim, nova, end);
    inserirIndiceSecundario(indiceCurso, r.curso, nova);
    inserirIndiceSecundario(indiceEstado, r.estado, nova);

    fclose(arq);
    return true;

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
    nPrim = 1;

    // Índices secundários
    indiceCurso[10] = inserir(indiceCurso[10], 111);
    indiceEstado[5] = inserir(indiceEstado[5], 111);

    // Criação do arquivo de registros
    FILE *f = fopen(arquivo, "wb");
    if (f) {
        REGISTRO a = {111, 10, 5, 20, true};
        fwrite(&a, sizeof(REGISTRO), 1, f);
        fclose(f);
    }

    // Alteração de chave primária
    printf("🔁 Alterando NroUSP de 111 para 999...\n");
    if (alterarChavePrimaria(arquivo, 111, 999))
        printf("✅ Chave primária alterada com sucesso.\n");
    else
        printf("❌ Falha na alteração.\n");

    // Verificação dos índices
    printf("🎓 Curso 10: "); imprimirLista(indiceCurso[10]);
    printf("🌎 Estado 5: "); imprimirLista(indiceEstado[5]);

    return 0;
}