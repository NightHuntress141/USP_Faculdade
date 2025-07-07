/*
QUESTÃO 5 – Parte I – Arquivos Simples (sem índices)

Enunciado:
Escreva uma função para excluir todos os registros do curso X. A exclusão deve ser lógica,
ou seja, basta alterar o campo 'valido' para false. O arquivo deve ser aberto em modo de
leitura e escrita binária, e os registros alterados devem ser sobrescritos na mesma posição.
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
Função: excluirPorCurso
Objetivo: Percorrer o arquivo e marcar como inválidos (valido = false)
todos os registros cujo campo 'curso' seja igual a 'cursoAlvo'.
Retorna o número de registros excluídos.
*/
int excluirPorCurso(const char *arquivo, int cursoAlvo) {
    FILE* arq = fopen(arquivo, "r+b");   // leitura e escrita binária
    if(!arq) return false;

    REGISTRO r;
    int excluidos = 0;
    while(fread(&r, sizeof(REGISTRO), 1, arq) == 1){
        if(r.curso == cursoAlvo){
            r.valido = false;
            fseek(arq, -sizeof(REGISTRO), SEEK_CUR); // Volta 1 registro atrás
            fwrite(&r, sizeof(REGISTRO), 1, arq); // Sobreescreve
            excluidos++;
        }
    }

    fclose(arq);
    return excluidos;
}

/*
Função auxiliar: criarArquivoParaExclusao
Objetivo: Criar um arquivo com múltiplos registros para teste da função de exclusão por curso.
*/
void criarArquivoParaExclusao(const char *arquivo) {
    FILE *f = fopen(arquivo, "wb");
    if (!f) return;

    REGISTRO r1 = {101, 10, 35, 20, true};
    REGISTRO r2 = {102, 20, 25, 22, true};
    REGISTRO r3 = {103, 10, 36, 19, true};
    REGISTRO r4 = {104, 30, 29, 21, true};

    fwrite(&r1, sizeof(REGISTRO), 1, f);
    fwrite(&r2, sizeof(REGISTRO), 1, f);
    fwrite(&r3, sizeof(REGISTRO), 1, f);
    fwrite(&r4, sizeof(REGISTRO), 1, f);

    fclose(f);
}

/*
Função principal: main
Objetivo: Testar a exclusão de todos os registros com um curso específico.
*/
int main() {
    const char *arquivo = "dados.bin";
    criarArquivoParaExclusao(arquivo);

    int cursoAlvo = 10;
    int total = excluirPorCurso(arquivo, cursoAlvo);

    if (total >= 0)
        printf("✅ %d registro(s) do curso %d foram excluídos logicamente.\n", total, cursoAlvo);
    else
        printf("❌ Erro ao tentar excluir registros.\n");

    return 0;
}