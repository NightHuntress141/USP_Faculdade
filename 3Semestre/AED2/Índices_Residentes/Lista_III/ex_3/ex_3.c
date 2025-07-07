/*
QUESTÃO 3 – Parte III – Índices Secundários

Enunciado:
Escreva uma função para excluir o registro de nroUSP X.
Use o índice primário para localizar e invalidar o registro.
Atualize também os índices primário e secundários (curso e estado).
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

// Opcional!!
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

// ---------- Função principal ----------

bool excluirRegistroPorUSP(const char *arquivo, int nroUSP) {
    int end = buscarEndereco(tabelaPrimario, nPrim, nroUSP);
    if(end == -1){
        printf("Registro não existe no arquivo para ser excluido");
        return false;
    }

    FILE* arq = fopen(arquivo, "r+b");
    if(!arq) return false;

    REGISTRO r;
    fseek(arq, sizeof(REGISTRO)*end, SEEK_SET);
    fread(&r, sizeof(REGISTRO), 1, arq);

    if (!r.valido) {
        fclose(arq);
        return false;
    }

    r.valido = false;
    fseek(arq, -sizeof(REGISTRO), SEEK_CUR);
    fwrite(&r, sizeof(REGISTRO), 1, arq);

    excluirIndice(tabelaPrimario, end, nroUSP);
    excluirIndiceSecundario(&indiceCurso[r.curso], nroUSP); // Opcional
    excluirIndiceSecundario(&indiceEstado[r.estado], nroUSP); // Opcional

    fclose(arq);
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
    nPrim = 2;

    // Índices secundários
    indiceCurso[10] = inserir(indiceCurso[10], 222);
    indiceCurso[10] = inserir(indiceCurso[10], 111);
    indiceEstado[5] = inserir(indiceEstado[5], 222);
    indiceEstado[5] = inserir(indiceEstado[5], 111);

    // Criação do arquivo de registros
    FILE *f = fopen(arquivo, "wb");
    if (f) {
        REGISTRO a = {111, 10, 5, 20, true};
        REGISTRO b = {222, 10, 5, 21, true};
        fwrite(&a, sizeof(REGISTRO), 1, f);
        fwrite(&b, sizeof(REGISTRO), 1, f);
        fclose(f);
    }

    // Exclusão
    printf("❌ Excluindo aluno 111...\n");
    if (excluirRegistroPorUSP(arquivo, 111))
        printf("✅ Registro excluído com sucesso.\n");
    else
        printf("❌ Registro não encontrado ou inválido.\n");

    // Verificação
    printf("🎓 Curso 10: "); imprimirLista(indiceCurso[10]);
    printf("🌎 Estado 5: "); imprimirLista(indiceEstado[5]);

    return 0;
}