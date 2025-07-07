/*
QUESTÃO 4 – Parte I – Arquivos Simples (sem índices)

Enunciado:
Escreva uma função para inserir um novo registro r no arquivo binário, 
tomando cuidado para evitar chaves duplicadas (ou seja, verificar se já existe 
um registro com o mesmo NroUSP antes de inserir).
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Estrutura de registro
typedef struct {
    int NroUSP;
    int curso;
    int estado;
    int idade;
    bool valido;
} REGISTRO;

/*
Função auxiliar: buscarRegistroPorUSP
Objetivo: Verifica se já existe um registro válido com o NroUSP fornecido.
Retorna true se encontrar, false caso contrário.
*/
bool buscarRegistroPorUSP(const char *arquivo, int usp, REGISTRO *resultado) {
    FILE *f = fopen(arquivo, "rb");
    if (!f) return false;

    REGISTRO r;
    while (fread(&r, sizeof(REGISTRO), 1, f) == 1) {
        if (r.valido && r.NroUSP == usp) {
            if (resultado) *resultado = r;
            fclose(f);
            return true;
        }
    }

    fclose(f);
    return false;
}

/*
Função: inserirRegistro
Objetivo: Insere um novo registro no final do arquivo binário, 
desde que a chave NroUSP não esteja duplicada.
Retorna true se a inserção foi feita com sucesso, ou false se a chave já existe.
*/
bool inserirRegistro(const char *arquivo, REGISTRO novo) {
    if (buscarRegistroPorUSP(arquivo, novo.NroUSP, NULL)) {
        return false;  // Duplicata detectada
    }

    FILE* arq = fopen(arquivo, "ab"); // Append em binário -> Adiciona ao final
    if(!arq) return false;

    novo.valido = true;
    fwrite(&novo, sizeof(REGISTRO), 1, arq);
    fclose(arq);
    return true;
}

/*
Função auxiliar: criarArquivoInicial
Objetivo: Cria um arquivo com um registro inicial para testar inserções.
*/
void criarArquivoInicial(const char *arquivo) {
    FILE *f = fopen(arquivo, "wb");
    if (!f) return;

    REGISTRO r = {111, 1, 10, 18, true};
    fwrite(&r, sizeof(REGISTRO), 1, f);
    fclose(f);
}

/*
Função principal: main
Objetivo: Testar a inserção de registros com e sem duplicação.
*/
int main() {
    const char *arquivo = "alunos.bin";
    criarArquivoInicial(arquivo);

    REGISTRO novo1 = {222, 2, 20, 19, true}; // Novo registro, deve ser inserido
    REGISTRO novo2 = {111, 9, 99, 25, true}; // Duplicado, deve ser rejeitado

    printf("Tentando inserir NroUSP %d... ", novo1.NroUSP);
    if (inserirRegistro(arquivo, novo1))
        printf("✅ Inserção realizada.\n");
    else
        printf("❌ Inserção falhou (duplicado).\n");

    printf("Tentando inserir NroUSP %d... ", novo2.NroUSP);
    if (inserirRegistro(arquivo, novo2))
        printf("✅ Inserção realizada.\n");
    else
        printf("❌ Inserção falhou (duplicado).\n");

    return 0;
}