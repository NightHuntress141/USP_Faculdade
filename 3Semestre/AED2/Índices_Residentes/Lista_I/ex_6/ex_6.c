/*
QUESTÃO 6 – Parte I – Arquivos Simples (sem índices)

Enunciado:
Escreva uma função para alterar o curso de um aluno com um dado nroUSP, desde que ele esteja
atualmente no curso X. Se for o caso, o curso deve ser atualizado para Y.
A alteração deve ser feita sobrescrevendo o registro no próprio arquivo.
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Estrutura do registro
typedef struct {
    int NroUSP;
    int curso;
    int estado;
    int idade;
    bool valido;
} REGISTRO;

/*
Função: alterarCursoSeCondizente
Objetivo: Procurar um aluno com o NroUSP especificado e curso atual X. 
Se encontrado, alterar para curso Y e sobrescrever no arquivo.
Retorna true se a alteração foi realizada com sucesso.
*/
bool alterarCursoSeCondizente(const char *arquivo, int nroUSP, int cursoAtual, int cursoNovo) {
    FILE* arq = fopen(arquivo, "r+b");
    if(!arq) return false;

    REGISTRO r;
    while(fread(&r, sizeof(REGISTRO), 1, arq) == 1){
        if(r.valido && r.NroUSP == nroUSP && r.curso == cursoAtual){
            r.curso = cursoNovo;
            fseek(arq, -sizeof(REGISTRO), SEEK_CUR);
            fwrite(&r, sizeof(REGISTRO), 1, arq);
            fclose(arq);
            return true;
        }
    }

    fclose(arq);
    return false;
}

/*
Função auxiliar: criarArquivoParaAtualizacao
Objetivo: Criar um arquivo com registros de teste para a alteração de curso.
*/
void criarArquivoParaAtualizacao(const char *arquivo) {
    FILE *f = fopen(arquivo, "wb");
    if (!f) return;

    REGISTRO r1 = {101, 10, 35, 20, true};
    REGISTRO r2 = {102, 20, 25, 22, true};
    REGISTRO r3 = {103, 10, 36, 19, true};

    fwrite(&r1, sizeof(REGISTRO), 1, f);
    fwrite(&r2, sizeof(REGISTRO), 1, f);
    fwrite(&r3, sizeof(REGISTRO), 1, f);

    fclose(f);
}

/*
Função principal: main
Objetivo: Testar a alteração de curso com sucesso e sem sucesso.
*/
int main() {
    const char *arquivo = "alunos.bin";
    criarArquivoParaAtualizacao(arquivo);

    // Teste 1: aluno 101, do curso 10 → mudar para 99
    printf("🔁 Tentando alterar aluno 101 do curso 10 para 99...\n");
    if (alterarCursoSeCondizente(arquivo, 101, 10, 99))
        printf("✅ Curso alterado com sucesso.\n\n");
    else
        printf("❌ Alteração não realizada.\n\n");

    // Teste 2: aluno 102 está no curso 20 → tentar alterar para 99, exigindo que estivesse no curso 10 (erro esperado)
    printf("🔁 Tentando alterar aluno 102 do curso 10 para 99...\n");
    if (alterarCursoSeCondizente(arquivo, 102, 10, 99))
        printf("✅ Curso alterado com sucesso.\n");
    else
        printf("❌ Alteração não realizada (curso atual não condizente).\n");

    return 0;
}