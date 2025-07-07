/*
QUESTÃO 2 – Parte I – Arquivos Simples (sem índices)

Enunciado:
Copie um arquivo texto (com registros no formato "NroUSP|curso|estado|idade") para um novo 
arquivo binário com estrutura REGISTRO. Todos os registros gerados devem ter o campo 
valido = true.
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
Função: converterTextoParaBinario
Objetivo: Ler registros de um arquivo texto e gravá-los em um arquivo binário,
preenchendo o campo 'valido' como true.
*/
void converterTextoParaBinario(const char *arqTxt, const char *arqBin) {
    // Abrir ambos os arquivo: Binário no modo escrita e Texto no modo leitura
    FILE* binario = fopen(arqBin, "wb");
    FILE* texto = fopen(arqTxt, "r");

    // Verificar se ambos os arquivos foram abertos
    if(!binario || !texto){
        printf("Erro ao abrir arquivos.\n");
        return;
    }

    // Leitura do arquivo texto e escrita do binario (apenas com os válidos!)
    REGISTRO r;
    while(fscanf(texto, "%d|%d|%d|%d", &r.NroUSP, &r.curso, &r.estado, &r.idade) == 4){ // fscanf retorna o número de elementos lidos
        r.valido = true;
        fwrite(&r, sizeof(REGISTRO), 1, binario);
    }

    fclose(texto);
    fclose(binario);
}

/*
Função principal: main
Objetivo: Criar um arquivo texto de teste e converter para binário.
*/
int main() {
    const char *arquivoTexto = "entrada.txt";
    const char *arquivoBinario = "saida.bin";

    // Criar arquivo texto manualmente para o exemplo
    FILE *txt = fopen(arquivoTexto, "w");
    if (txt) {
        fprintf(txt, "123|10|35|21\n");
        fprintf(txt, "456|11|25|22\n");
        fprintf(txt, "789|10|31|20\n");
        fclose(txt);
    }

    // Converter texto para binário
    converterTextoParaBinario(arquivoTexto, arquivoBinario);

    printf("Conversão concluída. Verifique o arquivo '%s'.\n", arquivoBinario);
    return 0;
}