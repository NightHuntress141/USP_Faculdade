/*
QUESTÃO 6 – Parte II – Índices Primários

Enunciado:
Escreva uma função para alterar o NroUSP de um registro para um novo valor, desde que esse novo valor
não exista ainda na tabela de índice. A operação deve:
1. Verificar se o novo NroUSP já existe
2. Excluir o índice antigo (chave antiga)
3. Inserir o índice novo com o mesmo endereço
4. Atualizar o campo no arquivo (acesso direto com fseek)
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

int excluirIndice(INDICE tabela[], int *n, int nroUSP) {
    for (int i = 0; i < *n; i++) {
        if (tabela[i].nroUSP == nroUSP) {
            int end = tabela[i].endereco;
            for (int j = i; j < (*n) - 1; j++) tabela[j] = tabela[j + 1];
            (*n)--;
            return end;
        }
    }
    return -1;
}

// ---------- Função principal ----------

bool alterarChavePrimaria(const char *arquivo, INDICE tabela[], int *n, int antiga, int nova) {
    // Verificando se nova chave já não existe
    if (buscarEndereco(tabela, *n, nova) != -1) return false; // nova chave já existe
    
    // Abrindo a pasta
    FILE* arq = fopen(arquivo, "r+b");
    if(!arq) return false;

    // Buscando a respectiva chave
    int end = buscarEndereco(tabela, n, antiga);
    if(end == -1) return false;

    // Lendo as informações dessa chave
    REGISTRO r;
    fseek(arq, end*sizeof(REGISTRO), SEEK_SET);
    if (fread(&r, sizeof(REGISTRO), 1, arq) != 1 || !r.valido) {
        fclose(arq);
        return false;
    }

    // Mudando o valor do número USP
    r.NroUSP = nova;
    fseek(arq, -sizeof(REGISTRO), SEEK_CUR);
    fwrite(&r, sizeof(REGISTRO), 1, arq);
    fclose(arq);

    // Mudar índice
    inserirIndice(tabela, n, nova, end);
    return true;

}

// ---------- Função de teste ----------

void criarArquivoComChaves(const char *arquivo, INDICE tabela[], int *n) {
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

    criarArquivoComChaves(arquivo, tabela, &n);

    int antiga = 222;
    int nova = 444;

    printf("🔁 Tentando alterar NroUSP %d para %d...\n", antiga, nova);
    if (alterarChavePrimaria(arquivo, tabela, &n, antiga, nova))
        printf("✅ Chave primária alterada com sucesso.\n");
    else
        printf("❌ Alteração não realizada (duplicata ou erro).\n");

    return 0;
}