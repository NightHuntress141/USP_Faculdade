/*
QUESTÃO 3 – Parte I – Arquivos Simples (sem índices)

Enunciado:
Escreva uma função que, dado um número USP X, retorne o registro correspondente do arquivo binário.
Se não encontrado ou se o registro estiver marcado como inválido, a função deve indicar isso.
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

// Estrutura de registro
typedef struct {
    int NroUSP;
    int curso;
    int estado;
    int idade;
    bool valido;
} REGISTRO;

/*
Função: buscarRegistroPorUSP
Objetivo: Procurar no arquivo binário um registro com NroUSP igual ao fornecido.
Se encontrado e válido, preenche a struct passada por ponteiro e retorna true.
Caso contrário, retorna false.
*/
bool buscarRegistroPorUSP(const char *arquivo, int usp, REGISTRO *resultado) {
    FILE* arq = fopen(arquivo, "rb");

    if(!arq){
        printf("Erro ao abrir arquivos.\n");
        return false;
    }

    REGISTRO r;
    while(fread(&r, sizeof(REGISTRO), 1, arq) == 1){
        if(r.valido && r.NroUSP == usp){
            *resultado = r;
            fclose(arq);
            return true;
        }
    }

    fclose(arq);
    return false;
}

/*
Função auxiliar: criarArquivoBinarioDeTeste
Objetivo: Criar um arquivo binário com alguns registros para teste da busca.
*/
void criarArquivoBinarioDeTeste(const char *nomeArquivo) {
    FILE *f = fopen(nomeArquivo, "wb");
    if (!f) {
        printf("Erro ao criar arquivo de teste.\n");
        return;
    }

    REGISTRO r1 = {111, 1, 11, 18, true};
    REGISTRO r2 = {222, 2, 22, 19, false}; // inválido
    REGISTRO r3 = {333, 3, 33, 20, true};

    fwrite(&r1, sizeof(REGISTRO), 1, f);
    fwrite(&r2, sizeof(REGISTRO), 1, f);
    fwrite(&r3, sizeof(REGISTRO), 1, f);

    fclose(f);
}

/*
Função principal: main
Objetivo: Testar a busca de registros com dois casos:
1. Um número USP válido.
2. Um número USP inexistente ou inválido.
*/
int main() {
    const char *arquivo = "alunos.bin";
    criarArquivoBinarioDeTeste(arquivo);

    REGISTRO encontrado;

    // Teste 1: Busca por um registro válido
    int nroBusca1 = 333;
    printf("🔎 Teste 1: Busca por NroUSP %d\n", nroBusca1);
    if (buscarRegistroPorUSP(arquivo, nroBusca1, &encontrado)) {
        printf("✅ Registro encontrado:\n");
        printf("NroUSP: %d | Curso: %d | Estado: %d | Idade: %d\n\n",
               encontrado.NroUSP, encontrado.curso, encontrado.estado, encontrado.idade);
    } else {
        printf("❌ Registro com NroUSP %d não encontrado ou inválido.\n\n", nroBusca1);
    }

    // Teste 2: Busca por um registro inexistente
    int nroBusca2 = 999;
    printf("🔎 Teste 2: Busca por NroUSP %d\n", nroBusca2);
    if (buscarRegistroPorUSP(arquivo, nroBusca2, &encontrado)) {
        printf("✅ Registro encontrado:\n");
        printf("NroUSP: %d | Curso: %d | Estado: %d | Idade: %d\n\n",
               encontrado.NroUSP, encontrado.curso, encontrado.estado, encontrado.idade);
    } else {
        printf("❌ Registro com NroUSP %d não encontrado ou inválido.\n", nroBusca2);
    }

    return 0;
}