/*
QUESTÃO 1 – Parte IV – Serialização

Enunciado:
Implemente funções para:
1. Escrever uma lista sequencial (vetor de registros) em arquivo binário.
2. Ler o arquivo e reconstruir a lista.
A lista armazena registros com campos simples, e a contagem de elementos
é recuperada diretamente da função fread.
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX 100

// ---------- Estrutura ----------

typedef struct {
    int chave;
    char nome[20];
    int idade;
} REGISTRO;

// ---------- Lista sequencial ----------

REGISTRO lista[MAX];
int prox = 0;

// ---------- Escrita em arquivo ----------

bool salvarLista(const char *arquivo) {
    FILE *f = fopen(arquivo, "wb");
    if (!f) return false;

    size_t salvos = fwrite(lista, sizeof(REGISTRO), prox, f);
    fclose(f);

    return (salvos == prox);
}

// ---------- Leitura do arquivo ----------

bool carregarLista(const char *arquivo) {
    FILE *f = fopen(arquivo, "rb");
    if (!f) return false;

    prox = fread(lista, sizeof(REGISTRO), MAX, f);
    fclose(f);

    return true;
}

// ---------- Utilitários ----------

void exibirLista() {
    for (int i = 0; i < prox; i++) {
        printf("Chave: %d | Nome: %s | Idade: %d\n", lista[i].chave, lista[i].nome, lista[i].idade);
    }
}

void inserir(int chave, const char *nome, int idade) {
    if (prox >= MAX) return;
    lista[prox].chave = chave;
    snprintf(lista[prox].nome, 20, "%s", nome);
    lista[prox].idade = idade;
    prox++;
}

// ---------- Teste ----------

int main() {
    const char *arquivo = "lista_sequencial.bin";

    // Inserção de teste
    inserir(1, "Ana", 20);
    inserir(2, "Bruno", 25);
    inserir(3, "Carla", 22);

    // Escrita
    if (salvarLista(arquivo))
        printf("✅ Lista salva com sucesso.\n");
    else
        printf("❌ Erro ao salvar a lista.\n");

    // Reset local e leitura
    prox = 0;
    if (carregarLista(arquivo))
        printf("✅ Lista carregada com sucesso.\n");
    else
        printf("❌ Erro ao carregar a lista.\n");

    // Exibição
    exibirLista();

    return 0;
}