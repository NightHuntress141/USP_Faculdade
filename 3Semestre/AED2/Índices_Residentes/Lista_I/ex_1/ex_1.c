/*
QUESTÃO 1 – Parte I – Arquivos Simples (sem índices)

Enunciado:
Reescreva um arquivo binário arq1 em um novo arquivo arq2 do tipo texto com separador barra (|),
eliminando os registros inválidos (ou seja, aqueles com campo 'valido == false').

Cada linha do arquivo texto deve conter os campos: NroUSP|curso|estado|idade
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Definição da estrutura de registro
typedef struct {
    int NroUSP;     // chave primária
    int curso;
    int estado;
    int idade;
    bool valido;    // marca se o registro é válido (true) ou excluído logicamente (false)
} REGISTRO;

/*
Função: converterBinarioParaTexto
Objetivo: Ler um arquivo binário com registros do tipo REGISTRO e gravar os registros válidos
em um novo arquivo texto com separadores '|'.
*/
void converterBinarioParaTexto(const char *arqBin, const char *arqTxt) {
    // Abrir ambos os arquivo: Binário no modo leitura e Texto no modo escrita
    FILE* binario = fopen(arqBin, "rb");
    FILE* texto = fopen(arqTxt, "w");

    // Verificar se ambos os arquivos foram abertos
    if(!binario || !texto){
        printf("Problema ao tentar abrir os arquivos \n");
        return;
    }

    // Leitura do arquivo binário e escrita do Texto (apenas com os válidos!)
    REGISTRO r; // Criando auxiliar que vai guardar temporariamente cada registro
    while(1 == fread(&r, sizeof(REGISTRO), 1, binario)){
        if(r.valido == true){
            fprintf(texto, "%d|%d|%d|%d", r.NroUSP, r.curso, r.estado, r.idade);
        }
    }

    // Fechando os arquivos utilizados
    fclose(binario);
    fclose(texto);
    
}

/*
Função auxiliar: criarArquivoBinarioDeTeste
Objetivo: Criar um arquivo binário de teste com alguns registros (válidos e inválidos).
*/
void criarArquivoBinarioDeTeste(const char *nomeArquivo) {
    FILE *f = fopen(nomeArquivo, "wb");
    if (!f) {
        printf("Erro ao criar arquivo de teste.\n");
        return;
    }

    REGISTRO r1 = {123, 10, 35, 21, true};
    REGISTRO r2 = {456, 11, 25, 22, false}; // inválido
    REGISTRO r3 = {789, 10, 31, 20, true};

    fwrite(&r1, sizeof(REGISTRO), 1, f);
    fwrite(&r2, sizeof(REGISTRO), 1, f);
    fwrite(&r3, sizeof(REGISTRO), 1, f);

    fclose(f);
}

/*
Função principal: main
Objetivo: Testar a função de conversão com um arquivo binário de exemplo.
*/
int main() {
    const char *arquivoBinario = "dados.bin";
    const char *arquivoTexto = "dados.txt";

    // Criar um arquivo binário de teste com registros simulados
    criarArquivoBinarioDeTeste(arquivoBinario);

    // Converter o binário para texto, eliminando os inválidos
    converterBinarioParaTexto(arquivoBinario, arquivoTexto);

    printf("Conversão concluída. Verifique o arquivo '%s'.\n", arquivoTexto);
    return 0;
}