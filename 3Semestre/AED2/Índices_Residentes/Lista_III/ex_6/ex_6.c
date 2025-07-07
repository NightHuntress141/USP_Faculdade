/*
QUESTÃO 6 – Parte III – Índices Secundários

Enunciado:
Escreva uma função para alterar o curso de um registro de nroUSP X para o curso Y.
Use o índice primário para localizar o registro no arquivo.
Atualize o campo `curso` no arquivo e, opcionalmente, o índice secundário.
Neste caso, atualizaremos o índice secundário para manter a consistência.
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

bool alterarCurso(const char *arquivo, int nroUSP, int novoCurso) {
    int end = buscarEndereco(tabelaPrimario, nPrim, nroUSP);
    if(end == -1) return false;

    FILE* arq = fopen(arquivo, "r+b");
    if(!arq) return false;

    REGISTRO r;
    fseek(arq, sizeof(REGISTRO)*end, SEEK_SET);
    fread(&r, sizeof(REGISTRO), 1, arq);

    if(!r.valido){
        int cursoAntigo = r.curso;
        r.curso = novoCurso;

        fseek(arq, -sizeof(REGISTRO), SEEK_CUR);
        fwrite(&r, sizeof(REGISTRO), 1, arq);
        
        excluirIndiceSecundario(&indiceCurso[cursoAntigo], nroUSP);
        inserirIndiceSecundario(&indiceCurso, novoCurso, nroUSP);

        fclose(arq);
        return true;
    }

    fclose(arq);
    return false;
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

    // Índice secundário por curso
    indiceCurso[10] = inserir(indiceCurso[10], 111);

    // Criação do arquivo de registros
    FILE *f = fopen(arquivo, "wb");
    if (f) {
        REGISTRO a = {111, 10, 5, 20, true};
        fwrite(&a, sizeof(REGISTRO), 1, f);
        fclose(f);
    }

    // Alteração de curso
    printf("🔁 Alterando curso do aluno 111 de 10 para 20...\n");
    if (alterarCurso(arquivo, 111, 20))
        printf("✅ Curso atualizado com sucesso.\n");
    else
        printf("❌ Falha na alteração.\n");

    // Verificação dos índices secundários
    printf("🎓 Curso 10: "); imprimirLista(indiceCurso[10]);
    printf("🎓 Curso 20: "); imprimirLista(indiceCurso[20]);

    return 0;
}